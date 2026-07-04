#include <iostream>

#include "dengue_case.h"
#include "mapper.h"
#include "file_manager.h"
#include "sorter.h"
#include "indexer.h"
#include "sorter_binding.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;


void printAge(DengueCase dengueCase) {
    std::cout << dengueCase.age;
}

PYBIND11_MODULE(dengue, m) {

    m.def("printAge", &printAge);
    
    py::class_<DadosAbertosMapper>(m, "DadosAbertosMapper")
        .def(py::init<>())
        .def("mapDengueCase", &DadosAbertosMapper::mapDengueCase);


    py::class_<FileManager>(m, "FileManager")
        .def(py::init<>())
        .def("append_bin", &FileManager::append_bin)
        .def("truncate_bins", &FileManager::truncate_bins)
        .def("load_bin", &FileManager::load_bin)
        .def("overwrite_bin", &FileManager::overwrite_bin);

        
    py::class_<CaseSorter>(m, "CaseSorter") 
        .def(py::init<>())
        .def("sort", &CaseSorter::sort)
        .def("select_field", &CaseSorter::select_field);

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

    py::class_<CaseSortingField,
               PyCaseSortingField,
               std::shared_ptr<CaseSortingField>>(m, "CaseSortingField")
        .def(py::init<>())
        .def("field", &CaseSortingField::field);

    py::class_<CaseDateField,
               CaseSortingField,
               std::shared_ptr<CaseDateField>>(m, "CaseDateField")
        .def(py::init<>());

    py::class_<CaseCityCodeField,
               CaseSortingField,
               std::shared_ptr<CaseCityCodeField>>(m, "CaseCityCodeField")
        .def(py::init<>());

    

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

