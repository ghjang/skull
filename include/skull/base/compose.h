#ifndef SKULL_BASE_COMPOSE_H
#define SKULL_BASE_COMPOSE_H


#include "type_list.h"
#include "quote.h"
#include "invoke.h"
#include "../prelude/foldr.h"
#include "../prelude/last.h"
#include "../prelude/init.h"


namespace skull::base
{
    /**
     * The result is a composed metafunction class.
     *
     * You can think it as a some kind of metafunction class pipe-lining.
     *
     * @tparam f metafunction classes
     */
    template <typename... f>
    struct compose
    {
        static_assert(sizeof...(f) > 0, "no metafunction classes to compose.");

        template <typename... xs>
        struct lambda
                : prelude::foldr<
                        quote<invoke>,                  // binary function
                        invoke_t<                       // right-side accumulation
                            prelude::last_t<TL<f...>>,
                            xs...
                        >,
                        prelude::init_t<TL<f...>>
                  >
        { };
    };
} // namespace skull::base


#endif // SKULL_BASE_COMPOSE_H
