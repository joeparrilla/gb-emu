#include "gb.h"
#include "cpu.h"
#include "platform.h"
#include "display.h"
#include <iostream>
#include <chrono>

const int VIDEO_WIDTH = 160;
const int VIDEO_HEIGHT = 144;

int main(int argc, char **argv)
{

        if (argc != 4)
        {
                std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
                std::exit(EXIT_FAILURE);
        }

        int video_scale = std::stoi(argv[1]);
        int cycle_delay = std::stoi(argv[2]);
        char const *rom_file_name = argv[3];

        Platform platform("BameGoy", VIDEO_WIDTH * video_scale, VIDEO_HEIGHT * video_scale, VIDEO_WIDTH, VIDEO_HEIGHT);
        // int video_pitch = sizeof(Display::bg[0]) * VIDEO_WIDTH;
        int video_pitch = sizeof(Display::bg[0]);

        GB::LoadCart(rom_file_name);
        GB::LoadBootRom("roms/dmg_boot.bin");
        // GB::DumpCartHeaderToConsole();
        // GB::DumpBootRomToConsole();

        auto lastCycleTime = std::chrono::high_resolution_clock::now();
        bool quit = false;

        while (GB::running && !quit)
        {
                quit = platform.ProcessInput(GB::buttons.data());

                auto currentTime = std::chrono::high_resolution_clock::now();
                float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

                // if (dt > cycle_delay)
                // {
                lastCycleTime = currentTime;
                GB::DumpCPURegToConsole();
                // if (!GB::boot_rom_enabled)
                // {
                //         GB::DumpVRamToConsole();
                //         break;
                // }
                CPU::Cycle();
                // Display::UpdateBGMap1();
                // Display::BuildTiles();
                // Display::UpdateBG();
                // GB::DumpBackgroundToConsole();
                platform.Update(Display::bg.data(), video_pitch);
                // }
        }

        // GB::DumpCPURegToConsole();

        return 0;
}
