
#include <pybind11/pybind11.h>
#include "sorter.h"

class PyCaseSortingField : public CaseSortingField {
public:
    using CaseSortingField::CaseSortingField;

    void field(std::vector<DengueCase>& cases, std::vector<int>& vector, std::vector<int>& indexes) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            CaseSortingField,
            field,
            cases,
            vector,
            indexes
        );
    }


};
