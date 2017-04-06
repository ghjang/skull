#ifndef SKULL_PRELUDE_INIT_H
#define SKULL_PRELUDE_INIT_H


#include <type_traits>

#include "../base/type_list.h"
#include "../base/tag.h"
#include "take.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::tag::no_elem_error_tag;

    template <typename TypeList>
    struct init : no_elem_error_tag<TypeList>
    { };

    template <typename x, typename... xs>
    struct init<TL<x, xs...>>
            : take<sizeof...(xs), TL<x, xs...>>
    { };

    template <typename TypeList>
    using init_t = typename init<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_INIT_H
