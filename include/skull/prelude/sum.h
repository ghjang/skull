#ifndef SKULL_PRELUDE_SUM_H
#define SKULL_PRELUDE_SUM_H


#include <type_traits>

#include "../base/type_list.h"


namespace skull::prelude
{
    using skull::base::TL;

    template <typename TypeList>
    struct sum;

    template <>
    struct sum<TL<>>
            : std::integral_constant<int, 0>
    { };

    template <typename T, T... i>
    struct sum<TL<std::integral_constant<T, i>...>>
            : std::integral_constant<T, (... + i)>
    { };

    template <typename TypeList>
    inline constexpr auto sum_v = sum<TypeList>::value;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_SUM_H
