#ifndef SKULL_PRELUDE_HEAD_H
#define SKULL_PRELUDE_HEAD_H


#include "../base/identity.h"
#include "../base/type_list.h"
#include "../base/tag.h"


namespace skull::prelude
{
    using skull::base::type_is;
    using skull::base::TL;
    using skull::base::tag::no_elem_error_tag;

    template <typename TypeList>
    struct head : no_elem_error_tag<TypeList>
    { };

    template <typename x, typename... xs>
    struct head<TL<x, xs...>> : type_is<x>
    { };

    template <typename TypeList>
    using head_t = typename head<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_HEAD_H
