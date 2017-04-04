#ifndef SKULL_BASE_TAG_H
#define SKULL_BASE_TAG_H


#include "type_list.h"
#include "is_same_template.h"


namespace skull::base::tag
{
    using skull::base::TL;
    using skull::base::is_same_template_v;

    template <typename TypeList>
    struct no_elem_error_tag
    {
        static_assert(is_same_template_v<TL<>, TypeList>, "not a type_list instance");
    };

    template <typename... xs>
    struct no_elem_error_tag<TL<xs...>>
    {
        static_assert(sizeof...(xs) > 0, "no type elements in the type list");
    };
} // namespace skull::base::tag


#endif // SKULL_BASE_TAG_H
