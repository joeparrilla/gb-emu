#pragma once

#include <stdint.h>

namespace Memory
{
        uint8_t Read(uint16_t address);
        void Write(uint16_t address, uint8_t data);

        enum BUS_POINTERS
        {
                CART_ROM0_START = 0x0000,
                CART_ROM0_END = 0x3FFF,
                CART_ROM1_START = 0x4000,
                CART_ROM1_END = 0x7FFF,
                VRAM_START = 0x8000,
                VRAM_END = 0x9FFF,
                EX_RAM_START = 0xA000,
                EX_RAM_END = 0xBFFF,
                W_RAM0_START = 0xC000,
                W_RAM0_END = 0xCFFF,
                W_RAM1_START = 0xD000,
                W_RAM1_END = 0xDFFF,
                ECHO_RAM_START = 0xE000,
                ECHO_RAM_END = 0xFDFF,
                OAM_START = 0xFE00,
                OAM_END = 0xFEFF,
                IO_START = 0xFF00,
                IO_END = 0xFF7F,
                HRAM_START = 0xFF80,
                HRAM_END = 0xFFFE,
                INT_REGISTER = 0xFFFF
        };
};