# Usage Quick Summary

## skull/base

* `append`
  ```
  append_t<TL<int, double>, std::string> ==> TL<int, double, std::string>
  ```
* `as_type_list`
* `at`
* `bind`
* `compose`
* `identity`
* `to_integer_sequence`
* `from_integer_sequence`
* `invoke`
* `is_same_template`
* `prepend`
* `quote`
* `rename_template`
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
