#include <iostream>

#include "dengue_case.h"
#include "mapper.h"
#include "file_manager.h"
#include "indexer.h"
#include "binary_search.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;



PYBIND11_MODULE(dengue, m) {

    
    py::class_<DadosAbertosMapper>(m, "DadosAbertosMapper")
        .def(py::init<>())
        .def("mapDengueCase", &DadosAbertosMapper::mapDengueCase);


    py::class_<FileManager>(m, "FileManager")
        .def(py::init<>())
        .def("append_bin", &FileManager::append_bin)
        .def("truncate_bins", &FileManager::truncate_bins)
        .def("load_bin", &FileManager::load_bin)
        .def("overwrite_bin", &FileManager::overwrite_bin)
        .def("save_indexes", &FileManager::save_indexes)
        .def("load_indexes", &FileManager::load_indexes)
        .def("load_bin_from_index", &FileManager::load_bin_from_index);


    py::class_<BinarySearch>(m, "BinarySearch")
        .def(py::init<>())
        .def("index_search", &BinarySearch::index_search)
        .def("after_date_search", &BinarySearch::after_date_search)
        .def("before_date_search", &BinarySearch::before_date_search);


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

    

    py::class_<IndexRegister>(m, "IndexRegister")
        .def(py::init<>())
        .def_readwrite("city_notification_code", &IndexRegister::city_notification_code)
        .def_readwrite("start", &IndexRegister::start)
        .def_readwrite("end", &IndexRegister::end);

    py::class_<Indexer>(m, "Indexer")
        .def(py::init<>())
        .def("create_index", &Indexer::create_index);

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

