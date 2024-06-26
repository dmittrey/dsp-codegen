cmake_minimum_required(VERSION 3.11)
project(generate-isp)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE lexem)
target_link_libraries(${PROJECT_NAME} PRIVATE syntax-cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC utility)
target_link_libraries(${PROJECT_NAME} PUBLIC serialize-interface)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)