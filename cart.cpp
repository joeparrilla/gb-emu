#include "cart.h"
#include <iostream>
#include <fstream>
#include <bitset>

Cart::Cart()
{
}

void Cart::LoadRom(std::string filename)
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

void Cart::DumpHeaderToConsole()
{
        std::bitset<8> converted;

        std::cout << "Nintendo Logo: ";
        for (int i{0}; auto &item : logo)
        {
                std::bitset<8> converted(item);
                std::cout << std::hex << converted.to_ulong() << " ";
                ++i;
        }
        std::cout << "\n";

        std::cout << "Title: ";
        for (int i{0}; auto &item : title)
        {
                std::bitset<8> converted(item);
                std::cout << std::hex << converted.to_ulong() << " ";
                ++i;
        }
        std::cout << "\n";

        std::cout << "Manufacturer Code: ";
        for (int i{0}; auto &item : mfct_code)
        {
                std::bitset<8> converted(item);
                std::cout << std::hex << converted.to_ulong() << " ";
                ++i;
        }
        std::cout << "\n";

        //cgb flag
        std::cout << "CGB Flag: ";
        converted = cgb_flag;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        std::cout << "New Licensee Code: ";
        for (int i{0}; auto &item : new_lics_code)
        {
                std::bitset<8> converted(item);
                std::cout << std::hex << converted.to_ulong() << " ";
                ++i;
        }
        std::cout << "\n";

        //sgb flag
        std::cout << "SGB Flag: ";
        converted = sgb_flag;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // cart type
        std::cout << "Cart Type: ";
        converted = cart_type;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // rom size
        std::cout << "Rom Size: ";
        converted = rom_size;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // ram size
        std::cout << "Ram Size: ";
        converted = ram_size;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // dest code
        std::cout << "Destination Code: ";
        converted = dest_code;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // Old lics code
        std::cout << "Old Licensee Code: ";
        converted = old_lics_code;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // mask rom
        std::cout << "Mask ROM Version: ";
        converted = mask_rom_version;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        // header check
        std::cout << "Header Checksum: ";
        converted = header_checksum;
        std::cout << std::hex << converted.to_ulong() << " ";        
        std::cout << "\n";

        std::cout << "Global Checksum: ";
        for (int i{0}; auto &item : global_checksum)
        {
                std::bitset<8> converted(item);
                std::cout << std::hex << converted.to_ulong() << " ";
                ++i;
        }
        std::cout << "\n";
}