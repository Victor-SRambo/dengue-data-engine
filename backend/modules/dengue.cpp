#include <iostream>

#include "dengue_case.h"
#include "case_mapper.h"
#include "bin_file_manager.h"
#include "case_indexer.h"
#include "binary_search.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;



PYBIND11_MODULE(dengue, m) {

    
    py::class_<DengueCaseMapper>(m, "DengueCaseMapper")
        .def(py::init<>())
        .def("map_vectors_to_class", &DengueCaseMapper::map_vectors_to_class);



    py::class_<DengueFieldVectors>(m, "DengueFieldVectors")
        .def(py::init<>())

        .def_readwrite("notification_dates", &DengueFieldVectors::notification_dates)
        .def_readwrite("first_symptoms_dates", &DengueFieldVectors::first_symptoms_dates)
        .def_readwrite("epidemiological_weeks", &DengueFieldVectors::epidemiological_weeks)

        .def_readwrite("state_notification_codes", &DengueFieldVectors::state_notification_codes)
        .def_readwrite("city_notification_codes", &DengueFieldVectors::city_notification_codes)

        .def_readwrite("state_living_codes", &DengueFieldVectors::state_living_codes)
        .def_readwrite("city_living_codes", &DengueFieldVectors::city_living_codes)

        .def_readwrite("ages", &DengueFieldVectors::ages)
        .def_readwrite("year_births", &DengueFieldVectors::year_births)
        .def_readwrite("escolarities", &DengueFieldVectors::escolarities)
        .def_readwrite("professions", &DengueFieldVectors::professions)
        .def_readwrite("pregnancy_states", &DengueFieldVectors::pregnancy_states)
        .def_readwrite("ethnicities", &DengueFieldVectors::ethnicities)

        .def_readwrite("sexes", &DengueFieldVectors::sexes);

    
    py::class_<DengueCase>(m, "DengueCase")
        .def(py::init<>())

        .def_readwrite("notification_date", &DengueCase::notification_date)
        .def_readwrite("first_symptoms_date", &DengueCase::first_symptoms_date)
        .def_readwrite("epidemiological_week", &DengueCase::epidemiological_week)

        .def_readwrite("state_notification_code", &DengueCase::state_notification_code)
        .def_readwrite("city_notification_code", &DengueCase::city_notification_code)

        .def_readwrite("state_living_code", &DengueCase::state_living_code)
        .def_readwrite("city_living_code", &DengueCase::city_living_code)

        .def_readwrite("age", &DengueCase::age)
        .def_readwrite("year_birth", &DengueCase::year_birth)
        .def_readwrite("escolarity", &DengueCase::escolarity)
        .def_readwrite("profession", &DengueCase::profession)
        .def_readwrite("pregnacy_state", &DengueCase::pregnacy_state)
        .def_readwrite("ethnicity", &DengueCase::ethnicity)
        .def_readwrite("sex", &DengueCase::sex);
}

