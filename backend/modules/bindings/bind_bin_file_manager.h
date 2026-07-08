
#pragma once

#include <pybind11/pybind11.h>
#include "bin_file_manager.h"

namespace py = pybind11;


void bind_bin_file_manager(py::module_& m)
{
    py::class_<BinaryFileManager<DengueCase>>(m, "DengueBinaryFileManager")
        .def(py::init<>())
        .def("truncate_cases_year_bin", &BinaryFileManager<DengueCase>::truncate_cases_year_bin)
        .def("append_cases_year_bin", &BinaryFileManager<DengueCase>::append_cases_year_bin)
        .def("load_cases_date_bin", &BinaryFileManager<DengueCase>::load_cases_date_bin)
        .def("overwrite_cases_bin", &BinaryFileManager<DengueCase>::overwrite_cases_bin)
        .def("load_cases_from_index_bin", &BinaryFileManager<DengueCase>::load_cases_from_index_bin)
        .def("overwrite_city_indexes", &BinaryFileManager<DengueCase>::overwrite_city_indexes)
        .def("load_city_indexes", &BinaryFileManager<DengueCase>::load_city_indexes);
}