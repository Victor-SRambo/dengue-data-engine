#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "case_sorter.h"
#include "sorter_trampoline.h"

namespace py = pybind11;

PYBIND11_MODULE(case_sorter, m) {

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


    py::class_<CaseSorter>(m, "CaseSorter") 
        .def(py::init<std::shared_ptr<SortingStrategy>>())
        .def("sort", &CaseSorter::sort);


    py::class_<CaseSortingField,
               PyCaseSortingField,
               std::shared_ptr<CaseSortingField>>(m, "CaseSortingField")
        .def(py::init<>())
        .def("field", &CaseSortingField::get_field);


    py::class_<DateField,
               CaseSortingField,
               std::shared_ptr<DateField>>(m, "DateField")
        .def(py::init<>());


    py::class_<CityCodeField,
               CaseSortingField,
               std::shared_ptr<CityCodeField>>(m, "CityCodeField")
        .def(py::init<>());


};