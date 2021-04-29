#include "gb.h"
#include <iostream>
#include <chrono>

int main(int argc, char **argv)
{
        std::cout << "hello world\n";

        GB gb;
        gb.LoadCart("roms/tetris.gb");
        gb.cart.DumpHeaderToConsole();

        return 0;
}
