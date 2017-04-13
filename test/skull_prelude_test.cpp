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

    static_assert(
        !std::is_same_v<
                double,
                head_t<TL<int, double, std::string>>
        >
    );

    static_assert(std::is_same_v<int, head_t<TL<int>>>);

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

    // NOTE: this is an expected compile error
    /*
    static_assert(
        !std::is_same_v<
                int,
                head_t<std::tuple<int, double, std::string>>    // not a 'type_list'
        >
    );
    */
}

TEST_CASE("tail", "[prelude]")
{
    static_assert(
        std::is_same_v<
                TL<double, std::string>,
                tail_t<TL<int, double, std::string>>
        >
    );

    static_assert(
        !std::is_same_v<
                TL<int, double>,
                tail_t<TL<int, double, std::string>>
        >
    );

    static_assert(std::is_same_v<TL<>, tail_t<TL<int>>>);

    // NOTE: This is an expected error.
    /*
    static_assert(
        std::is_same_v<
                TL<double, std::string>,
                tail_t<TL<>>    // empty type list
        >
    );
    */

    // NOTE: This is an expected error.
    /*
    static_assert(
        std::is_same_v<
                TL<double, std::string>,
                tail_t<int>     // not a type_list
        >
    );
    */

    // NOTE: This is an expected error.
    /*
    static_assert(
        std::is_same_v<
                TL<double, std::string>,
                tail_t<std::tuple<int, double, std::string>>    // not a type_list instance
        >
    );
    */
}

TEST_CASE("last", "[prelude]")
{
    static_assert(std::is_same_v<int, last_t<TL<int>>>);
    static_assert(std::is_same_v<int, last_t<TL<float, double, int>>>);
}

TEST_CASE("init", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, init_t<TL<int>>>);
    static_assert(std::is_same_v<TL<int>, init_t<TL<int, float>>>);
    static_assert(std::is_same_v<TL<int, float>, init_t<TL<int, float, double>>>);
}

TEST_CASE("take", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, take_t<0, TL<>>>);
    static_assert(std::is_same_v<TL<>, take_t<0, TL<int>>>);
    static_assert(std::is_same_v<TL<>, take_t<0, TL<int, float>>>);

    static_assert(std::is_same_v<TL<int>, take_t<1, TL<int, float, double>>>);
    static_assert(std::is_same_v<TL<int, float>, take_t<2, TL<int, float, double>>>);
    static_assert(std::is_same_v<TL<int, float, double>, take_t<3, TL<int, float, double>>>);
    
    static_assert(std::is_same_v<TL<int, float, double>, take_t<4, TL<int, float, double>>>);
}

TEST_CASE("concat", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, concat_t<TL<>>>);
    static_assert(std::is_same_v<TL<>, concat_t<TL<TL<>>>>);
    static_assert(std::is_same_v<TL<>, concat_t<TL<TL<>, TL<>>>>);
    static_assert(std::is_same_v<TL<>, concat_t<TL<TL<>, TL<>, TL<>>>>);

    static_assert(
        std::is_same_v<
                TL<int, long int, float, double, std::string>,
                concat_t<TL<TL<int, long int>, TL<float, double>, TL<std::string>>>
        >
    );
}

TEST_CASE("reverse", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, reverse_t<TL<>>>);
    static_assert(std::is_same_v<TL<int>, reverse_t<TL<int>>>);

    static_assert(
        std::is_same_v<
                TL<std::string, double, int>,
                reverse_t<TL<int, double, std::string>>
        >
    );
}

TEST_CASE("sum", "[prelude]")
{
    static_assert(sum_v<TL<>> == 0);

    static_assert(
        sum_v<
            TL<
                std::integral_constant<int, 1>,
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >
        > == 6
    );
}

TEST_CASE("elem", "[prelude]")
{
    static_assert(!elem_v<int, TL<>>);
    static_assert(elem_v<int, TL<int>>);
    static_assert(elem_v<int, TL<double, int, std::string>>);
    static_assert(elem_v<int, TL<double, int, std::string, int>>);
    static_assert(!elem_v<int, TL<double, long int, std::string>>);
}

