
set(INCLUDE_DIR ${LIBRADICL_TOP_DIR}/include)
message(STATUS "libradicl include directory : ${INCLUDE_DIR}")


set(SRC
        Header.cpp
        Tags.cpp
        Buffer.cpp
        Byte_Array.cpp
        RAD_Writer.cpp
)


add_library(radicl STATIC ${SRC})


target_include_directories(radicl PRIVATE ${INCLUDE_DIR})

target_compile_options(radicl PRIVATE ${COMPILE_FLAGS})

target_link_options(radicl PRIVATE ${LINK_FLAGS})


install(TARGETS radicl
        DESTINATION lib)


add_executable(test test.cpp)

target_include_directories(test PRIVATE ${INCLUDE_DIR})
target_compile_options(test PRIVATE ${COMPILE_FLAGS})
target_link_options(test PRIVATE ${LINK_FLAGS})
target_link_libraries(test radicl)


add_executable(test_flushable test_flushable.cpp)

target_include_directories(test_flushable PRIVATE ${INCLUDE_DIR})
target_compile_options(test_flushable PRIVATE ${COMPILE_FLAGS})
target_link_options(test_flushable PRIVATE ${LINK_FLAGS})
target_link_libraries(test_flushable radicl)
