#ifndef SKULL_PRELUDE_H
#define SKULL_PRELUDE_H


#include "base/identity.h"
#include "base/type_list.h"
#include "base/quote.h"
#include "base/invoke.h"
#include "base/bind.h"

#include "base/at.h"            // xs !! n
#include "base/append.h"        // [xs] ++ [new_element]
#include "base/prepend.h"       // new_element : [xs]

#include "prelude/id.h"
#include "prelude/length.h"
#include "prelude/head.h"
#include "prelude/tail.h"
#include "prelude/map.h"
#include "prelude/foldl.h"
#include "prelude/foldr.h"
#include "prelude/concat.h"
#include "prelude/reverse.h"
#include "prelude/sum.h"
#include "prelude/elem.h"


#endif // SKULL_PRELUDE_H
