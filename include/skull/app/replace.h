#ifndef SKULL_APP_REPLACE_H
#define SKULL_APP_REPLACE_H


#include <type_traits>

#include "../prelude/map.h"


namespace skull::app
{
    using skull::base::TL;
    using skull::base::quote;
    using skull::base::invoke_v;
    using skull::prelude::map_t;

    /**
     * @tparam TypeList source type list
     * @tparam UnaryPredicate a unary predicate metafunction class
     * @tparam T target type
     */
    template <typename TypeList, typename UnaryPredicate, typename T>
    struct replace_if;

    template <typename... xs, typename p, typename T>
    struct replace_if<TL<xs...>, p, T>
    {
        template <typename U>
        struct replace_impl
                : std::conditional<
                        invoke_v<p, U>,
                        T,
                        U
                  >
        { };

        using type = map_t<quote<replace_impl>, TL<xs...>>;
    };

    template <typename TypeList, typename UnaryPredicate, typename T>
    using replace_if_t = typename replace_if<TypeList, UnaryPredicate, T>::type;
} // namespace skull::app


#endif // SKULL_APP_REPLACE_H
