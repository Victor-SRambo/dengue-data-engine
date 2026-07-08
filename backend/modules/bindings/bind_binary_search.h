


#pragma once

#include <pybind11/pybind11.h>
#include "binary_search.h"

namespace py = pybind11;


void bind_binary_search(py::module_& m)
{
    py::class_<BinarySearch<DengueCase>>(m, "DengueBinarySearch")
        .def(py::init<>())
        .def("index_search", &BinarySearch<DengueCase>::index_search)
        .def("after_date_search", &BinarySearch<DengueCase>::after_date_search)
        .def("before_date_search", &BinarySearch<DengueCase>::before_date_search);
}








