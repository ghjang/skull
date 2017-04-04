#ifndef SKULL_PRELUDE_TAIL_H
#define SKULL_PRELUDE_TAIL_H


#include "../base/type_list.h"
#include "../base/tag.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::tag::no_elem_error_tag;

    template <typename TypeList>
    struct tail : no_elem_error_tag<TypeList>
    { };

    template <typename x, typename... xs>
    struct tail<TL<x, xs...>> : type_is<TL<xs...>>
    { };

    template <typename TypeList>
    using tail_t = typename tail<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_TAIL_H
