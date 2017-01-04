
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>

#include <boost/context/continuation.hpp>

namespace ctx = boost::context;

ctx::continuation foo( ctx::continuation && c) {
    for (;;) {
        std::cout << "then I say ...\n";
        c = c();
    }
    return std::move( c);
}

int main() {
    std::cout << "hello world\n";
    ctx::continuation c = ctx::callcc( foo);
    for (;;) {
        std::cout << "then you say ...\n";
        c = c();
    }
    std::cout << "main: done" << std::endl;
    return EXIT_SUCCESS;
}
