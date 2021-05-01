#pragma once

#include <array>
#include <stdint.h>

namespace RAM
{
        extern std::array<uint8_t, 8192> wram;
        extern std::array<uint8_t, 127> hram;
        extern std::array<uint8_t, 7680> eram;
        void WriteWRam(uint8_t address, uint8_t data);
        uint8_t ReadWRam(uint8_t address);
        void WriteHRam(uint8_t address, uint8_t data);
        uint8_t ReadHRam(uint8_t address);
        void WriteERam(uint8_t address, uint8_t data);
        uint8_t ReadERam(uint8_t address);
}