
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class Pessoa {
private:
    int idade_;

public:
    std::string name_;
    
    Pessoa(std::string name, int idade) : name_(name), idade_(idade) {}
};


int addTwoNumbers(int num1, int num2) {
    return num1 + num2;
}

PYBIND11_MODULE(myModule, m) {
    m.def("addTwoNumbers", &addTwoNumbers);


    py::class_<Pessoa>(m, "ClassePython")
        .def(py::init<std::string, int>())
        .def_readwrite("name_", &Pessoa::name_);
}


