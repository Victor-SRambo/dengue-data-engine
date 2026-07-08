#pragma once

#include <pybind11/pybind11.h>
#include "case_sorter.h"
#include "case_sorter_trampoline.h"
#include "dengue_case.h"

namespace py = pybind11;


void bind_case_sorter(py::module_& m)
{

    py::class_<CaseSorter<DengueCase>>(m, "DengueCaseSorter") 
        .def(py::init<std::shared_ptr<SortingStrategy>>())
        .def("sort", &CaseSorter<DengueCase>::sort);


    py::class_<CaseSortingField<DengueCase>,
               PyCaseSortingField<DengueCase>,
               std::shared_ptr<CaseSortingField<DengueCase>>>(m, "DengueCaseSortingField")
        .def("field", &CaseSortingField<DengueCase>::get_field);


    py::class_<DateField<DengueCase>,
               CaseSortingField<DengueCase>,
               std::shared_ptr<DateField<DengueCase>>>(m, "DengueDateField")
        .def(py::init<>());


    py::class_<CityCodeField<DengueCase>,
               CaseSortingField<DengueCase>,
               std::shared_ptr<CityCodeField<DengueCase>>>(m, "DengueCityCodeField")
        .def(py::init<>());

}













