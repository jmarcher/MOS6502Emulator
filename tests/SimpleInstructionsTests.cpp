#include "gtest/gtest.h"
#include "CPU.h"
#include "Memory.h"
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
    cpu.Execute(1, memory);

    ASSERT_EQ(CPU::PC_START_ADDRESS + 1, cpu.PC);
}

