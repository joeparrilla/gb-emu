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
                uint16_t addr16(0);
                uint8_t data8(0);

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
                        // ----------------------16 BIT LOADS---------------
                case 0x01: //LD BC, u16
                        reg_bc.value = NextByte() + (NextByte() << 8u);
                        break;
                case 0x11: //LD DE, u16
                        reg_de.value = NextByte() + (NextByte() << 8u);
                        break;
                case 0x21: //LD HL, u16
                        reg_hl.value = NextByte() + (NextByte() << 8u);
                        break;
                case 0x31: //LD SP, u16
                        sp = NextByte() + (NextByte() << 8u);
                        break;
                case 0x08: //LD (u16),SP
                        addr16 = NextByte() + (NextByte() << 8u);
                        Memory::Write(addr16, sp & 0x0Fu);
                        Memory::Write(addr16 + 1, sp >> 8u);
                        break;

                case 0xC1: //POP B,C
                        reg_bc.lo = Memory::Read(sp++);
                        reg_bc.hi = Memory::Read(sp++);
                case 0xD1: //POP D,E
                        reg_de.lo = Memory::Read(sp++);
                        reg_de.hi = Memory::Read(sp++);
                case 0xE1: //POP H,L
                        reg_hl.lo = Memory::Read(sp++);
                        reg_hl.hi = Memory::Read(sp++);
                case 0xF1: //POP A,F
                        reg_af.lo = Memory::Read(sp++);
                        reg_af.hi = Memory::Read(sp++);

                case 0xC5: //PUSH B,C
                        Memory::Write(--sp, reg_bc.hi);
                        Memory::Write(--sp, reg_bc.lo);
                case 0xD5: //PUSH D,E
                        Memory::Write(--sp, reg_de.hi);
                        Memory::Write(--sp, reg_de.lo);
                case 0xE5: //PUSH H,L
                        Memory::Write(--sp, reg_hl.hi);
                        Memory::Write(--sp, reg_hl.lo);
                case 0xF5: //PUSH A,F
                        Memory::Write(--sp, reg_af.hi);
                        Memory::Write(--sp, reg_af.lo);
                case 0xF9: //LD SP,HL
                        sp = reg_hl.value;
                // ------------------END OF 16 BIT LOADS
                // -------------8 BIT ALU-----------
                case 0x04: //INC B
                        reg_bc.hi++;
                        if (reg_bc.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_bc.hi - 1, reg_bc.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x14: //INC D
                        reg_de.hi++;
                        if (reg_de.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_de.hi - 1, reg_de.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x24: //INC H
                        reg_hl.hi++;
                        if (reg_hl.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_hl.hi - 1, reg_hl.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x34: //INC (HL)
                        data8 = Memory::Read(reg_hl.value);
                        Memory::Write(reg_hl.value, ++data8);

                        if (data8 == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(data8 - 1, data8))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x05: //DEC B
                        reg_bc.hi--;
                        if (reg_bc.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_bc.hi + 1, reg_bc.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x15: //DEC D
                        reg_de.hi--;
                        if (reg_de.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_de.hi + 1, reg_de.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x25: //DEC H
                        reg_hl.hi--;
                        if (reg_hl.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_hl.hi + 1, reg_hl.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x35: //DEC (HL)
                        data8 = Memory::Read(reg_hl.value);
                        Memory::Write(reg_hl.value, --data8);
                        if (data8 == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(data8 + 1, data8))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x0C: //INC C
                        reg_bc.lo++;
                        if (reg_bc.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_bc.lo - 1, reg_bc.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x1C: //INC E
                        reg_de.lo++;
                        if (reg_de.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_de.lo - 1, reg_de.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x2C: //INC L
                        reg_hl.lo++;
                        if (reg_hl.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_hl.lo - 1, reg_hl.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x3C: //INC A
                        reg_af.hi++;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckAddHalfCarry(reg_af.hi - 1, reg_af.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(0);
                        break;
                case 0x0D: //DEC C
                        reg_bc.lo--;
                        if (reg_bc.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_bc.lo + 1, reg_bc.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x1D: //DEC E
                        reg_de.lo--;
                        if (reg_de.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_de.lo + 1, reg_de.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x2D: //DEC L
                        reg_hl.lo--;
                        if (reg_hl.lo == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_hl.lo + 1, reg_hl.lo))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x3D: //DEC A
                        reg_af.hi--;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        if (CheckSubHalfCarry(reg_af.hi + 1, reg_af.hi))
                        {
                                SetHFlag(1);
                        }
                        else
                        {
                                SetHFlag(0);
                        }
                        setNFlag(1);
                        break;
                case 0x27: //DAA
                           //TODO
                        break;
                case 0x37: //SCF
                        setNFlag(0);
                        SetHFlag(0);
                        SetCFlag(1);
                        break;
                case 0x2F: //CPL
                        reg_af.hi = ~reg_af.hi;
                        setNFlag(1);
                        SetHFlag(1);
                        break;
                case 0x3F: //CCF
                        setNFlag(0);
                        SetHFlag(0);
                        SetCFlag(~GetCFlag());
                        break;
                case 0x80: //ADD A,B
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.hi));
                        setNFlag(0);
                        reg_af.hi += reg_bc.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x81: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x82: //ADD A,D
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_de.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_de.hi));
                        setNFlag(0);
                        reg_af.hi += reg_de.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x83: //ADD A,E
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_de.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_de.lo));
                        setNFlag(0);
                        reg_af.hi += reg_de.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x84: //ADD A,H
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_hl.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_hl.hi));
                        setNFlag(0);
                        reg_af.hi += reg_hl.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x85: //ADD A,L
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_hl.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_hl.lo));
                        setNFlag(0);
                        reg_af.hi += reg_hl.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x86: //ADD A,(HL)
                        data8 = Memory::Read(reg_hl.value);
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, data8));
                        SetCFlag(CheckAddCarry(reg_af.hi, data8));
                        setNFlag(0);
                        reg_af.hi += data8;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x87: //ADD A,A
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_af.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_af.hi));
                        setNFlag(0);
                        reg_af.hi += reg_af.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x88: //ADC A,B
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.hi + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.hi + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_bc.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x89: //ADC A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_bc.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8A: //ADC A,D
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_de.hi + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_de.hi + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_de.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8B: //ADC A,E
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_de.lo + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_de.lo + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_de.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8C: //ADC A,H
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_hl.hi + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_hl.hi + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_hl.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8D: //ADC A,L
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_hl.lo + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_hl.lo + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_hl.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8E: //ADC A,(HL)
                        data8 = Memory::Read(reg_hl.value);
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, data8 + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, data8 + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (data8 + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x8F: //ADC A,A
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_af.hi + GetCFlag()));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_af.hi  + GetCFlag()));
                        setNFlag(0);
                        reg_af.hi += (reg_af.hi  + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x90: //SUB A,B
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_bc.hi));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_bc.hi));
                        setNFlag(1);
                        reg_af.hi -= reg_bc.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x91: //SUB A,C
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(1);
                        reg_af.hi -= reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x92: //SUB A,D
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_de.hi));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_de.hi));
                        setNFlag(1);
                        reg_af.hi -= reg_de.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x93: //SUB A,E
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_de.lo));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_de.lo));
                        setNFlag(1);
                        reg_af.hi -= reg_de.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x94: //SUB A,H
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_hl.hi));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_hl.hi));
                        setNFlag(1);
                        reg_af.hi -= reg_hl.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x95: //SUB A,L
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_hl.lo));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_hl.lo));
                        setNFlag(1);
                        reg_af.hi -= reg_hl.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x96: //SUB A,(HL)
                        data8 = Memory::Read(reg_hl.value);
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, data8));
                        SetCFlag(CheckSubCarry(reg_af.hi, data8));
                        setNFlag(1);
                        reg_af.hi -= data8;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x97: //SUB A,A
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_af.hi));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_af.hi));
                        setNFlag(1);
                        reg_af.hi -= reg_af.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x98: //SBC A,B
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_bc.hi + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_bc.hi + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_bc.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x99: //SBC A,C
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_bc.lo + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_bc.lo + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_bc.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9A: //SBC A,D
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_de.hi + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_de.hi + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_de.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9B: //SBC A,E
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_de.lo + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_de.lo + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_de.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9C: //SBC A,H
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_hl.hi + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_hl.hi + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_hl.hi + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9D: //SBC A,L
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_hl.lo + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_hl.lo + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_hl.lo + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9E: //SBC A,(HL)
                        data8 = Memory::Read(reg_hl.value);
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, data8 + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, data8 + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (data8 + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0x9F: //SBC A,A
                        SetHFlag(CheckSubHalfCarry(reg_af.hi, reg_af.hi + GetCFlag()));
                        SetCFlag(CheckSubCarry(reg_af.hi, reg_af.hi  + GetCFlag()));
                        setNFlag(1);
                        reg_af.hi -= (reg_af.hi  + GetCFlag());
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                //TODO here down
                case 0xA0: //ADD A,B
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.hi));
                        setNFlag(0);
                        reg_af.hi += reg_bc.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA1: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA2: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA3: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA4: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA5: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA6: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA7: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA8: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xA9: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAA: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAB: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAC: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAD: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xAF: //XOR A,A
                        reg_af.hi ^= reg_af.hi;
                        SetZFlag(1);
                        break;
                case 0xB0: //ADD A,B
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.hi));
                        setNFlag(0);
                        reg_af.hi += reg_bc.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB1: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB2: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB3: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB4: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB5: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB6: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB7: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB8: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xB9: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBA: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBB: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBC: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBD: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xBF: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xC6: //ADD A,B
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.hi));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.hi));
                        setNFlag(0);
                        reg_af.hi += reg_bc.hi;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xD6: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xE6: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xF6: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xCE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xDE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xEE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                case 0xFE: //ADD A,C
                        SetHFlag(CheckAddHalfCarry(reg_af.hi, reg_bc.lo));
                        SetCFlag(CheckAddCarry(reg_af.hi, reg_bc.lo));
                        setNFlag(0);
                        reg_af.hi += reg_bc.lo;
                        if (reg_af.hi == 0)
                        {
                                SetZFlag(1);
                        }
                        else
                        {
                                SetZFlag(0);
                        }
                        break;
                        //----------------END OF 8 BIT ALU-----
                case 0x20: //JR NZ,i8
                {
                        int8_t i8 = (int8_t)NextByte();
                        if (reg_af.lo >> 7 == 0)
                        {
                                pc += i8;
                        }
                }
                break;
                case 0xCB: //CB prefix ops
                {
                        uint8_t cb_op = NextByte();
                        switch (cb_op)
                        {
                        case 0x7C: //BIT 7,H

                                if ((reg_hl.hi >> 7) == 0)
                                {
                                        SetZFlag(1);
                                }
                                else
                                {
                                        SetZFlag(0);
                                }
                                setNFlag(0);
                                SetHFlag(1);
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

        void SetZFlag(int a)
        {
                if (a == 1)
                {
                        reg_af.lo |= 0b1000'0000u; //set z flag to 1
                }
                else
                {
                        reg_af.lo &= 0b0111'1111; //set z flag to 0
                }
        }
        void setNFlag(int a)
        {
                if (a == 1)
                {
                        reg_af.lo |= 0b0100'0000u; //set n flag to 1
                }
                else
                {
                        reg_af.lo &= 0b1011'1111; //set n flag to 0
                }
        }
        void SetHFlag(int a)
        {
                if (a == 1)
                {
                        reg_af.lo |= 0b0010'0000u; //set h flag to 1
                }
                else
                {
                        reg_af.lo &= 0b1101'1111; //set h flag to 0
                }
        }
        void SetCFlag(int a)
        {
                if (a == 1)
                {
                        reg_af.lo |= 0b0001'0000u; //set c flag to 1
                }
                else
                {
                        reg_af.lo &= 0b1110'1111; //set c flag to 0
                }
        }
        uint8_t GetZFlag()
        {
                return reg_af.lo >> 7;
        }
        uint8_t GetNFlag()
        {
                return reg_af.lo >> 6;
        }
        uint8_t GetHFlag()
        {
                return reg_af.lo >> 5;
        }
        uint8_t GetCFlag()
        {
                return reg_af.lo >> 4;
        }
        bool CheckAddCarry(uint8_t a, uint8_t b)
        {
                return a > (0xFF - b);
        }
        bool CheckSubCarry(uint8_t a, uint8_t b)
        {
                return a < b;
        }

        bool CheckSubHalfCarry(uint8_t a, uint8_t b)
        {
                return (((a & 0xf) - (b & 0xf)) & 0x10) == 0x10;
        }

        bool CheckAddHalfCarry(uint8_t a, uint8_t b)
        {
                return (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10;
        }
}