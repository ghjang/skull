#ifndef SKULL_PRELUDE_REVERSE_H
#define SKULL_PRELUDE_REVERSE_H


#include "foldl.h"


namespace skull::prelude
{
    template <typename TypeList>
    struct reverse;

    template <>
    struct reverse<TL<>> : type_is<TL<>>
    { };

    template <typename x, typename... xs>
    struct reverse<TL<x, xs...>>
    {
        template <typename Acc, typename T>
        struct prepend_impl;

        template <typename... ys, typename T>
        struct prepend_impl<TL<ys...>, T> : type_is<TL<T, ys...>>
        { };

        using type = foldl_t<
                        quote<prepend_impl>,     // binary function
                        TL<>,                    // left-side accumulation
                        TL<x, xs...>
                     >;
    };

    template <typename TypeList>
    using reverse_t = typename reverse<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_REVERSE_H
