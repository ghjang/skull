#include "catch.hpp"

#include "skull/aux.h"
using namespace skull::aux;

#include <sstream>


struct output_streamable_obj
{
    friend std::ostream & operator << (std::ostream & out, output_streamable_obj const&)
    { return out; }
};

struct not_output_streamable_obj { };


TEST_CASE("is_basic_output_streamable metafunctions", "[aux]")
{
    static_assert(is_basic_output_streamable_v<int>);
    static_assert(!is_basic_output_streamable_v<not_output_streamable_obj>);

    static_assert(is_basic_output_streamable(int{}));
    static_assert(!is_basic_output_streamable(not_output_streamable_obj{}));

    std::ostringstream oss;
    oss << output_streamable_obj{};

    // THINK: Is it possible to make is_basic_output_streamable return true for output_streamable_obj?
    static_assert(!is_basic_output_streamable_v<output_streamable_obj>);
    static_assert(!is_basic_output_streamable(output_streamable_obj{}));
}

TEST_CASE("is_output_streamable", "[aux]")
{
    // THINK: Is it possible to make is_output_streamable return false for not_output_streamable_obj?
    static_assert(is_output_streamable_v<output_streamable_obj>);
    static_assert(is_output_streamable_v<not_output_streamable_obj>);

    static_assert(is_output_streamable_v<output_streamable_obj>);
    static_assert(is_output_streamable(output_streamable_obj{}));
}
