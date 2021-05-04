#include "cpu.h"
#include "memory.h"
#include "gb.h"
#include <iostream>

namespace CPU
{
        Register reg_af{0};
        Register reg_bc{0};
        Register reg_de{0};
        Register reg_hl{0};
        uint16_t sp{0};
        uint16_t pc{0};

        uint8_t opcode{0};

        uint8_t NextByte()
        {
                uint8_t byte = Memory::Read(pc);
                pc++;
                return byte;
                //add clock tick here
        }

        void Cycle()
        {
                opcode = NextByte();

                switch (opcode)
                {
                case 0x0E: //LD C,u8
                        reg_bc.lo = NextByte();
                        break;
                case 0x1E: //LD E,u8
                        reg_de.lo = NextByte();
                        break;
                case 0x2E: //LD L,u8
                        reg_hl.lo = NextByte();
                        break;
                case 0x3E: //LD A,u8
                        reg_af.hi = NextByte();
                        break;
                case 0x20: //JR NZ,i8
                {
                        int8_t i8 = (int8_t)NextByte();
                        if (reg_af.lo >> 7 == 0)
                        {
                                pc += i8;
                        }
                }
                break;
                case 0x21: //LD HL, u16
                        reg_hl.value = (NextByte() + (NextByte() << 8u));
                        break;
                case 0x31: //LD SP, u16
                        sp = NextByte() + (NextByte() << 8u);
                        break;
                case 0x32: //LD (HL-),A
                        Memory::Write(reg_hl.value, reg_af.hi);
                        reg_hl.value--;
                        break;
                case 0xAF: //XOR A,A
                        reg_af.hi ^= reg_af.hi;
                        reg_af.lo |= 0b01000000u; //set z reg to 1
                        break;
                case 0xCB: //CB prefix ops
                {
                        uint8_t cb_op = NextByte();
                        switch (cb_op)
                        {
                        case 0x7C: //BIT 7,H
                                
                                if ((reg_hl.hi >> 7) == 0)
                                {
                                        reg_af.lo |= 0b1000'0000u; //set z reg to 1
                                }
                                else
                                {
                                        reg_af.lo &= 0b0111'1111; //set z reg to 0
                                }
                                reg_af.lo &= 0b1011'1111u; //set n flag to 0
                                reg_af.lo |= 0b0010'0000u; //set h flag to 1
                                break;
                        }
                }
                break;
                default:
                        std::cout << "reached undef op";
                        GB::running = false;
                        break;
                }
        }
}