
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

set(COMPILE_FLAGS ${WARNING_FLAGS} ${OPTIMIZE_FLAGS})

# Here, we have some platform-specific considerations
# of which we must take care.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    execute_process(
        COMMAND getconf LEVEL1_DCACHE_LINESIZE
        COMMAND tr -d '\n'
        OUTPUT_VARIABLE L1_CACHE_LINE_SIZE
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
        # OSX has `getconf`, but doesn't report `LEVEL1_DCACHE_LINESIZE`;
        # so we instead use `sysctl` for the corresponding variable.
        execute_process(
            COMMAND sysctl machdep.cpu.cache.linesize
            COMMAND awk "{print $2}"
            COMMAND tr -d '\n'
            OUTPUT_VARIABLE L1_CACHE_LINE_SIZE
        )
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
        execute_process(
            COMMAND sysctl hw.cachelinesize
            COMMAND awk "{print $2}"
            COMMAND tr -d '\n'
            OUTPUT_VARIABLE L1_CACHE_LINE_SIZE
        )
    else()
        message(FATAL_ERROR "Unable to identify Apple Silicon processor architecture")
    endif()
endif()

add_compile_definitions(L1_CACHE_LINE_SIZE=${L1_CACHE_LINE_SIZE})
add_compile_definitions(CMAKE_EXPORT_COMPILE_COMMANDS)  # For better `clangd` scanning.


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(LIBRADICL_TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
