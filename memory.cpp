#include "memory.h"
#include "gb.h"
#include "cart.h"
#include "ram.h"

namespace Memory
{
        uint8_t Read(uint16_t address)
        {

                if (GB::boot_rom_enabled && address < Cart::ENTRY_START)
                {
                        return GB::boot_rom[address];
                }
                else if (address >= BUS_POINTERS::CART_ROM0_START && address <= BUS_POINTERS::CART_ROM0_END)
                {
                        return Cart::Read(address);
                }
                else if (address >= BUS_POINTERS::CART_ROM1_START && address <= BUS_POINTERS::CART_ROM1_END)
                {
                        return Cart::Read(address - BUS_POINTERS::CART_ROM1_START);
                }
                else if (address >= BUS_POINTERS::VRAM_START && address <= BUS_POINTERS::VRAM_END)
                {
                        return GB::vram[address - BUS_POINTERS::VRAM_START];
                }
                else if (address >= BUS_POINTERS::EX_RAM_START && address <= BUS_POINTERS::EX_RAM_END)
                {
                        //read from cart ram
                }
                else if (address >= BUS_POINTERS::W_RAM0_START && address <= BUS_POINTERS::W_RAM0_END)
                {
                        return RAM::ReadWRam(address - BUS_POINTERS::W_RAM0_START);
                }
                else if (address >= BUS_POINTERS::W_RAM1_START && address <= BUS_POINTERS::W_RAM1_END)
                {
                        return RAM::ReadWRam(address - BUS_POINTERS::W_RAM1_START);
                }
                else if (address >= BUS_POINTERS::ECHO_RAM_START && address <= BUS_POINTERS::ECHO_RAM_END)
                {
                        return RAM::ReadERam(address - BUS_POINTERS::ECHO_RAM_START);
                }
                else if (address >= BUS_POINTERS::OAM_START && address <= BUS_POINTERS::OAM_END)
                {
                        return GB::oam[address - BUS_POINTERS::OAM_START];
                }
                else if (address >= BUS_POINTERS::IO_START && address <= BUS_POINTERS::IO_END)
                {
                        return GB::io_regs[address - BUS_POINTERS::IO_START];
                }
                else if (address >= BUS_POINTERS::HRAM_START && address <= BUS_POINTERS::HRAM_END)
                {
                        return RAM::ReadHRam(address - BUS_POINTERS::HRAM_START);
                }
                else if (address == BUS_POINTERS::INT_REGISTER)
                {
                        return GB::ie;
                }
                else
                {
                        //INVALID ADDR
                }
        }
        void Write(uint16_t address, uint8_t data)
        {
                if (address >= BUS_POINTERS::CART_ROM0_START && address <= BUS_POINTERS::CART_ROM0_END)
                {
                        Cart::Write(address, data);
                }
                else if (address >= BUS_POINTERS::CART_ROM1_START && address <= BUS_POINTERS::CART_ROM1_END)
                {
                        Cart::Write(address - BUS_POINTERS::CART_ROM1_START, data);
                }
                else if (address >= BUS_POINTERS::VRAM_START && address <= BUS_POINTERS::VRAM_END)
                {
                        GB::vram[address - BUS_POINTERS::VRAM_START] = data;
                }
                else if (address >= BUS_POINTERS::EX_RAM_START && address <= BUS_POINTERS::EX_RAM_END)
                {
                        //read from cart ram
                }
                else if (address >= BUS_POINTERS::W_RAM0_START && address <= BUS_POINTERS::W_RAM0_END)
                {
                        RAM::WriteWRam(address - BUS_POINTERS::W_RAM0_START, data);
                }
                else if (address >= BUS_POINTERS::W_RAM1_START && address <= BUS_POINTERS::W_RAM1_END)
                {
                        RAM::WriteWRam(address - BUS_POINTERS::W_RAM1_START, data);
                }
                else if (address >= BUS_POINTERS::ECHO_RAM_START && address <= BUS_POINTERS::ECHO_RAM_END)
                {
                        RAM::WriteERam(address - BUS_POINTERS::ECHO_RAM_START, data);
                }
                else if (address >= BUS_POINTERS::OAM_START && address <= BUS_POINTERS::OAM_END)
                {
                        GB::oam[address - BUS_POINTERS::OAM_START] = data;
                }
                else if (address >= BUS_POINTERS::IO_START && address <= BUS_POINTERS::IO_END)
                {
                        GB::io_regs[address - BUS_POINTERS::IO_START] = data;
                }
                else if (address >= BUS_POINTERS::HRAM_START && address <= BUS_POINTERS::HRAM_END)
                {
                        RAM::WriteHRam(address - BUS_POINTERS::HRAM_START, data);
                }
                else if (address == BUS_POINTERS::INT_REGISTER)
                {
                        GB::ie = data;
                }
                else
                {
                        //INVALID ADDR
                }
        }
}
