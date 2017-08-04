#ifndef SKULL_PRELUDE_REPLICATE_H
#define SKULL_PRELUDE_REPLICATE_H


#include <array>
#include <tuple>

#include "../base/type_list.h"
#include "id.h"
#include "map.h"


namespace skull::prelude
{
    using skull::base::TL;

    template <typename n, typename x>
    struct replicate;

    template <typename n, typename x>
    using replicate_t = typename replicate<n, x>::type;

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

        // NOTE: lambda expressions can't be used
        //          in an unevaluated operand context directly.
        using type = decltype(l());
    };

    /**
     * workaround to fix the compile error, 'function cannot return function type'.
     */
    template <typename T, T n, typename R, typename... Args>
    struct replicate<std::integral_constant<T, n>, R(Args...)>
            : map<
                    quote<std::remove_pointer>,
                    replicate_t<
                        std::integral_constant<T, n>,
                        std::add_pointer_t<R(Args...)>
                    >
              >
    { };

    /**
     * workaround to fix the compile error, 'function cannot return array type'.
     */
    template <typename T, T n, typename U>
    struct replicate<std::integral_constant<T, n>, U[]>
            : map<
                    quote<std::remove_pointer>,
                    replicate_t<
                        std::integral_constant<T, n>,
                        std::add_pointer_t<U[]>
                    >
              >
    { };

    /**
     * workaround to fix the compile error, 'function cannot return array type'.
     */
    template <typename T, T n, typename U, T m>
    struct replicate<std::integral_constant<T, n>, U[m]>
            : map<
                    quote<std::remove_pointer>,
                    replicate_t<
                        std::integral_constant<T, n>,
                        std::add_pointer_t<U[m]>
                    >
              >
    { };

    template <std::size_t n, typename x>
    using replicate_c = replicate<std::integral_constant<std::size_t, n>, x>;

    template <std::size_t n, typename x>
    using replicate_c_t = typename replicate_c<n, x>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_REPLICATE_H
