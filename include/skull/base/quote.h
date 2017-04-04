#ifndef SKULL_BASE_QUOTE_H
#define SKULL_BASE_QUOTE_H


namespace skull::base
{
    /**
     * quote itself is a helper metafunction class
     * which turns metafunction into metafunction classe.
     *
     * @tparam f metafunction
     */
    template <template <typename...> class f>
    struct quote
    {
        template <typename... xs>
        struct lambda : f<xs...>
        { };
    };
} // namespace skull::base


#endif // SKULL_BASE_QUOTE_H
