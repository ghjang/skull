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
                    quote<std::is_floating_point>,
                    long long,
                    TL<int, double, long>
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
                    double,
                    long double,
                    TL<int, double, long, double, std::string>
                >
        >
    );
}

TEST_CASE("count_if", "[app]")
{
    static_assert(
        count_if_v<
            quote<std::is_integral>,
            TL<int, double, long int, std::string>
        > == 2
    );
}
