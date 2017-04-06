#ifndef SKULL_APP_REMOVE_H
#define SKULL_APP_REMOVE_H


#include <type_traits>

#include "../base/bind.h"
#include "../base/compose.h"
#include "../prelude/not.h"
#include "../prelude/filter.h"


namespace skull::app
{
    using skull::base::quote;
    using skull::base::compose;
    using skull::prelude::not_;
    using skull::prelude::filter;

    /**
     * @tparam UnaryPredicate unary predicate
     * @tparam TypeList source type list
     */
    template <typename UnaryPredicate, typename TypeList>
    struct remove_if;

    template <typename p, typename... xs>
    struct remove_if<p, TL<xs...>>
            : filter<
                compose<
                    quote<not_>,
                    p
                >,
                TL<xs...>
              >
    { };

    template <typename UnaryPredicate, typename TypeList>
    using remove_if_t = typename remove_if<UnaryPredicate, TypeList>::type;


    /**
     * @tparam T type to remove
     * @tparam TypeList source type list
     */
     template <typename T, typename TypeList>
     struct remove
                : remove_if<
                        bind_first<quote<std::is_same>, T>,
                        TypeList
                  >
     { };
     
     template <typename T, typename TypeList>
     using remove_t = typename remove<T, TypeList>::type;
} // namespace skull::app


#endif // SKULL_APP_REMOVE_H
