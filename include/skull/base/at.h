#ifndef SKULL_BASE_AT_H
#define SKULL_BASE_AT_H


#include <tuple>

#include "type_list.h"


namespace skull::base
{
    template <typename Index, typename TypeList>
    struct at;
    
    template <std::size_t i, typename... xs>
    struct at<std::integral_constant<std::size_t, i>, TL<xs...>>
            : std::tuple_element<i, std::tuple<xs...>>
    { };

    template <typename Index, typename TypeList>
    using at_t = typename at<Index, TypeList>::type;


    template <std::size_t i, typename TypeList>
    struct at_c : at<std::integral_constant<std::size_t, i>, TypeList>
    { };

    template <std::size_t i, typename TypeList>
    using at_c_t = at_t<std::integral_constant<std::size_t, i>, TypeList>;
} // namespace skull::base


#endif // SKULL_BASE_AT_H
