#include "catch.hpp"

#include <tuple>
#include <string>

#include "skull/base/quote.h"
#include "skull/base/bind.h"
#include "skull/base/invoke.h"
#include "skull/base/at.h"
#include "skull/base/append.h"
#include "skull/base/prepend.h"
#include "skull/base/is_same_template.h"
#include "skull/base/compose.h"
using namespace skull::base;


TEST_CASE("at", "[base]")
{
    using tl = TL<int, float, double, std::string>;

    static_assert(
        std::is_same_v<int, at_t<std::integral_constant<std::size_t, 0>, tl>>
    );
    static_assert(
        std::is_same_v<std::string, at_t<std::integral_constant<std::size_t, 3>, tl>>
    );

    static_assert(std::is_same_v<int, at_c_t<0, tl>>);
    static_assert(std::is_same_v<std::string, at_c_t<3, tl>>);
}

TEST_CASE("append", "[base]")
{
    static_assert(
        std::is_same_v<
                TL<int, float, double, std::string>,
                append_t<TL<int, float, double>, std::string>
        >
    );

    static_assert(
        std::is_same_v<
                TL<int, float, double>,
                append_if_t<
                    TL<int, float, double>,
                    std::string,
                    quote<std::is_integral>
                >
        >
    );

    static_assert(
        std::is_same_v<
                TL<int, float, double, long>,
                append_if_t<
                    TL<int, float, double>,
                    long,
                    quote<std::is_integral>
                >
        >
    );
}

TEST_CASE("prepend", "[base]")
{
    static_assert(
        std::is_same_v<
                TL<std::string, int, float, double>,
                prepend_t<std::string, TL<int, float, double>>
        >
    );

    static_assert(
        std::is_same_v<
                TL<int, float, double>,
                prepend_if_t<
                    quote<std::is_integral>,
                    std::string,
                    TL<int, float, double>
                >
        >
    );

    static_assert(
        std::is_same_v<
                TL<long, int, float, double>,
                prepend_if_t<
                    quote<std::is_integral>,
                    long,
                    TL<int, float, double>
                >
        >
    );
}

TEST_CASE("is_same_template", "[base]")
{
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int>>);
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int, int>>);
    static_assert(!is_same_template_v<std::tuple<int, int>, std::pair<int, int>>);
}

TEST_CASE("compose", "[base]")
{
    using a_t = compose<
                    quote<std::add_const>,
                    quote<std::add_pointer>
                >;
    static_assert(
        std::is_same_v<
                int * const,
                invoke_t<a_t, int>
        >
    );

    using b_t = compose<
                    quote<std::add_pointer>,
                    quote<std::add_const>
                >;
    static_assert(
        std::is_same_v<
                int const *,
                invoke_t<b_t, int>
        >
    );

    using c_t = compose<
                    bind_first<
                        quote<std::is_same>,
                        int const *
                    >,
                    quote<std::add_pointer>,
                    quote<std::add_const>
                >;
    static_assert(invoke_v<c_t, int>);
    static_assert(!invoke_v<c_t, double>);

    //==========================================================================
    using f_t = compose<
                    bind_first<
                        quote<std::is_same>,
                        char *
                    >,
                    quote<std::remove_const>
                >;

    static_assert(!invoke_v<f_t, std::decay_t<decltype("abc")>>);

    // NOTE: std::decay_t<decltype("abc")> results in 'char const *'.
    //          The result type doesn't have top-level qualifiers,
    //          so std::remove_const doesn't remove 'const' from it at all.
    //          refer to the following reference for more information:
    //              http://en.cppreference.com/w/cpp/types/remove_cv

    using g_t = compose<
                    bind_first<
                        quote<std::is_same>,
                        char const *
                    >,
                    quote<std::remove_const>
                >;

    static_assert(invoke_v<g_t, std::decay_t<decltype("abc")>>);
}
