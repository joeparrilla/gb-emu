#include "ram.h"

namespace RAM
{
        std::array<uint8_t, 8192> wram{0};
        std::array<uint8_t, 127> hram{0};
        std::array<uint8_t, 7680> eram{0};

        void WriteWRam(uint8_t address, uint8_t data)
        {
        }

        uint8_t ReadWRam(uint8_t address)
        {
                return 0;
        }

        void WriteHRam(uint8_t address, uint8_t data)
        {
        }

        uint8_t ReadHRam(uint8_t address)
        {
                return 0;
        }

        void WriteERam(uint8_t address, uint8_t data)
        {
        }

        uint8_t ReadERam(uint8_t address)
        {
                return 0;
        }
}
