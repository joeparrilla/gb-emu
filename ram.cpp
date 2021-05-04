#include "ram.h"

namespace RAM
{
        std::array<uint8_t, 8192> wram{0};
        std::array<uint8_t, 127> hram{0};
        std::array<uint8_t, 7680> eram{0};

        void WriteWRam(uint8_t address, uint8_t data)
        {
                wram[address] = data;
        }

        uint8_t ReadWRam(uint8_t address)
        {
                return wram[address];
        }

        void WriteHRam(uint8_t address, uint8_t data)
        {
                hram[address] = data;
        }

        uint8_t ReadHRam(uint8_t address)
        {
                return hram[address];
        }

        void WriteERam(uint8_t address, uint8_t data)
        {
                eram[address] = data;
        }

        uint8_t ReadERam(uint8_t address)
        {
                return eram[address];
        }
}
