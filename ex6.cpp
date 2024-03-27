#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <boost/pfr.hpp>
#include "ex6.hpp"
namespace nb = nanobind;

template<std::size_t Index, typename T>
static void register_property(nb::class_<T>& the_class)
{
    the_class.def_prop_rw(boost::pfr::get_name<Index, T>().data(), 
        [] (const T& t) { return boost::pfr::get<Index>(t); }, 
        [] (T& t, const boost::pfr::tuple_element_t<Index, T>& value) { boost::pfr::get<Index>(t) = value; }
    );
}

NB_MODULE(ex6, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());
    
    constexpr auto count = boost::pfr::tuple_size_v<Cat>;
    [&] <std::size_t... Is> (std::index_sequence<Is...>) {
      (register_property<Is>(the_class), ...);
    }(std::make_index_sequence<count>{});
    
    the_class.def("meow", &Cat::meow);
}
