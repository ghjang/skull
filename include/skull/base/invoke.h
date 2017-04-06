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

    template <typename f, typename... xs>
    using invoke_t = typename invoke<f, xs...>::type;

    template <typename f, typename... xs>
    inline constexpr auto invoke_v = invoke<f, xs...>::value;
} // namespace skull::base


#endif // SKULL_BASE_INVOKE_H
