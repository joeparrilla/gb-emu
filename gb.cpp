#include "gb.h"

GB::GB()
{
}

void GB::LoadCart(std::string filename)
{
        cart.LoadRom(filename);
}