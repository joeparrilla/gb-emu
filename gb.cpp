#include "gb.h"
#include <iostream>
#include <fstream>
#include <bitset>

GB::GB()
{
}

void GB::LoadCart(std::string filename)
{
        cart.LoadRom(filename);
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