#ifndef MOS6502EMULATOR_MEMORY_H
#define MOS6502EMULATOR_MEMORY_H

#include "Types.h"

class Memory {
public:
    static constexpr uint32_t MAX_MEMORY = 1024 * 64;
    MOS6502::Byte Data[MAX_MEMORY];

    void Initialise();

    MOS6502::Byte& operator[](uint32_t Address);

    void WriteWord(uint32_t & cycles, uint32_t Address, MOS6502::Word word);
};
#endif //MOS6502EMULATOR_MEMORY_H
