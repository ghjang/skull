#ifndef SKULL_PRELUDE_ZIP_H
#define SKULL_PRELUDE_ZIP_H


#include "../base/type_list.h"
#include "../base/identity.h"
#include "../base/prepend.h"
#include "../base/unpack.h"
#include "../base/integer_sequence.h"


namespace skull::prelude
{
    using skull::base::TL;
    using skull::base::type_is;
    using skull::base::prepend;
    using skull::base::unpack_t;
    using skull::base::from_integer_sequence_t;

    template <typename xs, typename ys>
    struct zip;

    template <typename xs, typename ys>
    using zip_t = typename zip<xs, ys>::type;

    template <>
    struct zip<TL<>, TL<>> : type_is<TL<>>
    { };

    template <typename x, typename... xs>
    struct zip<TL<x, xs...>, TL<>> : type_is<TL<>>
    { };

    template <typename y, typename... ys>
    struct zip<TL<>, TL<y, ys...>> : type_is<TL<>>
    { };

    template <typename x, typename... xs, typename y, typename... ys>
    struct zip<TL<x, xs...>, TL<y, ys...>>
            : prepend<
                    TL<x, y>,
                    zip_t<TL<xs...>, TL<ys...>>
              >
    { };
} // namespace skull::prelude


#endif // SKULL_PRELUDE_ZIP_H
