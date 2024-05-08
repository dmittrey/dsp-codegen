cmake_minimum_required(VERSION 3.11)
project(portable-isp)

add_subdirectory(parser)
add_subdirectory(utility)
add_subdirectory(generate)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME} PRIVATE generate)
target_link_libraries(${PROJECT_NAME} PRIVATE utility)