#pragma once

#include <stdint.h>
#include <array>

namespace Display
{
        extern std::array<uint32_t, 65536> bg;

        void BuildBG();

        union LCDC
        {
                struct
                {
                        uint8_t bg_window_enable : 1;
                        uint8_t obj_enable : 1;
                        uint8_t obj_size : 1;
                        uint8_t bg_tilemap_offset : 1;
                        uint8_t tile_data_not_offset : 1;
                        uint8_t window_enable : 1;
                        uint8_t window_tilemap_offset : 1;
                        uint8_t lcd_enable : 1;
                };
                uint8_t value; // 0xFF40
        };

        union STAT
        {
                struct
                {
                        uint8_t mode : 2;
                        uint8_t line_coincidence : 1;
                        uint8_t interrupt_h_Blank : 1;
                        uint8_t interrupt_v_blank : 1;
                        uint8_t interrupt_oam : 1;
                        uint8_t interrupt_lyc : 1;
                        uint8_t unused : 1;
                };
                uint8_t value; // 0xFF41
        };

        extern LCDC lcdc;
        extern STAT stat;

}