#pragma once

#include <stdint.h>
#include <array>

class Cart
{
public:
        Cart();

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
        std::array<uint8_t, 32768> rom{};
};