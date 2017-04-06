#include "catch.hpp"

#include <type_traits>
#include <string>

#include "skull/app.h"
using namespace skull::app;


TEST_CASE("replace_if", "[app]")
{
    static_assert(
        std::is_same_v<
                TL<int, long long, long>,
                replace_if_t<
                    TL<int, double, long>,
                    quote<std::is_floating_point>,
                    long long
                >
        >
    );
}

TEST_CASE("replace", "[app]")
{
    static_assert(
        std::is_same_v<
                TL<int, long double, long, long double, std::string>,
                replace_t<
                    TL<int, double, long, double, std::string>,
                    double,
                    long double
                >
        >
    );
}
