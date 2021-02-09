//
// Created by gordo on 09.02.21.
//

#include "JumpToSubroutine.h"

int32_t MOS6502::JumpToSubroutine::Handle(uint32_t cycles, CPU &cpu, Memory &memory) {
    Word Address = cpu.FetchWord(cycles, memory);
    memory.WriteWord(cycles, cpu.SP, cpu.PC);
    cpu.SP++;
    cpu.PC = Address;
    cycles -= 2;
    return cycles;
}
