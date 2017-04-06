#ifndef SKULL_PRELUDE_NOT_H
#define SKULL_PRELUDE_NOT_H


#include <type_traits>


namespace skull::prelude
{
    /**
     * NOTE: 'not' is a C++ keyword, which is an alternative for '!' operator.
     */
    template <typename Boolean>
    struct not_;

    template <typename T, T i>
    struct not_<std::integral_constant<T, i>>
            : std::integral_constant<T, !i>
    { };
} // namespace skull::prelude


#endif // SKULL_PRELUDE_NOT_H
