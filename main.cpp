#include "gb.h"
#include <iostream>
#include <chrono>

int main(int argc, char **argv)
{
        GB gb;
        gb.LoadCart("roms/tetris.gb");
        gb.DumpCartHeaderToConsole();

        return 0;
}
