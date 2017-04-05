#ifndef SKULL_PRELUDE_CONCAT_H
#define SKULL_PRELUDE_CONCAT_H


#include "foldl.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::quote;

    /**
     * @tparam xss a type list of type lists
     */
    template <typename xss>
    struct concat
    { };

    template <typename... xss>
    struct concat<TL<xss...>>
    {
        /**
         * concatenation binary operation
         *
         * @tparam xs left-side type list. It should be a type_list instance.
         * @tparam ys right-side type list. It should be a type_list instance.
         */
        template <typename xs, typename ys>
        struct binary_concat;

        template <typename... xs, typename... ys>
        struct binary_concat<TL<xs...>, TL<ys...>>
                : type_is<TL<xs..., ys...>>
        { };

        using type = foldl_t<quote<binary_concat>, TL<>, TL<xss...>>;
    };

    template <typename xss>
    using concat_t = typename concat<xss>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_CONCAT_H
