#pragma once

#include <stdint.h>
#include <array>
#include <string>

namespace CPU
{
        uint8_t NextByte();
        void Cycle();
        void SetZFlag(int a);
        void setNFlag(int a);
        void SetHFlag(int a);
        void SetCFlag(int a);
        uint8_t GetZFlag();
        uint8_t GetNFlag();
        uint8_t GetHFlag();
        uint8_t GetCFlag();
        bool CheckAddCarry(uint8_t a, uint8_t b);
        bool CheckSubCarry(uint8_t a, uint8_t b);
        bool CheckAddHalfCarry(uint8_t a, uint8_t b);
        bool CheckSubHalfCarry(uint8_t a, uint8_t b);

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