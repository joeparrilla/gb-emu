#pragma once

#include <stdint.h>
#include <array>
#include <string>

class GB
{
public:
        GB();
        void LoadCart(std::string file_name);
        void LoadBootRom(std::string file_name);
        void DumpCartHeaderToConsole();

        //ram, registers, etc on chip
        std::array<uint8_t, 8192> vram{};
        std::array<uint8_t, 16> io_regs{};
        std::array<uint8_t, 20> oam{};
        uint8_t ie{0};

private:
        //boot rom
        std::array<uint8_t, 256> boot_rom{};
};