#include "../catch.hpp"

#include <type_traits>
#include <array>
#include <variant>

#include "skull/app.h"


// NOTE: C++17 class template decuction guides is not supported in LLVM 4.0.0.
/*
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
*/

TEST_CASE("C++17 std::variant", "[example]")
{
    std::variant<int, double, std::string> v{ 10 };

    //==========================================================================
    // accessing the internal value with index

    REQUIRE(std::get<0>(v) == 10);

    v = 20.0;
    REQUIRE(std::get<1>(v) == 20.0);

    v = "abc";
    REQUIRE(std::get<2>(v) == "abc");

    bool wasExceptionThrown = false;
    try {
        std::get<0>(v); // '2' is the only valid index at the moment.
    }
    catch (std::bad_variant_access const&) {
        wasExceptionThrown = true;
    }
    REQUIRE(wasExceptionThrown);

    // NOTE: out-of-index results in a compile error.
    //std::get<3>(v);

    //==========================================================================
    // accessing the internal value with type

    v = 10;
    REQUIRE(std::get<int>(v) == 10);

    v = 20.0;
    REQUIRE(std::get<double>(v) == 20.0);

    v = "abc";
    REQUIRE(std::get<std::string>(v) == "abc");

    wasExceptionThrown = false;
    try {
        std::get<int>(v); // 'std::string' is the only valid type at the moment.
    }
    catch (std::bad_variant_access const&) {
        wasExceptionThrown = true;
    }
    REQUIRE(wasExceptionThrown);

    // NOTE: 'long' is not a valid type for 'v' so it results in a compile error.
    //std::get<long>(v);

    //==========================================================================
    // accessing the internal value with visitor

    std::size_t sum = 0;
    auto visitor = [&sum](auto && e) {
                        if constexpr (std::is_arithmetic_v<std::decay_t<decltype(e)>>) {
                            sum += e;
                        } else {
                            sum += e.length();
                        }
                   };
    
    v = "cdefgab"; // 7-char
    std::visit(visitor, v);
    REQUIRE(sum == 7);

    v = 100;
    std::visit(visitor, v);
    REQUIRE(sum == 107);

    // NOTE: A visitor can return a value.
    //       For more information about the rule, refer to the reference:
    //          http://en.cppreference.com/w/cpp/utility/variant/visit
    //       (It's a little bit of confusing at the moment.)

    //==========================================================================
    // NOTE: A variant like following is permitted. Huh??

    // two 'int' types in the variant
    std::variant<int, double, std::string, int> v1;         // it's OK
    //std::variant<int, double, std::string, int> v1{ 10 }; // it's a compile error.

    // This results in a compile error: no viable overloaded '='
    //v1 = 10;

    // These are compiled anyway. Huh??
    std::get<0>(v1);
    std::get<3>(v1);

    // These work.
    v1 = 20.0;
    REQUIRE(std::get<1>(v1) == 20.0);
    v1 = "abc";
    REQUIRE(std::get<2>(v1) == "abc");

    // This is a compile error. Hmm...
    //std::get<int>(v1);
}


template <typename... T>
auto make_variant_array(T &&... args)
{
    using namespace skull::app;

    using tmp_t = replace_if_t<
                        bind_first<
                            quote<std::is_same>,
                            char const *
                        >,
                        std::string,
                        unique_t<TL<std::decay_t<T>...>>
                  >;

    using arr_elem_t = rename_template_t<tmp_t, std::variant>;

    return std::array<arr_elem_t, sizeof...(args)>{
                std::forward<T>(args)...
           };
}

TEST_CASE("make_variant_array", "[example]")
{
    auto varArr = make_variant_array(100, "abc", 200.0);

    static_assert(
        std::is_same_v<
            std::variant<int, std::string, double>,
            decltype(varArr)::value_type
        >
    );

    for (auto & v : varArr) {
        // ...
    }

    REQUIRE(std::visit(
                [](auto e) { return 0; },
                varArr[0]
            ) == 0);

    auto varArr1 = make_variant_array(100, "abc", 200.0, 300, 400);

    static_assert(
        std::is_same_v<
            std::variant<int, std::string, double>,
            decltype(varArr1)::value_type
        >
    );

    for (auto & v : varArr1) {
        // ...
    }
}
