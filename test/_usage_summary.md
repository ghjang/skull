# Usage Quick Summary

## skull/base

* `append`
  ```
  append_t<TL<int, double>, std::string> ==> TL<int, double, std::string>
  ```
* `as_type_list`
  ```
  as_type_list_t<int, double> ==> TL<int, double>
  ```
* `at`
  ```
  at_c_t<1, TL<int, double, std::string>> ==> double
  ```
* `bind`
* `compose`
* `identity`
  ```
  identity<int> ==> int
  type_is<int> ==> identity<int> ==> int
  ```
* `to_integer_sequence`
  ```
  to_integer_sequence<
        TL<
            std::integral_constant<std::size_t, 10>,
            std::integral_constant<std::size_t, 20>,
            std::integral_constant<std::size_t, 30>,
        >
  >

  ==> std::integer_sequence<std::size_t, 10, 20, 30>
  ```
* `from_integer_sequence`
  ```
  from_integer_sequence<
        std::integer_sequence<std::size_t, 10, 20, 30>
  >

  ==>   TL<
            std::integral_constant<std::size_t, 10>,
            std::integral_constant<std::size_t, 20>,
            std::integral_constant<std::size_t, 30>,
        >
  ```
* `invoke`
* `is_same_template`
  ```
  is_same_template_v<std::tuple<int, double>, std::tuple<int>> ==> true
  is_same_template_v<std::tuple<int, double>, std::pair<int>> ==> false
  ```
* `prepend`
  ```
  prepend_t<int, TL<double, std::string>> ==> TL<int, double, std::string>
  ```
* `quote`
* `rename_template`
  ```
  rename_template_t<TL<int, double> std::tuple> ==> std::tuple<int, double>
  ```
* `unpack`

## skull/prelude

* `concat`
* `elem`
* `filter`
* `foldl`
* `foldr`
* `head`
* `id`
* `init`
* `last`
* `length`
* `map`
* `not_`
* `reverse`
* `sum`
* `tail`
* `take`
* `zip`

## skull/app

* `count`
* `remove`
* `replace`
* `unique`

---

## metafunctions implemented on top of the fold metafuncions, foldl or foldr

* `concat`
* `filter`
* `reverse`
* `take`
* `unique`
