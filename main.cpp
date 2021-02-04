#include "lib/Memory.h"
#include "lib/CPU.h"

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
