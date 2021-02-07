#include <iostream>
#include "CPU.h"

void CPU::Reset(Memory &memory) {
    PC = PC_START_ADDRESS;
    SP = SP_START_ADDRESS;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    memory.Initialise();
}

Byte CPU::FetchByte(uint32_t &cycles, Memory &memory) {
    Byte data = memory[PC];
    PC ++;
    cycles--;
    return data;
}

Word CPU::FetchWord(uint32_t &cycles, Memory &memory) {
    // 6502 is little endian
    Word data = memory[PC];
    PC ++;
    data |= memory[PC] << 8;
    cycles -= 2;

    return data;
}

Byte CPU::ReadByte(uint32_t &cycles, Byte &address, Memory &memory) {
    Byte data = memory[address];
    cycles--;
    return data;
}

void CPU::LDASetStatusFlags() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::Execute(uint32_t cycles, Memory &memory) {
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
                std::cerr << "Instruction not handled: " << instruction << std::endl;
        }
    }
}
