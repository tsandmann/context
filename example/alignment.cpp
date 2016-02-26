#include <iostream>

#include <boost/context/detail/fcontext.hpp>

void context_function( boost::context::detail::transfer_t t) {
    int i = 0;
    boost::context::detail::jump_fcontext( t.fctx, & i);
}

int main( int argc, char* argv[]) {
    std::size_t STACK_SIZE = 1024 * 1024;
    char * stack = new char[STACK_SIZE];
    boost::context::detail::fcontext_t ctx = boost::context::detail::make_fcontext( stack + STACK_SIZE, STACK_SIZE, context_function);
    boost::context::detail::transfer_t t = boost::context::detail::jump_fcontext( ctx, 0);
     std::cout
         << "FCTX: Misalignment = " << (uintptr_t(t.data) & 15) << std::endl;

    return 0;
}
