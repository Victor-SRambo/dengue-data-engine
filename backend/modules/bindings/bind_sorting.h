#pragma once

#include <pybind11/pybind11.h>

#include "sorting.h"
#include "sorting_trampoline.h"

namespace py = pybind11;

void bind_sorting(py::module_& m)
{

    py::class_<SortingStrategy,
                PySortingStrategy,
                std::shared_ptr<SortingStrategy>>(m, "SortingStrategy")
        .def(py::init<>());


    py::class_<QuickSort,
                SortingStrategy,
                std::shared_ptr<QuickSort>>(m, "QuickSort")
        .def(py::init<>());


    py::class_<MergeSort,
                SortingStrategy,
                std::shared_ptr<MergeSort>>(m, "MergeSort")
        .def(py::init<>());

}


