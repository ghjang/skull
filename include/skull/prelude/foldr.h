#ifndef SKULL_PRELUDE_FOLDR_H
#define SKULL_PRELUDE_FOLDR_H


#include "../base/identity.h"
#include "../base/type_list.h"
#include "../base/quote.h"
#include "../base/invoke.h"


namespace skull::prelude
{
    using skull::base::type_is;
    using skull::base::TL;
    using skull::base::invoke;

    /**
     * assumed that f is op:
     *  (t0 op (t1 op (t2 op ...(tn op init)...)
     *
     *  @tparam f (binary) metafunction class
     */
    template <typename f, typename init, typename TypeList>
    struct foldr
    { };

    template <typename f, typename init, typename TypeList>
    using foldr_t = typename foldr<f, init, TypeList>::type;

    template <typename f, typename init>
    struct foldr<f, init, TL<>> : type_is<init>
    { };

    template <typename f, typename init, typename x, typename... xs>
    struct foldr<f, init, TL<x, xs...>>
            : invoke<
                f,
                x,
                foldr_t<f, init, TL<xs...>>
              >
    { };
} // namespace skull::prelude


#endif // SKULL_PRELUDE_FOLDR_H
