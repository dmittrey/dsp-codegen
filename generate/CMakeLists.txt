cmake_minimum_required(VERSION 3.11)
project(generate)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include_priv)

target_link_libraries(${PROJECT_NAME} PUBLIC utility)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)