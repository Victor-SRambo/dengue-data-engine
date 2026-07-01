cmake_minimum_required(VERSION 3.50)
project(Dengue)

include(FetchContent)

set(PYBIND11_VERSION v3.0.1)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG ${PYBIND11_VERSION}
)
FetchContent_MakeAvailable(pybind11)
pybind11_add_module(myModule backend/test.cpp)
