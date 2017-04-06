#ifndef SKULL_BASE_PREPEND_H
#define SKULL_BASE_PREPEND_H


#include <type_traits>

#include "identity.h"
#include "type_list.h"
#include "invoke.h"


namespace skull::base
{
    /**
     * @tparam T new type to add
     * @tparam TypeList target type list
     */
    template <typename T, typename TypeList>
    struct prepend;

    template <typename T, typename... xs>
    struct prepend<T, TL<xs...>> : type_is<TL<T, xs...>>
    { };

    template <typename T, typename TypeList>
    using prepend_t = typename prepend<T, TypeList>::type;


    /**
     * @tparam UnaryPredicate unary predicate
     * @tparam T new type to add
     * @tparam TypeList target type list
     */
     template <typename UnaryPredicate, typename T, typename TypeList>
     struct prepend_if;

     template <typename p, typename T, typename... xs>
     struct prepend_if<p, T, TL<xs...>>
                : std::conditional<
                        invoke_v<p, T>,
                        TL<T, xs...>,
                        TL<xs...>     
                  >
     { };

    /**
     * @tparam UnaryPredicate unary predicate
     * @tparam T new type to add
     * @tparam TypeList target type list
     */
     template <typename UnaryPredicate, typename T, typename TypeList>
     using prepend_if_t = typename prepend_if<UnaryPredicate, T, TypeList>::type;
} // namespace skull::base


#endif // SKULL_BASE_PREPEND_H
