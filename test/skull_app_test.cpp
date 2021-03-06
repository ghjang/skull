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

TEST_CASE("count", "[app]")
{
    static_assert(count_v<float, TL<>> == 0);

    static_assert(
        count_v<
            float,
            TL<int, double, long int, std::string>
        > == 0
    );

    static_assert(
        count_v<
            int,
            TL<int, double, long int, std::string>
        > == 1
    );

    static_assert(
        count_v<
            int,
            TL<int, double, long int, std::string, int>
        > == 2
    );
}

TEST_CASE("remove_if", "[app]")
{
    static_assert(
        std::is_same_v<
            TL<double, std::string>,
            remove_if_t<quote<std::is_integral>, TL<int, double, long, std::string>>
        >
    );
}

TEST_CASE("remove", "[app]")
{
    static_assert(
        std::is_same_v<
            TL<double, long, std::string>,
            remove_t<int, TL<int, double, long, std::string, int>>
        >
    );
}

TEST_CASE("unique", "[app]")
{
    static_assert(std::is_same_v<TL<>, unique_t<TL<>>>);
    static_assert(std::is_same_v<TL<int>, unique_t<TL<int>>>);
    static_assert(std::is_same_v<TL<int>, unique_t<TL<int, int>>>);

    static_assert(
        std::is_same_v<
                TL<int, double, std::string>,
                unique_t<TL<int, double, int, std::string, int>>
        >
    );
}
