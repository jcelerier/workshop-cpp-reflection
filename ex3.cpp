#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "ex3.hpp"
namespace nb = nanobind;

NB_MODULE(ex3, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());
        
    the_class.def_prop_rw("name", 
        [] (const Cat& cat) { return cat.name; }, 
        [] (Cat& cat, const std::string& value) { cat.name = value; }
    );
    
    the_class.def_prop_rw("whiskers", 
        [] (const Cat& cat) { return cat.whiskers; }, 
        [] (Cat& cat, int value) { cat.whiskers = value; }
    );

    the_class.def("meow", &Cat::meow);
}
