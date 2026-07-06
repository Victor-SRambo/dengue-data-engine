cmake_minimum_required(VERSION 3.50)
project(Dengue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



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
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/dengue_case.cpp
)

target_include_directories(
    dengue 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/models
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/engine
)

pybind11_add_module(
    case_sorter 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/modules/case_sorter.cpp
)

target_include_directories(
    case_sorter 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/models
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/engine
)
