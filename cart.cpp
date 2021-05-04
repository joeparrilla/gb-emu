#include "cart.h"
#include <iostream>
#include <fstream>

namespace Cart
{
        std::array<uint8_t, 48> logo{0};
        std::array<uint8_t, 16> title{0};
        std::array<uint8_t, 4> mfct_code{0};
        uint8_t cgb_flag{0};
        std::array<uint8_t, 2> new_lics_code{0};
        uint8_t sgb_flag{0};
        uint8_t cart_type{0};
        uint8_t rom_size{0};
        uint8_t ram_size{0};
        uint8_t dest_code{0};
        uint8_t old_lics_code{0};
        uint8_t mask_rom_version{0};
        uint8_t header_checksum{0};
        std::array<uint8_t, 2> global_checksum{0};
        std::array<uint8_t, 32768> rom{0};

        void LoadRom(std::string filename)
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
                                rom[i] = buffer[i];
                        }
                        delete[] buffer;
                }

                //load nintendo logo
                for (u_long i = 0; i < logo.size(); i++)
                {
                        logo[i] = rom[i + LOGO_START];
                }

                //load title
                for (u_long i = 0; i < title.size(); i++)
                {
                        title[i] = rom[i + TITLE_START];
                }

                //load manufacturer code
                for (u_long i = 0; i < mfct_code.size(); i++)
                {
                        mfct_code[i] = rom[i + MANUFACTURER_START];
                }

                //load cgb flag
                cgb_flag = rom[CGB_FLAG_START];

                //load new licensee code
                for (u_long i = 0; i < new_lics_code.size(); i++)
                {
                        new_lics_code[i] = rom[i + NEW_LICENSEE_START];
                }

                //load sgb flag
                sgb_flag = rom[SGB_FLAG_START];

                //load new cart type
                cart_type = rom[CART_TYPE_START];

                //load rom size
                rom_size = rom[ROM_SIZE_START];

                //load ram size
                ram_size = rom[RAM_SIZE_START];

                //load dest code
                dest_code = rom[DESTINATION_CODE_START];

                //load old licensee code
                old_lics_code = rom[OLD_LICENSEE_START];

                //load mask rom version
                mask_rom_version = rom[MASK_ROM_VERSION_START];

                //load header checksum
                header_checksum = rom[HEADER_CHECKSUM_START];

                //load global checksum
                for (u_long i = 0; i < global_checksum.size(); i++)
                {
                        global_checksum[i] = rom[i + GLOBAL_CHECKSUM_START];
                }
        }

        void DumpHeaderToConsole()
        {
                std::cout << "Nintendo Logo: ";
                for (auto &item : logo)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";

                std::cout << "Title: ";
                for (auto &item : title)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";

                std::cout << "Manufacturer Code: ";
                for (auto &item : mfct_code)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";

                std::cout << "CGB Flag: ";
                std::cout << std::hex << int(cgb_flag) << " ";
                std::cout << "\n";

                std::cout << "New Licensee Code: ";
                for (auto &item : new_lics_code)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";

                std::cout << "SGB Flag: ";
                std::cout << std::hex << int(sgb_flag) << " ";
                std::cout << "\n";

                // cart type
                std::cout << "Cart Type: ";
                std::cout << std::hex << int(cart_type) << " ";
                std::cout << "\n";

                // rom size
                std::cout << "Rom Size: ";
                std::cout << std::hex << int(rom_size) << " ";
                std::cout << "\n";

                // ram size
                std::cout << "Ram Size: ";
                std::cout << std::hex << int(ram_size) << " ";
                std::cout << "\n";

                // dest code
                std::cout << "Destination Code: ";
                std::cout << std::hex << int(dest_code) << " ";
                std::cout << "\n";

                // Old lics code
                std::cout << "Old Licensee Code: ";
                std::cout << std::hex << int(old_lics_code) << " ";
                std::cout << "\n";

                // mask rom
                std::cout << "Mask ROM Version: ";
                std::cout << std::hex << int(mask_rom_version) << " ";
                std::cout << "\n";

                // header check
                std::cout << "Header Checksum: ";
                std::cout << std::hex << int(header_checksum) << " ";
                std::cout << "\n";

                std::cout << "Global Checksum: ";
                for (auto &item : global_checksum)
                {
                        std::cout << std::hex << int(item) << " ";
                }
                std::cout << "\n";
        }

        void Write(uint8_t address, uint8_t data)
        {
                rom[address] = data;
        }

        uint8_t Read(uint8_t address)
        {
                return rom[address];
        }

}