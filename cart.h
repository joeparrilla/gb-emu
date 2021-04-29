#pragma once

#include <stdint.h>
#include <array>
#include <string>

class Cart
{
public:
        Cart();
        void LoadRom(std::string filename);
        void DumpHeaderToConsole();

        std::array<uint8_t, 48> logo{};
        std::array<uint8_t, 16> title{};
        std::array<uint8_t, 4> mfct_code{};
        uint8_t cgb_flag{};
        std::array<uint8_t, 2> new_lics_code{};
        uint8_t sgb_flag{};
        uint8_t cart_type{};
        uint8_t rom_size{};
        uint8_t ram_size{};
        uint8_t dest_code{};
        uint8_t old_lics_code{};
        uint8_t mask_rom_version{};
        uint8_t header_checksum{};
        std::array<uint8_t, 4> global_checksum{};

        std::array<uint8_t, 32768> rom{};

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

private:

};