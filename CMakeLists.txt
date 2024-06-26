cmake_minimum_required(VERSION 3.11)
project(portable-isp)

set(LIBS
        parse
        utility
        syntax
        serialize
        generate
        lexem)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE parse-json)
target_link_libraries(${PROJECT_NAME} PRIVATE generate-isp)
target_link_libraries(${PROJECT_NAME} PRIVATE serialize-file)