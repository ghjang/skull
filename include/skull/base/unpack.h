#ifndef SKULL_BASE_UNPACK_H
#define SKULL_BASE_UNPACK_H


namespace skull::base
{
    template <template <typename...> class T, typename TypeList>
    struct unpack;

    template <template <typename...> class T, typename... xs>
    struct unpack<T, TL<xs...>> : type_is<T<xs...>>
    { };

    template <template <typename...> class T, typename TypeList>
    using unpack_t = typename unpack<T, TypeList>::type;
} // namespace skull::base


#endif // SKULL_BASE_UNPACK_H
