#ifndef SKULL_BASE_APPEND_H
#define SKULL_BASE_APPEND_H


#include <type_traits>

#include "identity.h"
#include "type_list.h"
#include "invoke.h"


namespace skull::base
{
    /**
     * @tparam TypeList target type list
     * @tparam T new type to add
     */
    template <typename TypeList, typename T>
    struct append;

    template <typename... xs, typename T>
    struct append<TL<xs...>, T> : type_is<TL<xs..., T>>
    { };

    template <typename TypeList, typename T>
    using append_t = typename append<TypeList, T>::type;

    /**
     * @tparam TypeList target type list
     * @tparam T new type to add
     * @tparam UnaryPredicate unary predicate
     */
    template <typename TypeList, typename T, typename UnaryPredicate>
    struct append_if;

    template <typename... xs, typename T, typename p>
    struct append_if<TL<xs...>, T, p>
            : std::conditional<
                    invoke_v<p, T>,
                    TL<xs..., T>,
                    TL<xs...>
              >
    { };

    template <typename TypeList, typename T, typename UnaryPredicate>
    using append_if_t = typename append_if<TypeList, T, UnaryPredicate>::type;
} // namespace skull::base


#endif // SKULL_BASE_APPEND_H
