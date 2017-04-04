#ifndef SKULL_IS_SAME_TEMPLATE_H
#define SKULL_IS_SAME_TEMPLATE_H


#include <type_traits>


namespace skull::base
{
    template <typename Lhs, typename Rhs>
    struct is_same_template
            : std::false_type
    { };

    template <template <typename...> class TypeList, typename... T, typename... U>
    struct is_same_template<TypeList<T...>, TypeList<U...>>
            : std::true_type
    { };

    template <typename Lhs, typename Rhs>
    inline constexpr auto is_same_template_v = is_same_template<Lhs, Rhs>::value;
} // namespace skull::base


#endif // SKULL_IS_SAME_TEMPLATE_H
