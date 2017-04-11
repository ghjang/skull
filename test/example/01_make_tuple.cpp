#include "../catch.hpp"

#include <iostream>
#include "skull/prelude.h"
using namespace skull::prelude;


/**
 * for debugging template
 */
template <typename T>
struct TD;


/**
 * empty base class for class hierarchy generation
 */
struct empty_base
{ };


//==============================================================================
namespace my_tuple::take0
{   
    /**
     * vertical wrap
     */ 
    template <typename T, typename Base>
    struct v_wrap : Base
    {
        T value_;
    };

    template <typename Acc, typename T>
    struct inherit
            : type_is<
                    v_wrap<T, Acc>
              >
    { };

    template <typename T, typename Base>
    auto & my_get(v_wrap<T, Base> & t)
    {
        return t.value_;
    }

    template <typename... T>
    auto my_make_tuple(T &&... args)
    {
        using my_tuple_t = foldl_t<
                                quote<inherit>,         // binary metafunction
                                empty_base,             // left-side accumulation
                                TL<std::decay_t<T>...>
                           >;
        my_tuple_t t{};
        (void) std::initializer_list<int> {
            (my_get<std::decay_t<T>>(t) = std::forward<T>(args), 0)...
        };
        return t;
    }
} // namespace my_tuple::take0


TEST_CASE("my_make_tuple with vertical wrap", "[example]")
{
    using namespace my_tuple::take0;

    auto t = my_make_tuple(10, "abc", 20.0);

    REQUIRE(my_get<int>(t) == 10);
    REQUIRE(std::strcmp(my_get<char const *>(t), "abc") == 0);
    REQUIRE(my_get<double>(t) == 20.0);
}


//==============================================================================
namespace my_tuple::take1
{
    template <typename T>
    struct holder
    {
        T value_;
    };

    /**
     * horizontal wrap
     */ 
    template <typename Holder, typename Base>
    struct h_wrap : Holder, Base
    { };

    template <typename Acc, typename T>
    struct inherit
            : type_is<
                    h_wrap<holder<T>, Acc>
              >
    { };

    template <typename T, typename Base>
    auto & my_get(h_wrap<holder<T>, Base> & t)
    {
        return static_cast<holder<T> &>(t).value_;
    }

    template <typename... T>
    auto my_make_tuple(T &&... args)
    {
        using my_tuple_t = foldl_t<
                                quote<inherit>,         // binary metafunction
                                empty_base,             // left-side accumulation
                                TL<std::decay_t<T>...>
                           >;
        my_tuple_t t{};
        (void) std::initializer_list<int> {
            (my_get<std::decay_t<T>>(t) = std::forward<T>(args), 0)...
        };
        return t;
    }
} // namespace my_tuple::take1


TEST_CASE("my_make_tuple with horizontal wrap", "[example]")
{
    using namespace my_tuple::take1;

    auto t = my_make_tuple(10, "abc", 20.0);

    REQUIRE(my_get<int>(t) == 10);
    REQUIRE(std::strcmp(my_get<char const *>(t), "abc") == 0);
    REQUIRE(my_get<double>(t) == 20.0);
}
