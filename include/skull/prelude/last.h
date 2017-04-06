#ifndef SKULL_PRELUDE_LAST_H
#define SKULL_PRELUDE_LAST_H


#include <type_traits>

#include "../base/identity.h"
#include "../base/type_list.h"
#include "../base/tag.h"
#include "id.h"


namespace skull::prelude
{
    using skull::base::type_is;
    using skull::base::TL;
    using skull::base::tag::no_elem_error_tag;

    namespace detail
    {
        template <typename InitElemIndices>
        struct last_elem_extractor;

        template <std::size_t... i>
        struct last_elem_extractor<std::index_sequence<i...>>
        {
            template <typename T>
            constexpr auto operator () (std::void_t<decltype(i)> *..., T *)
            { return T{}; }
        };

        template <std::size_t... i, typename... T>
        constexpr auto get_last_elem(std::index_sequence<i...>, T... args)
        {
            return last_elem_extractor<std::index_sequence<i...>>{}(&args...);
        }
    } // namespace detail

    template <typename TypeList>
    struct last : no_elem_error_tag<TypeList>
    { };

    template <typename x, typename... xs>
    struct last<TL<x, xs...>>
            : decltype(
                    detail::get_last_elem(
                        std::index_sequence_for<xs...>{},   // it's 'length of TL' - 1.
                        id<x>{}, id<xs>{}...
                    )
              )
    { };

    template <typename TypeList>
    using last_t = typename last<TypeList>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_LAST_H
