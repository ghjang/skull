#ifndef SKULL_PRELUDE_ELEM_H
#define SKULL_PRELUDE_ELEM_H


#include <type_traits>

#include "../base/type_list.h"
#include "../base/bind.h"
#include "map.h"
#include "sum.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::bind_last;

    template <typename T, typename TypeList>
    struct elem;

    template <typename T>
    struct elem<T, TL<>> : std::false_type
    { };

    template <typename T, typename x, typename... xs>
    struct elem<T, TL<x, xs...>>
            : std::bool_constant<
                    0 < sum_v<  // if the sum is greater than 0,
                            map_t<
                                bind_last<quote<std::is_same>, T>,
                                TL<x, xs...>
                            >
                        >
              >
    { };

    template <typename T, typename TypeList>
    inline constexpr auto elem_v = elem<T, TypeList>::value;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_ELEM_H
