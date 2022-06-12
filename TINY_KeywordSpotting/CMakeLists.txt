cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(tensorflow_hello_world)

# These samples use local static initialization. Since Zephyr doesn't support the
# C++ ABI for thread-safe initialization of local statics and the constructors don't
# appear to require thread safety, we turn it off in the C++ compiler.
set(NO_THREADSAFE_STATICS $<TARGET_PROPERTY:compiler-cpp,no_threadsafe_statics>)
zephyr_compile_options($<$<COMPILE_LANGUAGE:CXX>:${NO_THREADSAFE_STATICS}>)



#	Add neccesary files to the library
add_library(
    	req_files
   	internally_implemented.h
	internally_implemented.cpp
    	submitter_implemented.h
    	kws_input_data.cc
	kws_input_data.h
	kws_model_data.cc
	kws_model_data.h
	kws_model_settings.cc
	kws_model_settings.h
    	quantization_helpers.h
	tf_micro_model_runner.h
)




#	Source target
target_sources(app PRIVATE internally_implemented.cpp PRIVATE submitter_implemented.cpp)

#	Link libraries to target
target_link_libraries(app PRIVATE req_files)



