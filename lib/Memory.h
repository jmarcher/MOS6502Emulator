#ifndef MOS6502EMULATOR_MEMORY_H
#define MOS6502EMULATOR_MEMORY_H

#include "Types.h"

class Memory {
public:
    static constexpr uint32_t MAX_MEMORY = 1024 * 64;
    Byte Data[MAX_MEMORY];

    void Initialise();

    Byte& operator[](uint32_t Address);

    void WriteWord(uint32_t & cycles, uint32_t Address, Word word);
};
#endif //MOS6502EMULATOR_MEMORY_H
