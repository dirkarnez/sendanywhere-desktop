#include "sendanywhere.h"
#include <stdlib.h>
#include <stdio.h>

void callback(SendAnywhereState state, SendAnywhereDetailedState detailedState,
					const void* param, void* userptr) {
	int i;

	if(state == SENDANYWHERE_STATE_PREPARING) {
		if(detailedState == SENDANYWHERE_DETAILED_STATE_PREPARING_UPDATED_KEY) {
			const wchar_t* key = (const wchar_t*)param;
			printf("key: %ls\n", key);
		}
	} else if(state == SENDANYWHERE_STATE_TRANSFERRING) {
		const SendAnywhereTransferFileInfo* file = (const SendAnywhereTransferFileInfo*)param;
		printf("%ls => %lld/%lld\n", file->fullPath, file->sent, file->size);
	} else if(state == SENDANYWHERE_STATE_FINISHED) {
		switch(detailedState) {
		case SENDANYWHERE_DETAILED_STATE_FINISHED_SUCCESS:
			printf("Transfer finished (success)\n");
			break;
		case SENDANYWHERE_DETAILED_STATE_FINISHED_CANCEL:
			printf("Transfer finished (canceled)\n");
			break;
		case SENDANYWHERE_DETAILED_STATE_FINISHED_ERROR:
			printf("Transfer finished (error!)\n");
			break;
		}
	} else if(state == SENDANYWHERE_STATE_ERROR) {
		switch(detailedState) {
		case SENDANYWHERE_DETAILED_STATE_ERROR_SERVER:
			printf("Network or Server Error!\n");
			break;
		case SENDANYWHERE_DETAILED_STATE_ERROR_NO_REQUEST:
			printf("Timeout for waiting recipient\n");
			break;
		case SENDANYWHERE_DETAILED_STATE_ERROR_NO_EXIST_FILE:
			printf("No exist files!\n");
			break;
		}
	}
};


int main(int argc, char** argv) {
	sendanywhere_init("8b75c2f76418fe47d6eb95604a8ae5003b5ce3af", ".sendanywhere-token");

	wchar_t** files = (wchar_t**)malloc(sizeof(wchar_t**)* (argc - 1)); 

    for (int i = 1; i < argc; i++) {
		const size_t cSize = strlen(argv[i]) + 1;
		files[i] = (wchar_t*)malloc(sizeof(wchar_t*)*cSize); 
		mbstowcs (files[i], argv[i], cSize); 
	}
	
	SendAnywhereTask task = sendanywhere_create_send(files, argc - 1);
	sendanywhere_set_listner(task, callback, 0);

	sendanywhere_start(task);
	sendanywhere_wait(task);

	sendanywhere_cleanup();

    return 0;
}
