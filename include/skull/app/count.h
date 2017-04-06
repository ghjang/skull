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

    template <typename TypeList, typename UnaryPredicate>
    struct count_if;

    template <typename... xs, typename p>
    struct count_if<TL<xs...>, p>
            : sum<
                map_t<
                    bind_first<quote<invoke>, p>,
                    TL<xs...>
                >
              >
    { };

    template <typename TypeList, typename UnaryPredicate>
    inline constexpr auto count_if_v = count_if<TypeList, UnaryPredicate>::value;
} // namespace skull::app


#endif // SKULL_APP_COUNT_H
