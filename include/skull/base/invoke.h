#ifndef SKULL_BASE_INVOKE_H
#define SKULL_BASE_INVOKE_H


namespace skull::base
{
    /**
     * invoke itself is a higher-order metafunction.
     *
     * invoke calls the metafunction wrapped inside the metafunction class f indirectly.
     *
     * @tparam f metafunction class
     */
    template <typename f, typename... xs>
    struct invoke : f::template lambda<xs...>
    { };

    template <typename f, typename TypeList>
    using invoke_t = typename invoke<f, TypeList>::type;
} // namespace skull::base


#endif // SKULL_BASE_INVOKE_H
