#pragma once

#include <stdint.h>
#include <array>
#include <string>

namespace CPU
{
        uint8_t NextByte();
        void Cycle();

        union Register
        {
                struct
                {
                        uint8_t lo;
                        uint8_t hi;
                };
                uint16_t value;
        };

        extern Register reg_af;
        extern Register reg_bc;
        extern Register reg_de;
        extern Register reg_hl;
        extern uint16_t sp;
        extern uint16_t pc;

        extern uint8_t opcode;
}