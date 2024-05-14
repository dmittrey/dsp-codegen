cmake_minimum_required(VERSION 3.11)
project(parser)

include(FetchContent)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        master
)

FetchContent_GetProperties(jsoncpp)
if (NOT jsoncpp_POPULATED)
    FetchContent_Populate(jsoncpp)
    add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR})
    message(${jsoncpp_SOURCE_DIR})
    message(${jsoncpp_BINARY_DIR})
endif ()

FetchContent_MakeAvailable(jsoncpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} jsoncpp_static)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG_LEX=1>)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})