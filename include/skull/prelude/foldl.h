#ifndef SKULL_PRELUDE_FOLDL_H
#define SKULL_PRELUDE_FOLDL_H


#include "../base/type_list.h"


namespace skull::prelude
{
    using skull::base::type_is;
    using skull::base::TL;
    using skull::base::invoke_t;

    /**
     * assumed that f is op:
     *      (...(init op t0) op t1) op t2)... op tn)
     *
     * @tparam f metafunction class
     */
    template <typename f, typename init, typename TypeList>
    struct foldl
    { };

    template <typename f, typename init>
    struct foldl<f, init, TL<>> : type_is<init>
    { };

    template <typename f, typename init, typename x, typename... xs>
    struct foldl<f, init, TL<x, xs...>>
            : foldl<f, invoke_t<f, init, x>, TL<xs...>>
    { };
} // namespace skull::prelude


#endif // SKULL_PRELUDE_FOLDL_H
