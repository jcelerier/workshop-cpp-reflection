#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <boost/pfr.hpp>
#include "ex4.hpp"
namespace nb = nanobind;

NB_MODULE(ex4, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());
    
    the_class.def_prop_rw("name", 
        [] (const Cat& cat) { return boost::pfr::get<0>(cat); }, 
        [] (Cat& cat, const std::string& value) { boost::pfr::get<0>(cat) = value; }
    );
    
    the_class.def_prop_rw("whiskers", 
        [] (const Cat& cat) { return boost::pfr::get<1>(cat); }, 
        [] (Cat& cat, int value) { boost::pfr::get<1>(cat) = value; }
    );
    
    the_class.def("meow", &Cat::meow);
}
