#ifndef SKULL_APP_UNIQUE_H
#define SKULL_APP_UNIQUE_H


#include <type_traits>

#include "../base/type_list.h"
#include "../prelude/foldl.h"
#include "../prelude/elem.h"


namespace skull::app
{
    using skull::base::TL;
    using skull::prelude::foldl_t;
    using skull::prelude::elem_v;

    template <typename TypeList>
    struct unique;

    template <typename... xs>
    struct unique<TL<xs...>>
    {
        template <typename Acc, typename T>
        struct append_unique;

        template <typename... ys, typename T>
        struct append_unique<TL<ys...>, T>
                : std::conditional<
                        elem_v<T, TL<ys...>>,
                        TL<ys...>,
                        TL<ys..., T>
                  >
        { };

        using type = foldl_t<
                        quote<append_unique>,   // binary function
                        TL<>,                   // left-side accumulation
                        TL<xs...>
                     >;
    };

    template <typename TypeList>
    using unique_t = typename unique<TypeList>::type;
} // namespace skull::app


#endif // SKULL_APP_UNIQUE_H
