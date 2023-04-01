cmake_minimum_required(VERSION 3.18)

project("SendAnywhereSDK")

include_directories("include")

add_library(${PROJECT_NAME} src/sendanywhere.c)

target_link_libraries(${PROJECT_NAME} sendanywhere)
