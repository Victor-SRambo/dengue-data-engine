#pragma once

#include <pybind11/pybind11.h>

#include "case_indexer.h"
#include "dengue_case.h"

namespace py = pybind11;

void bind_case_indexer(py::module_& m)
{

    py::class_<IndexRegister>(m, "IndexRegister")
        .def(py::init<>())
        .def_readwrite("city_notification_code", &IndexRegister::city_notification_code)
        .def_readwrite("start", &IndexRegister::start)
        .def_readwrite("end", &IndexRegister::end);

    py::class_<CaseIndexer<DengueCase>>(m, "DengueCaseIndexer")
        .def(py::init<>())
        .def("create_city_indexes", &CaseIndexer<DengueCase>::create_city_indexes);

}


