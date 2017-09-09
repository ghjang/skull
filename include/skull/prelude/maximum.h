#ifndef SKULL_PRELUDE_MAXIMUM_H
#define SKULL_PRELUDE_MAXIMUM_H


#include "foldr.h"
#include "max.h"


namespace skull::prelude
{
    template <typename TypeList>
    struct maximum;

    template <typename... T>
    struct maximum<TL<T...>>
            : foldr<
                quote<max>,
                TL<>,       // right init
                TL<T...>
              >
    { };

    template <typename TypeList>
    using maximum_t = typename maximum<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_MAXIMUM_H
