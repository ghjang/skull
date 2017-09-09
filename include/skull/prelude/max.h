#ifndef SKULL_PRELUDE_MAX_H
#define SKULL_PRELUDE_MAX_H


#include <type_traits>


namespace skull::prelude
{
    template <typename T, typename U>
    struct max
            : std::conditional<
                    (sizeof(T) >= sizeof(U)),   // if different types have same size,
                    T,                          // then return the first one.
                    U
              >
    { };
    
    template <typename T, T t, typename U, U u>
    struct max<std::integral_constant<T, t>, std::integral_constant<U, u>>
            : std::integral_constant<
                        std::common_type_t<T, U>,
                        (t > u) ? t : u
              >
    { };

    template <typename T, typename U>
    using max_t = typename max<T, U>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_MAX_H
