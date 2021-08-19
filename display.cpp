#include "display.h"
#include "memory.h"
#include <iostream>

namespace Display
{
        std::array<uint32_t, 65536> bg{0};

        LCDC lcdc{0};
        STAT stat{0};

        void BuildBG()
        {
                
        }
}