#pragma once

#include <stdint.h>
#include <array>

class GB
{
public:
        GB();

        enum mem_bus_pointers
        {
                CART_ROM0_START = 0x0000,
                CART_ROM1_START = 0x4000,
                V_RAM_START = 0x8000,
                CART_RAM_START = 0xA000,
                W_RAM0_START = 0xC000,
                W_RAM1_START = 0xD000,
                ECHO_RAM_START = 0xE000,
                SPRITE_ATTR_TABLE_START = 0xFE00,
                NOT_USEABLE_START = 0xFEA0,
                IO_REGISTERS_START = 0xFF00,
                HRAM_START = 0xFF80,
                INT_REGISTER = 0xFFFF
        };

private:
        std::array<uint8_t, 8192> vram{};
        std::array<uint8_t, 8192> wram{};
};