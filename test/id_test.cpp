#include "catch.hpp"

#include <type_traits>

#include "skull/prelude/id.h"


TEST_CASE("id", "[prelude]")
{
    using namespace skull::prelude;

    static_assert(std::is_same_v<int, id_t<int>>);
}
