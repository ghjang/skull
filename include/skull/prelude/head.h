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

    // NOTE: This will force the compiler to show 'no_elem_error_tag<...>' text
    //          in the error messages when it's not a 'type_list' or it has no
    //          elements at all.
    template <typename TypeList>
    struct head : no_elem_error_tag<TypeList>
    {
          // NOTE: made this have no 'type' member explicitly.
    };

    template <typename x, typename... xs>
    struct head<TL<x, xs...>> : type_is<x>
    { };

    template <typename TypeList>
    using head_t = typename head<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_HEAD_H
