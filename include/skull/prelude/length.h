#ifndef SKULL_PRELUDE_LENGTH_H
#define SKULL_PRELUDE_LENGTH_H


#include <type_traits>


namespace skull::prelude
{
    using skull::base::TL;

    template <typename TypeList>
    struct length;

    template <template <typename...> class TypeList, typename... xs>
    struct length<TypeList<xs...>>
            : std::integral_constant<std::size_t, sizeof...(xs)>
    { };

    template<typename TypeList>
    inline constexpr auto length_v = length<TypeList>::value;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_LENGTH_H
