#ifndef SKULL_PRELUDE_ID_H
#define SKULL_PRELUDE_ID_H


#include "../base/identity.h"


namespace skull::prelude
{
    using skull::base::type_is;

    template <typename T>
    struct id : type_is<T>
    {
        constexpr T val() const;    // NOTE: declaration only.
    };

    template <typename T>
    using id_t = typename id<T>::type;
} // namespace skull::prelude


#endif // SKULL_PRELUDE_ID_H
