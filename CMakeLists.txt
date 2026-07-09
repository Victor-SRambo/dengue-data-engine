cmake_minimum_required(VERSION 3.50)
project(Dengue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODULE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/modules")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MODULE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MODULE_OUTPUT_DIR})
foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${MODULE_OUTPUT_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${MODULE_OUTPUT_DIR})
endforeach()

include(FetchContent)

set(PYBIND11_VERSION v3.0.1)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG ${PYBIND11_VERSION}
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(
    dengue 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/dengue.cpp
)

target_include_directories(
    dengue 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/engine
)

pybind11_add_module(
    engine 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/engine.cpp
)

target_include_directories(
    engine 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/trampolines
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/bindings
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/engine
)

if(MINGW)
    target_link_options(dengue PRIVATE -static-libgcc -static-libstdc++ -static -lwinpthread)
    target_link_options(engine PRIVATE -static-libgcc -static-libstdc++ -static -lwinpthread)
endif()