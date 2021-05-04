#pragma once

#include <stdint.h>
#include <array>
#include <string>

namespace Cart
{
        extern std::array<uint8_t, 48> logo;
        extern std::array<uint8_t, 16> title;
        extern std::array<uint8_t, 4> mfct_code;
        extern uint8_t cgb_flag;
        extern std::array<uint8_t, 2> new_lics_code;
        extern uint8_t sgb_flag;
        extern uint8_t cart_type;
        extern uint8_t rom_size;
        extern uint8_t ram_size;
        extern uint8_t dest_code;
        extern uint8_t old_lics_code;
        extern uint8_t mask_rom_version;
        extern uint8_t header_checksum;
        extern std::array<uint8_t, 2> global_checksum;
        extern std::array<uint8_t, 32768> rom;

        enum cart_header_pointers
        {
                ENTRY_START = 0x0100,
                LOGO_START = 0x0104,
                TITLE_START = 0x0134,
                MANUFACTURER_START = 0x013F,
                CGB_FLAG_START = 0x0143,
                NEW_LICENSEE_START = 0x0144,
                SGB_FLAG_START = 0x0146,
                CART_TYPE_START = 0x0147,
                ROM_SIZE_START = 0x0148,
                RAM_SIZE_START = 0x0149,
                DESTINATION_CODE_START = 0x014A,
                OLD_LICENSEE_START = 0x014B,
                MASK_ROM_VERSION_START = 0x014C,
                HEADER_CHECKSUM_START = 0x014D,
                GLOBAL_CHECKSUM_START = 0x014E
        };

        void LoadRom(std::string filename);
        void DumpHeaderToConsole();
        void Write(uint8_t address, uint8_t data);
        uint8_t Read(uint8_t address);
};