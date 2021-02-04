#ifndef CPU6502_CPU_H
#define CPU6502_CPU_H
#include "Types.h"
#include "Memory.h"

struct CPU {

    Word PC; // Program counter
    Word SP; // Stack pointer
    Byte A, X, Y; // Registers

    Byte C: 1; // Status flag
    Byte Z: 1; // Status flag
    Byte I: 1; // Status flag
    Byte D: 1; // Status flag
    Byte B: 1; // Status flag
    Byte V: 1; // Status flag
    Byte N: 1; // Status flag

    // Optcodes
    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;
    static constexpr Byte INS_LDA_ZPX = 0xB5;
    static constexpr Byte INS_JPR = 0x20;

    void Reset(Memory &memory);

    Byte FetchByte(uint32_t& cycles, Memory &memory);
    Word FetchWord(uint32_t& cycles, Memory &memory);
    static Byte ReadByte(uint32_t &cycles, Byte &address, Memory &memory);

    void LDASetStatusFlags();

    void Execute(uint32_t cycles, Memory &memory);
};
#endif //CPU6502_CPU_H