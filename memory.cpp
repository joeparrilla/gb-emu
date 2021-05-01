#include "memory.h"
#include "gb.h"
#include "cart.h"

namespace Memory
{
        uint8_t Read(uint8_t address)
        {
                if (address >= BUS_POINTERS::CART_ROM0_START && address <= BUS_POINTERS::CART_ROM0_END)
                {
                        return Cart::Read(address);
                }
                else if (address >= BUS_POINTERS::CART_ROM1_START && address <= BUS_POINTERS::CART_ROM1_END)
                {
                        return Cart::Read(address);
                }
                else if (address >= BUS_POINTERS::VRAM_START && address <= BUS_POINTERS::VRAM_END)
                {

                }
                else if (address >= BUS_POINTERS::EX_RAM_START && address <= BUS_POINTERS::EX_RAM_END)
                {
                }
                else if (address >= BUS_POINTERS::W_RAM0_START && address <= BUS_POINTERS::W_RAM0_END)
                {
                }
                else if (address >= BUS_POINTERS::W_RAM1_START && address <= BUS_POINTERS::W_RAM1_END)
                {
                }
                else if (address >= BUS_POINTERS::ECHO_RAM_START && address <= BUS_POINTERS::ECHO_RAM_END)
                {
                }
                else if (address >= BUS_POINTERS::OAM_START && address <= BUS_POINTERS::OAM_END)
                {
                }
                else if (address >= BUS_POINTERS::IO_START && address <= BUS_POINTERS::IO_END)
                {
                }
                else if (address >= BUS_POINTERS::HRAM_START && address <= BUS_POINTERS::HRAM_END)
                {
                }
                else if (address == BUS_POINTERS::INT_REGISTER)
                {
                }
                else
                {
                        //INVALID ADDR
                }
        }
        void Write(uint8_t address, uint8_t data)
        {
                if (address >= BUS_POINTERS::CART_ROM0_START && address <= BUS_POINTERS::CART_ROM0_END)
                {
                }
                else if (address >= BUS_POINTERS::CART_ROM1_START && address <= BUS_POINTERS::CART_ROM1_END)
                {
                }
                else if (address >= BUS_POINTERS::VRAM_START && address <= BUS_POINTERS::VRAM_END)
                {
                }
                else if (address >= BUS_POINTERS::EX_RAM_START && address <= BUS_POINTERS::EX_RAM_END)
                {
                }
                else if (address >= BUS_POINTERS::W_RAM0_START && address <= BUS_POINTERS::W_RAM0_END)
                {
                }
                else if (address >= BUS_POINTERS::W_RAM1_START && address <= BUS_POINTERS::W_RAM1_END)
                {
                }
                else if (address >= BUS_POINTERS::ECHO_RAM_START && address <= BUS_POINTERS::ECHO_RAM_END)
                {
                }
                else if (address >= BUS_POINTERS::OAM_START && address <= BUS_POINTERS::OAM_END)
                {
                }
                else if (address >= BUS_POINTERS::IO_START && address <= BUS_POINTERS::IO_END)
                {
                }
                else if (address >= BUS_POINTERS::HRAM_START && address <= BUS_POINTERS::HRAM_END)
                {
                }
                else if (address == BUS_POINTERS::INT_REGISTER)
                {
                }
                else
                {
                        //INVALID ADDR
                }
        }
}
