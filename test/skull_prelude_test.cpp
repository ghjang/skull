#include "catch.hpp"

#include <type_traits>
#include <tuple>
#include <string>


#include "skull/prelude.h"
using namespace skull::prelude;


TEST_CASE("id", "[prelude]")
{
    static_assert(std::is_same_v<int, id_t<int>>);
}

TEST_CASE("length", "[prelude]")
{
    static_assert(0 == length_v<TL<>>);
    static_assert(3 == length_v<TL<int, double, std::string>>);
}

TEST_CASE("head", "[prelude}")
{
    static_assert(
        std::is_same_v<
                int,
                head_t<TL<int, double, std::string>>
        >
    );

    // NOTE: this is an expected compile error
    /*
    static_assert(
        !std::is_same_v<
                int,
                head_t<TL<>>    // empty type list
        >
    );
    */

    // NOTE: this is an expected compile error
    /*
    static_assert(
        !std::is_same_v<
                int,
                head_t<int>    // not a 'type_list'
        >
    );
    */
}
