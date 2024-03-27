#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "ex1.hpp"
namespace nb = nanobind;

NB_MODULE(ex1, m) {
    nb::class_<Cat>(m, "Cat")
        .def(nb::init<>())
        
        .def_rw("name", &Cat::name)
        .def_rw("whiskers", &Cat::whiskers)

        .def("meow", &Cat::meow)
        ;
}
