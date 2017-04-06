#ifndef SKULL_BASE_BIND_H
#define SKULL_BASE_BIND_H


#include "invoke.h"


namespace skull::base
{
    /**
     * bind_first itself is a metafunction class
     * and also a kind of higher-order metafunction.
     *
     * @tparam f metafunction class
     * @tparam xs type list to bind first
     */
    template <typename f, typename... xs>
    struct bind_first
    {
        template <typename... ys>
        struct lambda : invoke<f, xs..., ys...>
        { };
    };

    /**
     * bind_last itself is a metafunction class
     * and also a kind of higher-order metafunction.
     *
     * @tparam f metafunction class
     * @tparam xs type list to bind last
     */
    template <typename f, typename... xs>
    struct bind_last
    {
        template <typename... ys>
        struct lambda : invoke<f, ys..., xs...>
        { };
    };
} // namespace skull::base


#endif // SKULL_BASE_BIND_H
