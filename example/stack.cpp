#include <cstdint>
#include <emmintrin.h>
#include <iostream>

#include <boost/context/all.hpp>

void context_function( boost::context::detail::transfer_t t) {
    volatile float __attribute__ ((vector_size(16))) xmm;
    boost::context::detail::jump_fcontext( t.fctx, (void*)&xmm);
}

int main( int argc, char* argv[]) {
    const std::size_t STACK_SIZE = 1024 * 1024;
    const auto stack = new char[STACK_SIZE];
    const auto ctx = boost::context::detail::make_fcontext(stack + STACK_SIZE, STACK_SIZE, context_function);
    const auto t = boost::context::detail::jump_fcontext(ctx, nullptr);

    std::cout
        << "Address      = " << t.data << std::endl
        << "Misalignment = " << (uintptr_t(t.data) & 15) << std::endl;

    return 0;
}
