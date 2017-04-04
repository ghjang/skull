#ifndef SKULL_PRELUDE_MAP_H
#define SKULL_PRELUDE_MAP_H


#include "../base/identity.h"
#include "../base/type_list.h"
#include "../base/invoke.h"


namespace skull::prelude
{
    using skull::base::type_is;
    using skull::base::TL;
    using skull::base::quote;
    using skull::base::invoke;
    using skull::base::invoke_t;

    /**
     * @tparam f metafunction class
     */
    template <typename f, typename TypeList>
    struct map;

    template <typename f, typename... xs>
    struct map<f, TL<xs...>>
            : type_is<
                    TL<invoke_t<f, xs>...>
              >
    { };

    template <typename f, typename TypeList>
    using map_t = typename map<f, TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_MAP_H
