#include <cstdint>
#include <iostream>

#include <boost/context/all.hpp>

#if defined(__i386)
# define ACQUIRE_ESP(esp) __asm__ __volatile__("mov %%esp, %0" : "=r"(esp) ::"memory");
#elif defined(__x86_64__)
# define ACQUIRE_ESP(esp) __asm__ __volatile__("mov %%rsp, %0" : "=r"(esp) ::"memory");
#else
# error "Unsupported arch"
#endif

void context_function( boost::context::detail::transfer_t t) {
    void * esp = nullptr;
    ACQUIRE_ESP( esp);
    boost::context::detail::jump_fcontext( t.fctx, esp);
}

int main( int argc, char* argv[]) {
    void * main_esp = nullptr;
    ACQUIRE_ESP( main_esp);

    const std::size_t STACK_SIZE = 1024 * 1024;
    const auto stack = new char[STACK_SIZE];
    const auto ctx = boost::context::detail::make_fcontext( stack + STACK_SIZE, STACK_SIZE, context_function);
    const auto t = boost::context::detail::jump_fcontext( ctx, nullptr);

    std::cout
        << "MAIN: ESP          = " << main_esp << std::endl
        << "MAIN: Misalignment = " << (uintptr_t(main_esp) & 15) << std::endl
        << "FCTX: ESP          = " << t.data << std::endl
        << "FCTX: Misalignment = " << (uintptr_t(t.data) & 15) << std::endl;

    return 0;
}
