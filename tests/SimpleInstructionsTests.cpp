#include "gtest/gtest.h"
#include "CPU.h"
#include "Memory.h"
using namespace MOS6502;
class SimpleInstructionsTests : public testing::Test
{
public:
    Memory memory;
    CPU cpu;

    virtual void SetUp()
    {
        cpu.Reset( memory );
    }

    virtual void TearDown()
    {
    }
};

TEST_F(SimpleInstructionsTests, ItShouldIncrementPCOnNOP)
{
    memory[CPU::PC_START_ADDRESS] = CPU::INS_NOP;
    int32_t  cyclesUsed = cpu.Execute(2, memory);

    ASSERT_EQ(CPU::PC_START_ADDRESS + 1, cpu.PC);
    EXPECT_EQ(cyclesUsed, 2);
}

