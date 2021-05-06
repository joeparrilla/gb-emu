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
        }

        void Cycle()
        {
                opcode = NextByte();

                switch (opcode)
                {
                        //--------------8 bit loads-----------------
                case 0x02: //LD (BC),A
                        Memory::Write(reg_bc.value, reg_af.hi);
                        break;
                case 0x12: //LD (DE),A
                        Memory::Write(reg_de.value, reg_af.hi);
                        break;
                case 0x22: //LD (HL+),A
                        Memory::Write(reg_hl.value++, reg_af.hi);
                        break;
                case 0x32: //LD (HL-),A
                        Memory::Write(reg_hl.value--, reg_af.hi);
                        break;

                case 0x06: //LD B,u8
                        reg_bc.hi = NextByte();
                        break;
                case 0x16: //LD D,u8
                        reg_de.hi = NextByte();
                        break;
                case 0x26: //LD H,u8
                        reg_hl.hi = NextByte();
                        break;
                case 0x36: //LD (HL),u8
                        Memory::Write(reg_hl.value, NextByte());
                        break;

                case 0x0A: //LD A,(BC)
                        reg_af.hi = Memory::Read(reg_bc.value);
                        break;
                case 0x1A: //LD A,(DE)
                        reg_af.hi = Memory::Read(reg_de.value);
                        break;
                case 0x2A: //LD A,(HL+)
                        reg_af.hi = Memory::Read(reg_hl.value++);
                        break;
                case 0x3A: //LD A,(HL-)
                        reg_af.hi = Memory::Read(reg_hl.value--);
                        break;

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

                case 0x40: //LD B,B
                        reg_bc.hi = reg_bc.hi;
                        break;
                case 0x41: //LD B,C
                        reg_bc.hi = reg_bc.lo;
                        break;
                case 0x42: //LD B,D
                        reg_bc.hi = reg_de.hi;
                        break;
                case 0x43: //LD B,E
                        reg_bc.hi = reg_de.lo;
                        break;
                case 0x44: //LD B,H
                        reg_bc.hi = reg_hl.hi;
                        break;
                case 0x45: //LD B,L
                        reg_bc.hi = reg_hl.lo;
                        break;
                case 0x46: //LD B,(HL)
                        reg_bc.hi = Memory::Read(reg_hl.value);
                        break;
                case 0x47: //LD B,A
                        reg_bc.hi = reg_af.hi;
                        break;
                case 0x48: //LD C,B
                        reg_bc.lo = reg_bc.hi;
                        break;
                case 0x49: //LD C,C
                        reg_bc.lo = reg_bc.lo;
                        break;
                case 0x4A: //LD C,D
                        reg_bc.lo = reg_de.hi;
                        break;
                case 0x4B: //LD C,E
                        reg_bc.lo = reg_de.lo;
                        break;
                case 0x4C: //LD C,H
                        reg_bc.lo = reg_hl.hi;
                        break;
                case 0x4D: //LD C,L
                        reg_bc.lo = reg_hl.lo;
                        break;
                case 0x4E: //LD C,(HL)
                        reg_bc.lo = Memory::Read(reg_hl.value);
                        break;
                case 0x4F: //LD C,A
                        reg_bc.lo = reg_af.hi;
                        break;

                case 0x50: //LD D,B
                        reg_de.hi = reg_bc.hi;
                        break;
                case 0x51: //LD D,C
                        reg_de.hi = reg_bc.lo;
                        break;
                case 0x52: //LD D,D
                        reg_de.hi = reg_de.hi;
                        break;
                case 0x53: //LD D,E
                        reg_de.hi = reg_de.lo;
                        break;
                case 0x54: //LD D,H
                        reg_de.hi = reg_hl.hi;
                        break;
                case 0x55: //LD D,L
                        reg_de.hi = reg_hl.lo;
                        break;
                case 0x56: //LD D,(HL)
                        reg_de.hi = Memory::Read(reg_hl.value);
                        break;
                case 0x57: //LD D,A
                        reg_de.hi = reg_af.hi;
                        break;
                case 0x58: //LD E,B
                        reg_de.lo = reg_bc.hi;
                        break;
                case 0x59: //LD E,C
                        reg_de.lo = reg_bc.lo;
                        break;
                case 0x5A: //LD E,D
                        reg_de.lo = reg_de.hi;
                        break;
                case 0x5B: //LD E,E
                        reg_de.lo = reg_de.lo;
                        break;
                case 0x5C: //LD E,H
                        reg_de.lo = reg_hl.hi;
                        break;
                case 0x5D: //LD E,L
                        reg_de.lo = reg_hl.lo;
                        break;
                case 0x5E: //LD E,(HL)
                        reg_de.lo = Memory::Read(reg_hl.value);
                        break;
                case 0x5F: //LD E,A
                        reg_de.lo = reg_af.hi;
                        break;

                case 0x60: //LD H,B
                        reg_hl.hi = reg_bc.hi;
                        break;
                case 0x61: //LD H,C
                        reg_hl.hi = reg_bc.lo;
                        break;
                case 0x62: //LD H,D
                        reg_hl.hi = reg_de.hi;
                        break;
                case 0x63: //LD H,E
                        reg_hl.hi = reg_de.lo;
                        break;
                case 0x64: //LD H,H
                        reg_hl.hi = reg_hl.hi;
                        break;
                case 0x65: //LD H,L
                        reg_hl.hi = reg_hl.lo;
                        break;
                case 0x66: //LD H,(HL)
                        reg_hl.hi = Memory::Read(reg_hl.value);
                        break;
                case 0x67: //LD H,A
                        reg_hl.hi = reg_af.hi;
                        break;
                case 0x68: //LD L,B
                        reg_hl.lo = reg_bc.hi;
                        break;
                case 0x69: //LD L,C
                        reg_hl.lo = reg_bc.lo;
                        break;
                case 0x6A: //LD L,D
                        reg_hl.lo = reg_de.hi;
                        break;
                case 0x6B: //LD L,E
                        reg_hl.lo = reg_de.lo;
                        break;
                case 0x6C: //LD L,H
                        reg_hl.lo = reg_hl.hi;
                        break;
                case 0x6D: //LD L,L
                        reg_hl.lo = reg_hl.lo;
                        break;
                case 0x6E: //LD L,(HL)
                        reg_hl.lo = Memory::Read(reg_hl.value);
                        break;
                case 0x6F: //LD L,A
                        reg_hl.lo = reg_af.hi;
                        break;

                case 0x70: //LD (HL),B
                        Memory::Write(reg_hl.value, reg_bc.hi);
                        break;
                case 0x71: //LD (HL),C
                        Memory::Write(reg_hl.value, reg_bc.lo);
                        break;
                case 0x72: //LD (HL),D
                        Memory::Write(reg_hl.value, reg_de.hi);
                        break;
                case 0x73: //LD (HL),E
                        Memory::Write(reg_hl.value, reg_de.lo);
                        break;
                case 0x74: //LD (HL),H
                        Memory::Write(reg_hl.value, reg_hl.hi);
                        break;
                case 0x75: //LD (HL),L
                        Memory::Write(reg_hl.value, reg_hl.lo);
                        break;
                case 0x77: //LD (HL),A
                        Memory::Write(reg_hl.value, reg_af.hi);
                        break;
                case 0x78: //LD A,B
                        reg_af.hi = reg_bc.hi;
                        break;
                case 0x79: //LD A,C
                        reg_af.hi = reg_bc.lo;
                        break;
                case 0x7A: //LD A,D
                        reg_af.hi = reg_de.hi;
                        break;
                case 0x7B: //LD A,E
                        reg_af.hi = reg_de.lo;
                        break;
                case 0x7C: //LD A,H
                        reg_af.hi = reg_hl.hi;
                        break;
                case 0x7D: //LD A,L
                        reg_af.hi = reg_hl.lo;
                        break;
                case 0x7E: //LD A,(HL)
                        reg_af.hi = Memory::Read(reg_hl.value);
                        break;
                case 0x7F: //LD A,A
                        reg_af.hi = reg_af.hi;
                        break;

                case 0xE0: //LD (FF00+u8),A
                        Memory::Write(0xFF00u + NextByte(), reg_af.hi);
                        break;

                case 0xF0: //LD A,(FF00+u8)
                        reg_af.hi = Memory::Read(0xFF00u + NextByte());
                        break;

                case 0xE2: //LD (FF00+C),A
                        Memory::Write(0xFF00u + reg_bc.lo, reg_af.hi);
                        break;

                case 0xF2: //LD A,(FF00+C)
                        reg_af.hi = Memory::Read(0xFF00u + reg_bc.lo);
                        break;

                case 0xEA: //LD (u16),A
                        Memory::Write(NextByte() + (NextByte() << 8u), reg_af.hi);
                        break;

                case 0xFA: //LD A,(u16)
                        reg_af.hi = (NextByte() + (NextByte() << 8u));
                        break;
                        // --------------------- END OF 8 BIT LOADS----------------
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