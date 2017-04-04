#ifndef SKULL_TYPE_LIST_H
#define SKULL_TYPE_LIST_H


namespace skull::base
{
    template <typename...>
    struct type_list
    { };

    template <typename... T>
    using TL = type_list<T...>;
} // namespace skull::base


#endif // SKULL_TYPE_LIST_H