TEST_CASE("zip", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, zip_t<TL<>, TL<>>>);
    static_assert(std::is_same_v<TL<>, zip_t<TL<int>, TL<>>>);
    static_assert(std::is_same_v<TL<>, zip_t<TL<>, TL<int>>>);

    static_assert(
        std::is_same_v<
                TL<TL<int, int>>,
                zip_t<TL<int>, TL<int>>
        >
    );
    static_assert(
        std::is_same_v<
                TL<
                    TL<int, int>,
                    TL<long, char>,
                    TL<long long, std::string>
                >,
                zip_t<
                    TL<int, long, long long>,
                    TL<int, char, std::string>
                >
        >
    );

    static_assert(
        std::is_same_v<
                TL<
                    TL<int, int>,
                    TL<long, char>
                >,
                zip_t<
                    TL<int, long>,
                    TL<int, char, std::string>
                >
        >
    );
}

TEST_CASE("zipWith", "[prelude]")
{
    struct A { };
    struct B { };
    struct C : A { };
    struct D : A { };
    struct E : A { };
    struct F : C { };

    static_assert(
        std::is_same_v<
            TL<
                std::true_type, std::true_type, std::true_type,
                std::false_type, std::true_type, std::false_type
            >,
            zipWith_t<
                quote<std::is_base_of>,
                TL<A, A, A, B, B, B>,
                TL<F, E, D, C, B, A>
            >
        >
    );
}


// map, transform
// cf.> std::transform, runtime transform
TEST_CASE("map", "[prelude]")
{
    static_assert(
        std::is_same_v<
                TL<int const, double const, std::string const>,
                map_t<
                    quote<std::add_const>,
                    TL<int, double, std::string>
                >
        >
    );

    static_assert(
        std::is_same_v<
                TL<int, double, std::string>,
                map_t<
                    quote<std::remove_const>,
                    TL<int const, double const, std::string const>
                >
        >
    );

    void f();   // NOTE: function forward declaration only for this test case.
    static_assert(
        std::is_same_v<
                TL<int, std::string, double *, void (*) ()>,
                map_t<
                    quote<std::decay>,
                    TL<int const, std::string const &, double [8], decltype(f)>
                >
        >
    );
}

// filter, select
TEST_CASE("filter", "[prelude]")
{
    static_assert(std::is_same_v<TL<>, filter_t<quote<std::is_integral>, TL<>>>);

    static_assert(
        std::is_same_v<
            TL<int, long, short, unsigned>,
            filter_t<
                quote<std::is_integral>,
                TL<int, float, long, double, std::string, short, unsigned>
            >
        >
    );
}


template <int i>
using int_c_t = std::integral_constant<int, i>;

// note that left-side is the accumulation result.
template <typename Acc, typename T>
struct addition_l;

template <int i, int j>
struct addition_l<int_c_t<i>, int_c_t<j>>
        : int_c_t<i + j>
{ };


// note that right-side is the accumulation result.
template <typename T, typename Acc>
struct addition_r;

template <int i, int j>
struct addition_r<int_c_t<i>, int_c_t<j>>
        : int_c_t<i + j>
{ };


// note that left-side is the accumulation result.
template <typename Acc, typename T>
struct subtraction_l;

template <int i, int j>
struct subtraction_l<int_c_t<i>, int_c_t<j>>
        : int_c_t<i - j>
{ };

// note that right-side is the accumulation result.
template <typename T, typename Acc>
struct subtraction_r;

template <int i, int j>
struct subtraction_r<int_c_t<i>, int_c_t<j>>
        : int_c_t<i - j>
{ };


// fold, reduce, accumulation
// cf.> std::accumulate, runtime fold
TEST_CASE("foldl, foldr", "[prelude]")
{
    // addition
    static_assert(
        foldl_t<
            quote<addition_l>,
            int_c_t<0>,
            TL<
                int_c_t<1>,
                int_c_t<2>,
                int_c_t<3>
            >
        >::value == 6
    );

    static_assert(
        foldr_t<
            quote<addition_r>,
            int_c_t<0>,
            TL<
                int_c_t<1>,
                int_c_t<2>,
                int_c_t<3>
            >
        >::value == 6
    );

    // subtraction
    static_assert(
        foldl_t<
            quote<subtraction_l>,
            int_c_t<0>,
            TL<
                int_c_t<1>,
                int_c_t<2>,
                int_c_t<3>
            >
        >::value == -6  // (((0 - 1) - 2) - 3)
    );

    static_assert(
        foldr_t<
            quote<subtraction_r>,
            int_c_t<0>,
            TL<
                int_c_t<1>,
                int_c_t<2>,
                int_c_t<3>
            >
        >::value == 2   // (1 - (2 - (3 - 0)))
    );
}
