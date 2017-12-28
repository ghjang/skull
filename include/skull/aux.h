#ifndef SKULL_AUX_H
#define SKULL_AUX_H

#include <type_traits>
#include <iostream>

namespace skull::aux
{
    template <typename T, typename = void>
    struct is_output_streamable_ : std::false_type
    { };

    template <typename T>
    struct is_output_streamable_<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type
    { };

    template <typename T>
    inline constexpr auto is_output_streamable_v = is_output_streamable_<T>::value;

    template <typename T>
    constexpr auto is_output_streamable(T)
    { return is_output_streamable_v<std::decay_t<T>>; }
} // namespace skull::aux


#endif // SKULL_AUX_H
