#ifndef SKULL_BASE_PREPEND_H
#define SKULL_BASE_PREPEND_H


#include "identity.h"
#include "type_list.h"


namespace skull::base
{
    template <typename T, typename TypeList>
    struct prepend
    { };

    template <typename T, typename... xs>
    struct prepend<T, TL<xs...>> : type_is<TL<T, xs...>>
    { };

    template <typename T, typename TypeList>
    using prepend_t = typename prepend<T, TypeList>::type;
} // namespace skull::base


#endif // SKULL_BASE_PREPEND_H
