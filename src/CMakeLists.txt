
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)


set(SRC
        libradicl.cpp
)


add_library(libradicl STATIC ${SRC})


target_include_directories(libradicl PRIVATE ${INCLUDE_DIR})


set(COMPILE_FLAGS ${WARNING_FLAGS} ${OPTIMIZE_FLAGS})


target_compile_options(libradicl PRIVATE ${COMPILE_FLAGS})


install(TARGETS libradicl
        DESTINATION lib)
