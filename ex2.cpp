#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "ex2.hpp"
namespace nb = nanobind;

NB_MODULE(ex2, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());
        
    the_class.def_rw("name", &Cat::name);
    the_class.def_rw("whiskers", &Cat::whiskers);

    the_class.def("meow", &Cat::meow);
}
