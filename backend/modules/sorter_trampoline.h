
#include <pybind11/pybind11.h>
#include "case_sorter.h"

class PyCaseSortingField : public CaseSortingField {
public:
    using CaseSortingField::CaseSortingField;

    // CORREÇÃO: Adicionado o 'const' para casar exatamente com a classe base corrigida
    int extract(const DengueCase& c) override {
        PYBIND11_OVERRIDE_PURE(
            int,               // Tipo de retorno
            CaseSortingField,  // Classe pai
            extract,           // Nome do método no C++ / Python
            c                  // Argumento
        );
    }
};

class PySortingStrategy : public SortingStrategy {
public:
    using SortingStrategy::SortingStrategy;

    void sort(std::vector<int>& vector, std::vector<int>& idx, int min, int max) override {
        PYBIND11_OVERRIDE_PURE(
            void,            // Tipo de retorno
            SortingStrategy, // Classe pai
            sort,            // Nome do método
            std::ref(vector),// CORREÇÃO: Força o pybind a passar como referência real, não como cópia!
            std::ref(idx),   // CORREÇÃO: Mesma coisa para os índices
            min,
            max
        );
    }
};