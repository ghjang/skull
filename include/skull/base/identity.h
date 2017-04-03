#ifndef SKULL_BASE_IDENTITY_H
#define SKULL_BASE_IDENTITY_H


namespace skull::base
{
    template <typename T>
    struct identity
    {
        using type = T;
    };


    template <typename T>
    using type_is = identity<T>;
} // namespace skull::base


#endif // SKULL_BASE_IDENTITY_H
