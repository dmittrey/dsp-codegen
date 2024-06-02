cmake_minimum_required(VERSION 3.11)
project(generate)

set(LIBS
        isp)

foreach(elem ${LIBS})
    add_subdirectory(${elem})
endforeach()