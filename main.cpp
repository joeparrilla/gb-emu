#include "gb.h"
#include "cpu.h"
#include <iostream>
#include <chrono>

int main(int argc, char **argv)
{
        GB::LoadCart("roms/tetris.gb");
        GB::LoadBootRom("roms/dmg_boot.bin");
        // GB::DumpCartHeaderToConsole();
        // GB::DumpBootRomToConsole();

        while (GB::running)
        {
                // GB::DumpCPURegToConsole();
                if (!GB::boot_rom_enabled)
                {
                        GB::DumpVRamToConsole();
                        break;
                }
                CPU::Cycle();
                
        }

        // GB::DumpCPURegToConsole();

        return 0;
}
