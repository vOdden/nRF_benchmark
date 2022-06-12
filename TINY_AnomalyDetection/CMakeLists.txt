cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tensorflow_hello_world)

# These samples use local static initialization. Since Zephyr doesn't support the
# C++ ABI for thread-safe initialization of local statics and the constructors don't
# appear to require thread safety, we turn it off in the C++ compiler.
set(NO_THREADSAFE_STATICS $<TARGET_PROPERTY:compiler-cpp,no_threadsafe_statics>)
zephyr_compile_options($<$<COMPILE_LANGUAGE:CXX>:${NO_THREADSAFE_STATICS}>)


#######

add_library(
    api_intern
    internally_implemented.cpp
    internally_implemented.h
    submitter_implemented.h
    #model2.cpp
    model.h
)



add_library(
    header_files
    model.cc
    model.h
    internally_implemented.h
    internally_implemented.cpp
    submitter_implemented.h
)


target_sources(app PRIVATE internally_implemented.cpp PRIVATE submitter_implemented.cpp)
target_link_libraries(app PRIVATE header_files)

