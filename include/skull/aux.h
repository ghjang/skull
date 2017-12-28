#ifndef SKULL_AUX_H
#define SKULL_AUX_H

#include <type_traits>
#include <iostream>

namespace skull::aux
{
    template <typename T>
    constexpr auto is_basic_output_streamable(T)
        -> decltype(std::declval<std::ostream>().operator << (std::declval<T>()), bool{})
    { return true; }

    // NOTE: This doesn't work as expected.
    /*
    template <typename T>
    constexpr auto is_basic_output_streamable(T)
        -> decltype(std::declval<std::ostream>() << std::declval<T>(), bool{})
    { return true; }
    */

    constexpr bool is_basic_output_streamable(...)
    { return false; }


    template <typename T>
    struct is_basic_output_streamable_
    {
        template <typename U>
        static auto test(U u)
            -> decltype(std::declval<std::ostream>().operator << (u));

        static std::false_type test(...);

        constexpr static auto value
            = !std::is_same_v<
                    std::false_type,
                    decltype(test(std::declval<T>()))
               >;
    };

    template <typename T>
    inline constexpr auto is_basic_output_streamable_v = is_basic_output_streamable_<T>::value;
} // namespace skull::aux


#endif // SKULL_AUX_H
