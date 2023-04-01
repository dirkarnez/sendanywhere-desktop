cmake_minimum_required(VERSION 3.18)

add_subdirectory(SDK)

project("sendanywhere-desktop")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(CMAKE_VERBOSE_MAKEFILE on)
#SET(CMAKE_C_FLAGS "-g")

if(WIN32)
    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        link_directories(${CMAKE_SOURCE_DIR}/SDK/lib/windows/x64)
    else()
        link_directories(${CMAKE_SOURCE_DIR}/SDK/lib/windows/win32)
    endif()
elseif(APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/SDK/lib/osx)
elseif(UNIX)
    EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDK/lib/linux/${ARCHITECTURE})
endif()

target_include_directories(SendAnywhereSDK PUBLIC "SDK/include")

add_executable(sample_send src/sample_send.c)
target_link_libraries(sample_send SendAnywhereSDK)

add_executable(sample_receive src/sample_receive.c)
target_link_libraries(sample_receive SendAnywhereSDK)

