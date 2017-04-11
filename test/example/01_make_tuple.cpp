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

    // t's type
    /*
    v_wrap<
        double,
        v_wrap<
            const char *,
            v_wrap<
                int,
                empty_base
            >
        >
    >
    */

    // Accessing the values directly

    // the first int
    REQUIRE((static_cast<v_wrap<int, empty_base> &>(t).value_ == 10));

    // the second char const *
    REQUIRE(std::strcmp(
                    static_cast<
                        v_wrap<
                            char const *,
                            v_wrap<
                                int,
                                empty_base
                            >
                        > &
                    >(t).value_,
                    "abc"
            ) == 0);

    // the third double
    REQUIRE((static_cast<
                v_wrap<
                    double,
                    v_wrap<
                        const char *,
                        v_wrap<
                            int,
                            empty_base
                        >
                    >
                > &
             >(t).value_ == 20.0));

    // NOTE: the bottom-most value_ member is looked up.
    REQUIRE(t.value_ == 20.0);
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

    // t's type
    /*
    h_wrap<
        holder<double>,
        h_wrap<
            holder<const char *>,
            h_wrap<
                holder<int>,
                empty_base
            >
        >
    >
    */

    // Accessing the values directly

    // the first int
    REQUIRE(static_cast<holder<int> &>(t).value_ == 10);

    // the second char const *
    REQUIRE(std::strcmp(static_cast<holder<char const *> &>(t).value_, "abc") == 0);

    // the third double
    REQUIRE(static_cast<holder<double> &>(t).value_ == 20.0);

    // NOTE: This expression is now a compile error:
    //          'member 'value_' found in multiple base classes of different types',
    //          'member found by ambiguous name lookup'
    //t.value_;
}


//==============================================================================
namespace my_tuple::take2
{   
    /**
     * vertical wrap
     */ 
    template <typename T, typename Base>
    struct v_wrap : Base
    {
        using Base::get;

        using base_index_t = typename Base::index_t;
        using index_t = std::integral_constant<std::size_t, base_index_t::value + 1>;

        auto & get(index_t)
        { return value_; }

        T value_;
    };

    template <typename T>
    struct v_wrap<T, empty_base>
    {
        using index_t = std::integral_constant<std::size_t, 0>;

        auto & get(index_t)
        { return value_; }

        T value_;
    };

    template <typename Acc, typename T>
    struct inherit
            : type_is<
                    v_wrap<T, Acc>
              >
    { };

    template <std::size_t i, typename T, typename Base>
    auto & my_get(v_wrap<T, Base> & t)
    {
        return t.get(std::integral_constant<std::size_t, i>{});
    }

    template <std::size_t... i, typename... T>
    auto my_make_tuple_impl(std::index_sequence<i...>, T &&... args)
    {
        using my_tuple_t = foldl_t<
                                quote<inherit>,         // binary metafunction
                                empty_base,             // left-side accumulation
                                TL<std::decay_t<T>...>
                           >;

        my_tuple_t t{};
        (void) std::initializer_list<int> {
            (my_get<i>(t) = std::forward<T>(args), 0)...
        };
        return t;
    }

    template <typename... T>
    auto my_make_tuple(T &&... args)
    {
        return my_make_tuple_impl(
                    std::index_sequence_for<T...>{},
                    std::forward<T>(args)...
               );
    }
} // namespace my_tuple::take2


TEST_CASE("my_make_tuple with vertical wrap, take2, indexed element access", "[example]")
{
    using namespace my_tuple::take2;

    auto t = my_make_tuple(10, "abc", 20.0);

    REQUIRE(my_get<0>(t) == 10);
    REQUIRE(std::strcmp(my_get<1>(t), "abc") == 0);
    REQUIRE(my_get<2>(t) == 20.0);
}
