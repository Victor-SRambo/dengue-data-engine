
#include <pybind11/pybind11.h>
#include "sorting.h"

class PySortingStrategy : public SortingStrategy {
public:
    using SortingStrategy::SortingStrategy;

    void sort(std::vector<int>& vector, std::vector<int>& idx, int min, int max) override {
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
};