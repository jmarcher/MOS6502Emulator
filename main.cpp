#include <iostream>
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

    void Reset(Memory &memory) {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();
    }
    Byte FetchByte(uint32_t& cycles, Memory &memory) {
        Byte data = memory[PC];
        PC ++;
        cycles--;
        return data;
    }

    Word FetchWord(uint32_t& cycles, Memory &memory) {
        // 6502 is little endian
        Word data = memory[PC];
        PC ++;
        data |= memory[PC] << 8;
        cycles -= 2;

        return data;
    }

    Byte ReadByte(uint32_t &cycles, Byte &address, Memory &memory) {
        Byte data = memory[address];
        cycles--;
        return data;
    }

    void LDASetStatusFlags()
    {
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }

    void Execute(uint32_t cycles, Memory &memory) {
        while(cycles > 0){
            Byte instruction = FetchByte(cycles, memory);
            switch (instruction) {
                case INS_LDA_IM:
                {
                    Byte value = FetchByte(cycles, memory);
                    A = value;
                    LDASetStatusFlags();
                }
                break;
                case INS_LDA_ZP:
                {
                    Byte ZeroPageAddress = FetchByte(cycles, memory);
                    A = ReadByte(cycles, ZeroPageAddress, memory);
                    LDASetStatusFlags();
                }
                break;
                case INS_LDA_ZPX:
                {
                     Byte ZeroPageAddress = FetchByte(cycles, memory);
                     ZeroPageAddress += X;
                     cycles--;
                     A = ReadByte(cycles, ZeroPageAddress, memory);
                     LDASetStatusFlags();
                }
                break;
                case INS_JPR:
                {
                    Word Address = FetchWord(cycles, memory);
                    memory.WriteWord(cycles, SP, PC);
                    SP++;
                    PC = Address;
                    cycles -= 2;
                }
                break;
                default:
                    std::cout << "Instruction not handled: " << instruction << std::endl;
            }
        }
    }
};

int main() {
    Memory memory{};
    CPU cpu{};
    cpu.Reset(memory);

    // Start of Inline Program
    memory[0xFFFC] = CPU::INS_JPR;
    memory[0xFFFD] = 0x42;
    memory[0xFFFE] = 0x42;
    memory[0x4242] = CPU::INS_LDA_IM;
    memory[0x4243] = 0x84;
    // End of inline program

    cpu.Execute(9, memory);
    return 0;
}
