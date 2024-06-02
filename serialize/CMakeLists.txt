cmake_minimum_required(VERSION 3.11)
project(serialize)

set(LIBS
        interface
        generic
        file)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()