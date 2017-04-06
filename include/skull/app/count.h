#ifndef SKULL_APP_COUNT_H
#define SKULL_APP_COUNT_H


#include "../base/type_list.h"
#include "../base/invoke.h"
#include "../base/bind.h"
#include "../prelude/sum.h"


namespace skull::app
{
    using skull::base::TL;
    using skull::base::invoke;
    using skull::base::bind_first;
    using skull::prelude::sum;

    /**
     * @tparam UnaryPredicate a unary predicate metafunction class
     * @tparam TypeList source type list
     */
    template <typename UnaryPredicate, typename TypeList>
    struct count_if;

    template <typename p, typename... xs>
    struct count_if<p, TL<xs...>>
            : sum<
                map_t<
                    bind_first<quote<invoke>, p>,
                    TL<xs...>
                >
              >
    { };

    template <typename UnaryPredicate, typename TypeList>
    inline constexpr auto count_if_v = count_if<UnaryPredicate, TypeList>::value;
} // namespace skull::app


#endif // SKULL_APP_COUNT_H
