#ifndef SKULL_PRELUDE_REPLICATE_H
#define SKULL_PRELUDE_REPLICATE_H


#include <array>
#include <tuple>

#include "../base/type_list.h"
#include "id.h"


namespace skull::prelude
{
    using skull::base::TL;

    template <typename n, typename x>
    struct replicate;

    template <typename T, T n, typename x>
    struct replicate<std::integral_constant<T, n>, x>
    {
        constexpr static auto l = []{
            std::array<id<x>, n> arr;
            return std::apply(
                        [](auto... xs) {
                            return TL<
                                        decltype(xs.val())...
                                   >{};
                        },
                        arr
                   );
        };

        using type = decltype(l());
    };

    template <typename n, typename x>
    using replicate_t = typename replicate<n, x>::type;

    template <std::size_t n, typename x>
    using replicate_c = replicate<std::integral_constant<std::size_t, n>, x>;

    template <std::size_t n, typename x>
    using replicate_c_t = typename replicate_c<n, x>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_REPLICATE_H
