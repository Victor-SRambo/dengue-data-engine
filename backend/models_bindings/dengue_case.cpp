#include <iostream>

#include "dengue_case.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;


void printAge(DengueCase dengueCase) {
    std::cout << dengueCase.age;
}

PYBIND11_MODULE(dengue, m) {

    m.def("printAge", &printAge);

    py::class_<DengueCase>(m, "DengueCase")
        .def(py::init<>())

        .def_readwrite("notification_date", &DengueCase::notification_date)
        .def_readwrite("first_symptoms_date", &DengueCase::first_symptoms_date)
        .def_readwrite("epidemiological_week", &DengueCase::epidemiological_week)

        .def_readwrite("state_notification_code", &DengueCase::state_notification_code)
        .def_readwrite("city_notification_code", &DengueCase::city_notification_code)

        .def_readwrite("state_living_code", &DengueCase::state_living_code)
        .def_readwrite("city_living_code", &DengueCase::city_living_code)

        .def_readwrite("name", &DengueCase::name)
        .def_readwrite("age", &DengueCase::age)
        .def_readwrite("year_birth", &DengueCase::year_birth)
        .def_readwrite("escolarity", &DengueCase::escolarity)
        .def_readwrite("profession", &DengueCase::profession)
        .def_readwrite("pregnacy_state", &DengueCase::pregnacy_state)
        .def_readwrite("ethnicity", &DengueCase::ethnicity)
        .def_readwrite("sex", &DengueCase::sex);
}

