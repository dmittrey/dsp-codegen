cmake_minimum_required(VERSION 3.11)
project(syntax)

set(LIBS
        interface
        generic
        cpp)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()