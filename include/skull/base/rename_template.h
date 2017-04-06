#ifndef SKULL_BASE_RENAME_TEMPLATE_H
#define SKULL_BASE_RENAME_TEMPLATE_H


#include "identity.h"


namespace skull::base
{
    template <typename TypeList, template <typename...> class T>
    struct rename_template;

    template
    <
        template <typename...> class TypeList,
        typename... xs, 
        template <typename...> class T
    >
    struct rename_template<TypeList<xs...>, T>
            : type_is<T<xs...>>
    { };

    template <typename TypeList, template <typename...> class T>
    using rename_template_t = typename rename_template<TypeList, T>::type;
} // namespace skull::base


#endif // SKULL_BASE_RENAME_TEMPLATE_H
