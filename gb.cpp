#include "gb.h"
#include "cart.h"
#include "memory.h"
#include <iostream>
#include <fstream>
#include <bitset>

using namespace Cart;

GB::GB()
{
}

void GB::LoadCart(std::string filename)
{
        Cart::LoadRom(filename);
}

void GB::LoadBootRom(std::string filename)
{
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (file.is_open())
        {
                std::streampos size = file.tellg();
                char *buffer = new char[size];
                file.seekg(0, std::ios::beg);
                file.read(buffer, size);
                file.close();

                for (long i = 0; i < size; ++i)
                {
                        boot_rom[i] = buffer[i];
                }
                delete[] buffer;
        }
}

void GB::DumpCartHeaderToConsole()
{
        Cart::DumpHeaderToConsole();
}
