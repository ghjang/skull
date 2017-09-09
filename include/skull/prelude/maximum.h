#ifndef SKULL_PRELUDE_MAXIMUM_H
#define SKULL_PRELUDE_MAXIMUM_H


#include "foldr.h"
#include "max.h"


namespace skull::prelude
{
    template <typename TypeList>
    struct maximum;

#if __clang_major__ >= 5
    template <typename... T>
    struct maximum<TL<T...>>
            : foldr<
                quote<max>,
                TL<>,       // right init
                TL<T...>
              >
    {
        constexpr maximum() = default;
        
        template <typename U>
        constexpr maximum(U &&...)   // discard all arguments
        { }
    };

    template <typename... T>
    maximum(T &&...) -> maximum<TL<std::decay_t<T>...>>;

#else

    template <typename... T>
    struct maximum<TL<T...>>
            : foldr<
                quote<max>,
                TL<>,       // right init
                TL<T...>
            >
    { };

#endif // __clang_major__ >= 5

    template <typename TypeList>
    using maximum_t = typename maximum<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_MAXIMUM_H
