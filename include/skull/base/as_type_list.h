#ifndef SKULL_BASE_AS_TYPE_LIST_H
#define SKULL_BASE_AS_TYPE_LIST_H


#include "type_list.h"


namespace skull::base
{
    /**
     * A metafunction which just wraps the template parameters as the type list
     */
    template <typename... T>
    struct as_type_list
    {
        using type = TL<T...>;
    };

    template <typename... T>
    using as_type_list_t = typename as_type_list<T...>::type;
} // namespace skull::base


#endif // SKULL_BASE_AS_TYPE_LIST_H
