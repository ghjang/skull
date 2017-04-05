#ifndef SKULL_BASE_APPEND_H
#define SKULL_BASE_APPEND_H


#include "identity.h"
#include "type_list.h"


namespace skull::base
{
    template <typename TypeList, typename T>
    struct append;

    template <typename... xs, typename T>
    struct append<TL<xs...>, T> : type_is<TL<xs..., T>>
    { };

    template <typename TypeList, typename T>
    using append_t = typename append<TypeList, T>::type;
} // namespace skull::base


#endif // SKULL_BASE_APPEND_H
