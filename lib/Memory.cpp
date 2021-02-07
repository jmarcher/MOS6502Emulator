//
// Created by gordo on 03.02.21.
//

#include "Memory.h"
#include <cassert>

void Memory::Initialise()  {
    for (unsigned char & i : Data) {
        i = 0;
    }
}

Byte& Memory::operator[](uint32_t Address){
    assert(Address < MAX_MEMORY);
    return Data[Address];
}

void Memory::WriteWord(uint32_t & cycles, uint32_t Address, Word word)
{
    Data[Address] = word & 0xFF;
    Data[Address + 1] = (word >> 8);
    cycles -= 2;
}
