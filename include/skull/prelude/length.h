#ifndef SKULL_PRELUDE_LENGTH_H
#define SKULL_PRELUDE_LENGTH_H


#include <type_traits>

#include "../base/tag.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::tag::no_elem_error_tag;

    // NOTE: This will force the compiler to show 'no_elem_error_tag<...>' text
    //          in the error messages when it's not a 'type_list' or it has no
    //          elements at all.
    template <typename TypeList>
    struct length : no_elem_error_tag<TypeList>
    {
        // NOTE: made this have no 'type' member explicitly.
    };

    template <typename... xs>
    struct length<TL<xs...>>
            : std::integral_constant<std::size_t, sizeof...(xs)>
    { };

    template<typename TypeList>
    inline constexpr auto length_v = length<TypeList>::value;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_LENGTH_H
