#include "catch.hpp"

#include <tuple>
#include <string>

#include "skull/base/at.h"
#include "skull/base/append.h"
#include "skull/base/is_same_template.h"
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
}

TEST_CASE("is_same_template", "[base]")
{
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int>>);
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int, int>>);
    static_assert(!is_same_template_v<std::tuple<int, int>, std::pair<int, int>>);
}
