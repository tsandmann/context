
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <tuple>

#include <boost/context/all.hpp>

struct my_exception {
};

boost::context::execution_context<void> f1(boost::context::execution_context<void> && ctx) {
    try {
        for (;;) {
            std::cout << "f1()" << std::endl;
            ctx();
        }
    } catch ( my_exception & e) {
        std::cout << "f1(): my_exception catched" << std::endl;
    }
    return std::move( ctx);
}

void f2() {
    throw my_exception();
}

int main() {
    boost::context::execution_context< void > ctx( f1);
    ctx();
    ctx();
    ctx( boost::context::exec_ontop_arg, f2);

    std::cout << "main: done" << std::endl;

    return EXIT_SUCCESS;
}
