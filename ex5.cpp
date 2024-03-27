#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <boost/pfr.hpp>
#include "ex5.hpp"
namespace nb = nanobind;

template<std::size_t Index, typename T>
static void register_property(nb::class_<T>& the_class)
{
    the_class.def_prop_rw(boost::pfr::get_name<Index, T>().data(), 
        [] (const T& t) { return boost::pfr::get<Index>(t); }, 
        [] (T& t, const boost::pfr::tuple_element_t<Index, T>& value) { boost::pfr::get<Index>(t) = value; }
    );
}

NB_MODULE(ex5, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());
    
    register_property<0>(the_class);
    register_property<1>(the_class);
    
    the_class.def("meow", &Cat::meow);
}
