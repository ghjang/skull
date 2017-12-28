#include "catch.hpp"

#include "skull/aux.h"
using namespace skull::aux;

#include <sstream>


struct not_output_streamable_obj { };

struct output_streamable_obj
{
    friend std::ostream & operator << (std::ostream & out, output_streamable_obj const&)
    { return out; }
};

TEST_CASE("is_output_streamable metafunctions", "[aux]")
{
    static_assert(is_output_streamable_v<int>);
    static_assert(is_output_streamable(int{}));

    static_assert(!is_output_streamable_v<not_output_streamable_obj>);
    static_assert(!is_output_streamable(not_output_streamable_obj{}));

    std::ostringstream oss;
    //oss << not_output_streamable_obj{};   // NOTE: This is an expected compile error.
    oss << output_streamable_obj{};

    static_assert(is_output_streamable_v<output_streamable_obj>);
    static_assert(is_output_streamable(output_streamable_obj{}));
}
