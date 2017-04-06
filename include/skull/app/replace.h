#ifndef SKULL_APP_REPLACE_H
#define SKULL_APP_REPLACE_H


#include <type_traits>

#include "../prelude/map.h"


namespace skull::app
{
    using skull::base::TL;
    using skull::base::quote;
    using skull::base::invoke_v;
    using skull::base::bind_last;
    using skull::prelude::map_t;

    /**
     * @tparam UnaryPredicate a unary predicate metafunction class
     * @tparam T new type
     * @tparam TypeList source type list
     */
    template <typename UnaryPredicate, typename T, typename TypeList>
    struct replace_if;

    template <typename p, typename T, typename... xs>
    struct replace_if<p, T, TL<xs...>>
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

    template <typename UnaryPredicate, typename T, typename TypeList>
    using replace_if_t = typename replace_if<UnaryPredicate, T, TypeList>::type;

    /**
     * @tparam T old type
     * @tparam U new type
     * @tparam TypeList source type list
     */
    template <typename T, typename U, typename TypeList>
    struct replace
            : replace_if<
                bind_last<quote<std::is_same>, T>,
                U,
                TypeList
              >
    { };

    template <typename T, typename U, typename TypeList>
    using replace_t = typename replace<T, U, TypeList>::type;
} // namespace skull::app


#endif // SKULL_APP_REPLACE_H
