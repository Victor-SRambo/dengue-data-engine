
#include <pybind11/pybind11.h>
#include "case_sorter.h"

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


class PySortingStrategy : public SortingStrategy {
public:
    using SortingStrategy::SortingStrategy;

    void sort(std::vector<int>& vector, std::vector<int>&idx, int min, int max) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            SortingStrategy,
            sort,
            vector,
            idx,
            min,
            max
        );
    }

    int partition(std::vector<int>& vector, std::vector<int>&idx, int min, int max) override {
        PYBIND11_OVERRIDE_PURE(
            int,
            SortingStrategy,
            partition,
            vector,
            idx,
            min,
            max
        );        
    }
};

