#ifndef SKULL_PRELUDE_FILTER_H
#define SKULL_PRELUDE_FILTER_H


#include "../base/append.h"
#include "../base/bind.h"
#include "foldl.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::bind_first;
    using skull::base::bind_last;
    using skull::base::append_if;

    /**
     * @tparam UnaryPredicate unary predicate
     * @tparam TypeList target type list
     */
    template <typename UnaryPredicate, typename TypeList>
    struct filter;

    template <typename p, typename... xs>
    struct filter<p, TL<xs...>>
            : foldl<
                bind_last<
                    quote<append_if>,
                    bind_first<quote<invoke>, p>
                >,          // binary function
                TL<>,       // lefe-side accumulation
                TL<xs...>
              >
    { };

    /**
     * @tparam UnaryPredicate unary predicate
     * @tparam TypeList target type list
     */
    template <typename UnaryPredicate, typename TypeList>
    using filter_t = typename filter<UnaryPredicate, TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_FILTER_H
