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
            std::integral_constant<std::size_t, 30>
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
  ```
  unpack_t<std::tuple, TL<int, double>> ==> std::tuple<int, double>
  ```

## skull/prelude

* `concat`
  ```
  concat_t<TL<int>, TL<double>, TL<long, char>> ==> TL<int, double, long, char>
  ```
* `elem`
  ```
  elem_v<int, TL<int, double, std::string>> ==> true
  elem_v<char, TL<int, double, std::string>> ==> false
  ```
* `filter`
  ```
  filter_t<quote<std::is_integral>, TL<int, double, long, float>> ==> TL<int, long>
  ```
* `foldl`
* `foldr`
* `head`
  ```
  head_t<TL<int, double, std::string>> ==> int
  ```
* `id`
  ```
  id_t<int> ==> int
  ```
* `init`
  ```
  init_t<TL<int, double, std::string>> ==> TL<int, double>
  ```
* `last`
  ```
  last_t<TL<int, double, std::string>> ==> std::string
  ```
* `length`
  ```
  length_v<TL<int, double, std::string> ==> 3
  ```
* `map`
  ```
  map_t<quote<std::add_pointer>, TL<int, double, char>> ==> TL<int *, double *, char *>
  ```
* `not_`
  ```
  not_<std::true_type> ==> std::false_type
  ```
* `reverse`
  ```
  reverse_t<TL<int, double, std::string>> ==> TL<std::string, double, int>
  ```
* `sum`
  ```
  sum_v<
    std::integral_constant<std::size_t, 10>,
    std::integral_constant<std::size_t, 20>,
    std::integral_constant<std::size_t, 30>
  >

  ==> 60
  ```
* `tail`
  ```
  tail_t<TL<int, double, std::string>> ==> TL<double, std::string>
  ```
* `take`
  ```
  take_c_t<2, TL<int, double, std::string>> ==> TL<int, double>
  ```
* `zip`
  ```
  zip_t<
    TL<int, double, std::string>,
    TL<char, char, char>
  >

  ==> TL<
        TL<int, char>,
        TL<double, char>,
        TL<std::string, char>
      >

  zipWith_t<
    quote<std::is_same>,
    TL<int, double, std::string>,
    TL<int, float, char>
  >

  ==> TL<std::true_type, std::false_type, std::false_type>
  ```

## skull/app

* `count`
  ```
  count_v<int, TL<int, char, double, int>> ==> 2
  ```
* `remove`
  ```
  remove_t<int, TL<char, short, int, double>> ==> TL<char, short, double>

  remove_if_t<
        quote<std::is_integral>,
        TL<char, short, int, double>
  >
  
  ==> TL<double>
  ```
* `replace`
  ```
  replace_t<int, long, TL<int, long, double>> ==> TL<long, long, double>

  replace_if_t<
        quote<std::is_integral>,
        int,
        TL<int, long, double>
  >
  
  ==> TL<int, int, double>
  ```
* `unique`
  ```
  unique_t<TL<int, int, double, double, std::string>> ==> TL<int, double, std::string>
  ```

---

## metafunctions implemented on top of the fold metafuncions, foldl or foldr

* `concat`
* `filter`
* `reverse`
* `take`
* `unique`
