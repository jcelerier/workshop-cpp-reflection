#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

// -std=c++26 -freflection -stdlib=libc++
#include <experimental/meta>
#include "ex7.hpp"
namespace nb = nanobind;

template<std::size_t Index, typename T>
static consteval auto nth_name() {
    static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
    return name_of(member);
}

template<std::size_t Index, typename T>
static consteval auto nth_getter() {
    static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
    return +[] (const T& t) { return t.[: member :]; };
}

template<std::size_t Index, typename T>
static consteval auto nth_setter() {
    static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
    return +[] (T& t, const [: type_of(member) :] & value) { t.[: member :] = value; };
}

template<std::size_t Index, typename T>
static void register_property(nb::class_<T>& the_class)
{
    the_class.def_prop_rw(
        nth_name<Index, T>().data(), 
        nth_getter<Index, T>(), 
        nth_setter<Index, T>()
    );
}

template<typename T>
consteval auto member_count()
{ 
  return std::meta::nonstatic_data_members_of(^T).size();
}

NB_MODULE(ex7, m) {
    nb::class_<Cat> the_class(m, "Cat");

    the_class.def(nb::init<>());

    constexpr auto count = member_count<Cat>();
    [&] <std::size_t... Is> (std::index_sequence<Is...>) {
      (register_property<Is>(the_class), ...);
    }(std::make_index_sequence<count>{});

    the_class.def("meow", &Cat::meow);
}
