#include "../catch.hpp"

#include <type_traits>
#include <array>
#include <variant>

#include "skull/app.h"


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

    auto varArr1 = make_variant_array(100, "abc", 200.0, 300, 400);

    static_assert(
        std::is_same_v<
            std::variant<int, std::string, double>,
            decltype(varArr1)::value_type
        >
    );
}
