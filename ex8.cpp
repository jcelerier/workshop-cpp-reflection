#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

// -std=c++26 -freflection -stdlib=libc++
#include <experimental/meta>
#include "ex8.hpp"
namespace nb = nanobind;

template <std::size_t Index, typename T>
static consteval auto nth_name()
{
  static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
  return name_of(member);
}

template <std::size_t Index, typename T>
static consteval auto nth_getter()
{
  static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
  return +[](const T &t)
  { return t.[:member:]; };
}

template <std::size_t Index, typename T>
static consteval auto nth_setter()
{
  static constexpr auto member = std::meta::nonstatic_data_members_of(^T)[Index];
  return +[](T &t, const[:type_of(member):] & value)
  { t.[:member:] = value; };
}

template <std::size_t Index, typename T>
static void register_property(nb::class_<T> &the_class)
{
  the_class.def_prop_rw(
      nth_name<Index, T>().data(),
      nth_getter<Index, T>(),
      nth_setter<Index, T>());
}

template <typename T>
consteval auto member_count()
{
  return std::meta::nonstatic_data_members_of(^T).size();
}

template <typename T>
consteval auto function_count()
{
  int i = 0;
  auto mems = std::meta::members_of(^T);
  for (auto mem : mems)
  {
    if (is_function(mem) && !is_constructor(mem) && !is_destructor(mem) && !is_special_member(mem))
      i++;
  }
  return i;
}

template <std::size_t I, typename T>
consteval auto nth_function()
{
  int i = 0;
  auto mems = std::meta::members_of(^T);
  for (auto mem : mems)
  {
    if (is_function(mem) && !is_constructor(mem) && !is_destructor(mem) && !is_special_member(mem))
    {
      if(i == I)
        return mem;
      i++;
    }
  }
  return ^void;
}

template <std::size_t Index, typename T>
static consteval auto nth_function_call()
{
  static constexpr auto func = nth_function<Index, T>();
  return +[](T &t) { t.[:func:](); };
}

template <std::size_t Index, typename T>
static void register_function(nb::class_<T> &the_class)
{
  the_class.def(
      name_of(nth_function<Index, T>()).data(),
      nth_function_call<Index, T>());
}

NB_MODULE(ex8, m)
{
  nb::class_<Cat> the_class(m, "Cat");

  the_class.def(nb::init<>());

  [&]<std::size_t... Is>(std::index_sequence<Is...>)
  {
    (register_property<Is>(the_class), ...);
  }(std::make_index_sequence<member_count<Cat>()>{});

  [&]<std::size_t... Is>(std::index_sequence<Is...>)
  {
    (register_function<Is>(the_class), ...);
  }(std::make_index_sequence<function_count<Cat>()>{});
}
