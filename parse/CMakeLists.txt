cmake_minimum_required(VERSION 3.11)
project(parse)

set(LIBS
        interface
        json)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()