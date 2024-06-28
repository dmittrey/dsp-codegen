cmake_minimum_required(VERSION 3.11)
project(syntax)

set(LIBS
        interface
        generic
        c)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()