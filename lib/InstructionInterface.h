#ifndef CPU6502_INSTRUCTIONINTERFACE_H
#define CPU6502_INSTRUCTIONINTERFACE_H
#include "Types.h"
#include "Memory.h"
#include "CPU.h"
namespace MOS6502 {
    class InstructionInterface {
    public:
        virtual int32_t Handle(uint32_t cycles, CPU &cpu, Memory &memory) = 0;
        virtual ~InstructionInterface() {  };
    };
}
#endif //CPU6502_INSTRUCTIONINTERFACE_H
