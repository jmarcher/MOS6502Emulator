#include <iostream>
#include "CPU.h"

#include "Instructions/JumpToSubroutine.h"

void MOS6502::CPU::Reset(Memory &memory) {
    PC = PC_START_ADDRESS;
    SP = SP_START_ADDRESS;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    memory.Initialise();
}

MOS6502::Byte MOS6502::CPU::FetchByte(uint32_t &cycles, Memory &memory) {
    Byte data = memory[PC];
    PC ++;
    cycles--;
    return data;
}

MOS6502::Word MOS6502::CPU::FetchWord(uint32_t &cycles, Memory &memory) {
    // 6502 is little endian
    Word data = memory[PC];
    PC ++;
    data |= memory[PC] << 8;
    cycles -= 2;

    return data;
}

MOS6502::Byte MOS6502::CPU::ReadByte(uint32_t &cycles, Byte &address, Memory &memory) {
    Byte data = memory[address];
    cycles--;
    return data;
}

void MOS6502::CPU::LDASetStatusFlags() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

int32_t MOS6502::CPU::Execute(uint32_t cycles, Memory &memory) {
    const uint32_t cyclesRequested = cycles;
    while(cycles > 0){
        Byte instruction = FetchByte(cycles, memory);
        switch (instruction) {
            case INS_NOP:
                {
                    cycles--;
                }
            break;
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
                JumpToSubroutine jpr{};
                cycles = jpr.Handle(cycles, *this, memory);
            }
                break;
            default:
                std::cerr << "Instruction not handled: " << instruction << std::endl;
        }
    }

    return cyclesRequested - cycles;
}
