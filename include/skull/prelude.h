#ifndef SKULL_PRELUDE_H
#define SKULL_PRELUDE_H


#include "base.h"


#include "prelude/id.h"
#include "prelude/length.h"
#include "prelude/head.h"
#include "prelude/tail.h"
#include "prelude/last.h"
#include "prelude/init.h"
#include "prelude/map.h"        // map higher-order metafunction
#include "prelude/foldl.h"      // foldl higher-order metafunction
#include "prelude/foldr.h"      // foldr higher-order metafunction
#include "prelude/concat.h"
#include "prelude/reverse.h"
#include "prelude/sum.h"
#include "prelude/elem.h"
#include "prelude/filter.h"     // filter higher-order metafunction
#include "prelude/not.h"
#include "prelude/take.h"
#include "prelude/zip.h"
#include "prelude/replicate.h"
#include "prelude/max.h"


namespace skull::prelude
{
    using namespace skull::base;
} // namespace skull::app


#endif // SKULL_PRELUDE_H
