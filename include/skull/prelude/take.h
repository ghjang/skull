#ifndef SKULL_PRELUDE_TAKE_H
#define SKULL_PRELUDE_TAKE_H


#include <type_traits>

#include "foldl.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::type_is;

    template <std::size_t n, typename TypeList>
    struct take;

    template <std::size_t n>
    struct take<n, TL<>> : type_is<TL<>>
    { };

    template <std::size_t n, typename x, typename... xs>
    struct take<n, TL<x, xs...>>
    {
        template <std::size_t i>
        using int_c_t = std::integral_constant<std::size_t, i>;

        template <typename Acc, typename T>
        struct append_until;

        template <std::size_t i, typename... ys, typename T>
        struct append_until<std::pair<int_c_t<i>, TL<ys...>>, T>
                : std::conditional<
                        i == 0,
                        std::pair<int_c_t<0>, TL<ys...>>,
                        std::pair<int_c_t<i - 1>, TL<ys..., T>>
                    >
        { };
        
        using type = typename foldl_t<
                                quote<append_until>,         // binary function
                                std::pair<int_c_t<n>, TL<>>, // left-side accumulation
                                TL<x, xs...>
                              >::second_type;
    };

    template <std::size_t n, typename TypeList>
    using take_t = typename take<n, TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_TAKE_H
