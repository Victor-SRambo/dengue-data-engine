
#include <pybind11/pybind11.h>
#include "case_sorter.h"

template <typename Arbovirus>
class PyCaseSortingField : public CaseSortingField<Arbovirus> {
public:
    using CaseSortingField<Arbovirus>::CaseSortingField;

    int extract(const Arbovirus& c) override {
        PYBIND11_OVERRIDE_PURE(
            int,            
            CaseSortingField<Arbovirus>, 
            extract,         
            c               
        );
    }
};

