cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tensorflow_hello_world)

# These samples use local static initialization. Since Zephyr doesn't support the
# C++ ABI for thread-safe initialization of local statics and the constructors don't
# appear to require thread safety, we turn it off in the C++ compiler.
set(NO_THREADSAFE_STATICS $<TARGET_PROPERTY:compiler-cpp,no_threadsafe_statics>)
zephyr_compile_options($<$<COMPILE_LANGUAGE:CXX>:${NO_THREADSAFE_STATICS}>)

#include_directories( api )
#add_executable(aps api/internally_implemented.h)
#add_executable(Api2 internally_implemented.h)
#add_executable(Api3 submitter_implemented.h)
#set_target_properties(aps PROPERTIES LINKER_LANGUAGE CPP)

#######

add_library(
    api_intern
    internally_implemented.cpp
    internally_implemented.h
    submitter_implemented.h
    #model2.cpp
    model.h
)

#add_executable(Hopefully_main main.cpp)
#target_link_libraries(app PRIVATE api_intern)

#file(GLOB src_files CONFIGURE_DEPENDS
#    ".h"
#    ".cpp"
#    "api/*.cpp"
#    "api/*.h"
#    "util/*.h"
#)

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




#target_sources(app PRIVATE api/internally_implemented.cpp)
#target_sources(app PRIVATE api/internally_implemented.h)
#target_sources(app PRIVATE api/submitter_implemented.h)


