
cmake_minimum_required(VERSION 3.14)


set(LIB_NAME libradicl)
project(${LIB_NAME}
        VERSION 0.1.0
        LANGUAGES CXX C
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)


set(WARNING_FLAGS -Wall -Wextra -Wpedantic)

set(OPTIMIZE_FLAGS -funroll-loops)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(LIBRADICL_TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
