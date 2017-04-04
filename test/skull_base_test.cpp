#include "catch.hpp"

#include <tuple>

#include "skull/base/is_same_template.h"
using namespace skull::base;


TEST_CASE("is_same_template", "[base]")
{
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int>>);
    static_assert(is_same_template_v<std::tuple<int, int>, std::tuple<int, int, int>>);
    static_assert(!is_same_template_v<std::tuple<int, int>, std::pair<int, int>>);
}
