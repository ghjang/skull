#ifndef SKULL_BASE_INTEGER_SEQUENCE_H
#define SKULL_BASE_INTEGER_SEQUENCE_H


#include "type_list.h"
#include "identity.h"


namespace skull::base
{
    template <typename IntegralConstantList>
    struct to_integer_sequence;

    template <typename T, T... i>
    struct to_integer_sequence<TL<std::integral_constant<T, i>...>>
            : type_is<std::integer_sequence<T, i...>>
    { };

    template <typename IntegralConstantList>
    using to_integer_sequence_t = typename to_integer_sequence<IntegralConstantList>::type;


    template <typename IntegerSequence>
    struct from_integer_sequence;

    template <typename T, T... i>
    struct from_integer_sequence<std::integer_sequence<T, i...>>
            : type_is<TL<std::integral_constant<T, i>...>>
    { };

    template <typename IntegerSequence>
    using from_integer_sequence_t = typename from_integer_sequence<IntegerSequence>::type;
} // namespace skull::base


#endif // SKULL_BASE_INTEGER_SEQUENCE_H
