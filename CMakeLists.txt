cmake_minimum_required(VERSION 3.11)
project(portable-isp)

set(LIBS
        parser
        utility
        generate
        agregate
        common)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME} PRIVATE generate)
target_link_libraries(${PROJECT_NAME} PRIVATE agregate)