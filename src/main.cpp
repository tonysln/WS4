#include <iostream>
#include "WS4.h"


int main()
{
    // Print version info
    #ifdef __clang__
    std::cout << "Clang Version: ";
    std::cout << __clang__ << std::endl;
    std::cout << "LLVM Version: ";
    std::cout << __llvm__ << std::endl;
    #else
    std::cout << "GCC Version: ";
    std::cout << __VERSION__ << std::endl;
    #endif


    ws4::WS4 ws4Engine;



    return ws4Engine.runLoop();
};
