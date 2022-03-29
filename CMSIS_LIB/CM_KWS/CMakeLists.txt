cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(example-standalone-inferencing-zephyr)

include(utils/cmake/utils.cmake)
# Needed for colorful output
zephyr_compile_options(-fdiagnostics-color=always)

# Use hardware acceleration for DSP and Neural Network code
# You'll need to disable these on non-Arm cores
add_definitions(-DEIDSP_USE_CMSIS_DSP=1
                -DEIDSP_LOAD_CMSIS_DSP_SOURCES=1
                -DEI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN=1
                -DEIDSP_QUANTIZE_FILTERBANK=0
                -DARM_MATH_LOOPUNROLL
                -DEI_SENSOR_AQ_STREAM=FILE
                )

# Edge impulse SDK include directories
set(INCLUDES
    .
    edge-impulse-sdk
    edge-impulse-sdk/third_party/ruy
    edge-impulse-sdk/third_party/gemmlowp
    edge-impulse-sdk/third_party/flatbuffers/include
    edge-impulse-sdk/third_party
    edge-impulse-sdk/tensorflow
    edge-impulse-sdk/dsp
    edge-impulse-sdk/CMSIS/NN/Include
    edge-impulse-sdk/CMSIS/DSP/PrivateInclude
    edge-impulse-sdk/CMSIS/DSP/Include
    edge-impulse-sdk/CMSIS/Core/Include
    edge-impulse-sdk/porting
    )
include_directories(${INCLUDES})

#edge-impulse/ingestion-sdk-c
#    edge-impulse/ingestion-sdk-platform/NordicSemi-nrf52
#    edge-impulse/ingestion-sdk-platform/NordicSemi-nrf52/sensors
#    edge-impulse/mbedtls_hmac_sha256_sw
#    edge-impulse/QCBOR/inc
#    edge-impulse/QCBOR/src
#    edge-impulse/repl

add_library(
    EXTERN
    internally_implemented.h
    kws_input_data.cc
    kws_input_data.h
    kws_model_data.cc
    kws_model_data.h
    kws_model_settings.cc
    kws_model_settings.h
)


RECURSIVE_FIND_FILE(SOURCE_FILES "edge-impulse-sdk" "*.cpp")
RECURSIVE_FIND_FILE(CC_FILES "edge-impulse-sdk" "*.cc")
RECURSIVE_FIND_FILE(S_FILES "edge-impulse-sdk" "*.s")
RECURSIVE_FIND_FILE(C_FILES "edge-impulse-sdk" "*.c")
RECURSIVE_FIND_FILE(PORTING_FILES "edge-impulse-sdk/porting/zephyr" "*.cpp")
RECURSIVE_FIND_FILE(EXTERN "src" "*.h")

list(APPEND SOURCE_FILES ${S_FILES})
list(APPEND SOURCE_FILES ${C_FILES})
list(APPEND SOURCE_FILES ${CC_FILES})
list(APPEND SOURCE_FILES ${PORTING_FILES})
list(APPEND SOURCE_FILES ${EXTERN})

# add all sources to the project
target_sources(app PRIVATE ${SOURCE_FILES})
target_sources(app PRIVATE main.cpp PRIVATE internally_implemented.cpp)
#target_link_libraries(app PRIVATE EXTERN)
