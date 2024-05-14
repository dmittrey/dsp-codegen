cmake_minimum_required(VERSION 3.11)
project(agregate)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_link_libraries(${PROJECT_NAME} INTERFACE utility)
target_link_libraries(${PROJECT_NAME} INTERFACE parser)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})