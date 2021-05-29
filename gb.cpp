#include "gb.h"
#include "cart.h"
#include "memory.h"
#include "cpu.h"
#include <iostream>
#include <fstream>

namespace GB
{
        //ram, registers, etc on chip
        std::array<uint8_t, 8192> vram{0};
        std::array<uint8_t, 128> io_regs{0};
        std::array<uint8_t, 160> oam{0};
        uint8_t ie{0};
        bool ime{0};

        //boot rom
        std::array<uint8_t, 256> boot_rom{0};
        bool boot_rom_enabled = false;

        bool running = true;

        void LoadCart(std::string filename)
        {
                Cart::LoadRom(filename);
                Memory::Write(0xFF44, 0x90); //TODO hard coded to get through boot rom without display
        }

        void LoadBootRom(std::string filename)
        {
                std::ifstream file(filename, std::ios::binary | std::ios::ate);

                if (file.is_open())
                {
                        std::streampos size = file.tellg();
                        char *buffer = new char[size];
                        file.seekg(0, std::ios::beg);
                        file.read(buffer, size);
                        file.close();

                        for (long i = 0; i < size; ++i)
                        {
                                boot_rom[i] = buffer[i];
                        }
                        delete[] buffer;
                }

                boot_rom_enabled = true;
        }

        void DumpCartHeaderToConsole()
        {
                Cart::DumpHeaderToConsole();
        }

        void DumpBootRomToConsole()
        {
                std::cout << "Boot ROM: ";
                for (auto &item : boot_rom)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";
        }

        void DumpCPURegToConsole()
        {
                std::cout << "\n";
                std::cout << "AF: " << std::hex << int(CPU::reg_af.value) << "\n";
                std::cout << "BC: " << std::hex << int(CPU::reg_bc.value) << "\n";
                std::cout << "DE: " << std::hex << int(CPU::reg_de.value) << "\n";
                std::cout << "HL: " << std::hex << int(CPU::reg_hl.value) << "\n";
                std::cout << "SP: " << std::hex << int(CPU::sp) << "\n";
                std::cout << "PC: " << std::hex << int(CPU::pc) << "\n";
        }

        void DumpVRamToConsole()
        {
                std::cout << "VRAM: ";
                for (ulong i = 0; i < vram.size(); i += 2)
                {
                        std::cout << "0x" << Memory::VRAM_START + i << ": ";
                        std::cout << std::hex << ((int(vram[i]) + (int(vram[i+1]) << 8u))) << " ";
                        std::cout << "\n";
                }
                
        }

}