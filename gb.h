#pragma once

#include <stdint.h>
#include <array>
#include <string>

namespace GB
{
        void LoadCart(std::string file_name);
        void LoadBootRom(std::string file_name);
        void DumpCartHeaderToConsole();
        void DumpBootRomToConsole();
        void DumpCPURegToConsole();
        void DumpVRamToConsole();

        //ram, registers, etc on chip
        extern std::array<uint8_t, 8192> vram;
        extern std::array<uint8_t, 160> oam;
        extern std::array<uint8_t, 128> io_regs;
        extern uint8_t ie;

        //I/O
        extern uint16_t div;
        extern uint16_t tima;
        extern uint8_t tma;
        extern uint8_t tac;
        extern bool ime;
        extern uint8_t intf;

        //Input buttons
        extern std::array<uint8_t, 1> buttons;

        //boot rom
        extern std::array<uint8_t, 256> boot_rom;
        extern bool boot_rom_enabled;

        extern bool running;
};