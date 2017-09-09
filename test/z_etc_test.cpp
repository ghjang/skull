#include "catch.hpp"

#include <type_traits>
#include <tuple>
#include <optional>

#include "skull/prelude.h"
using namespace skull::prelude;


//==============================================================================
// functor implemented by using only the built-in C++ features.

namespace
{
    template <template <typename> class F, typename T>
    struct functor;

    template
    <
        template <typename> class F,
        template <typename...> class Container,
        typename... T
    >
    struct functor<F, Container<T...>>
    {
        using type = Container<typename F<T>::type...>;
    };

    template <template <typename> class F, typename T>
    using functor_t = typename functor<F, T>::type;
} // un-named namespace


TEST_CASE("functor", "[etc]")
{
    static_assert(
        std::is_same_v<
            typename functor<std::add_const, std::tuple<int>>::type,
            std::tuple<int const>
        >
    );

    static_assert(
        std::is_same_v<
            typename functor<std::add_const, std::optional<int>>::type,
            std::optional<int const>
        >
    );
}

#define SA_IS_SAME(...) static_assert(std::is_same_v<__VA_ARGS__>)

TEST_CASE("SA_IS_SAME macro", "[etc]")
{
    SA_IS_SAME(functor_t<std::add_const, std::optional<int>>, std::optional<int const>);
}


//==============================================================================
// functor implemented by using skull

namespace
{
    template <typename F, typename T>
    struct functor_s;

    template
    <
        typename F,
        template <typename...> class Container,
        typename... T
    >
    struct functor_s<F, Container<T...>>
            : rename_template<
                    map_t<F, TL<T...>>,
                    Container
              >
    { };

    template <typename F, typename T>
    using functor_s_t = typename functor_s<F, T>::type;
} // un-named namespace

TEST_CASE("functor with skull", "[etc]")
{
    static_assert(
        std::is_same_v<
            functor_s_t<
                quote<std::add_const>,  // mata-function to meta-function class
                std::tuple<int>
            >,
            std::tuple<int const>
        >
    );

    static_assert(
        std::is_same_v<
            functor_s_t<
                quote<std::add_const>,  // mata-function to meta-function class
                std::optional<int>
            >,
            std::optional<int const>
        >
    );

    // NOTE: meta-function composition is possible here~ :)
    static_assert(
        std::is_same_v<
            functor_s_t<
                compose<
                    quote<std::add_pointer>,
                    quote<std::add_const>
                >,
                std::tuple<int>
            >,
            std::tuple<int const *>
        >
    );
}


#if __clang_major__ >= 5

template <typename T>
struct single_type_param
{
    single_type_param(T) { }
};

template <typename T>
single_type_param(T) -> single_type_param<T>;

TEST_CASE("C++17 template deduction guide", "[etc]")
{
    single_type_param s(5);

    // compile errors
    //single_type_param{ 5 };
    //single_type_param(5);
}

#endif // __clang_major__ >= 5
