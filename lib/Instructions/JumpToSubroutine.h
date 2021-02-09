#ifndef CPU6502_JUMPTOSUBROUTINE_H
#define CPU6502_JUMPTOSUBROUTINE_H
#include "InstructionInterface.h"
namespace MOS6502 {
    class JumpToSubroutine: public InstructionInterface {
    public:
        int32_t Handle(uint32_t cycles, CPU &cpu, Memory &memory) override;
    };
}

#endif //CPU6502_JUMPTOSUBROUTINE_H
