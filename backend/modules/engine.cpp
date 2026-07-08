#include <iostream>


#include "bind_bin_file_manager.h"
#include "bind_binary_search.h"
#include "bind_case_sorter.h"
#include "bind_sorting.h"
#include "bind_case_indexer.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;


PYBIND11_MODULE(engine, m) {

    bind_bin_file_manager(m);
    bind_binary_search(m);
    bind_case_sorter(m);
    bind_sorting(m);
    bind_case_indexer(m);

};