#include "gtest/gtest.h"
#include "CPU.h"
#include "Memory.h"
class LDATests : public testing::Test
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

TEST_F(LDATests, TestThatAfterLoadingAImmediatlyTheFlagsAreCorrectlySet)
{
    // When
    memory[CPU::PC_START_ADDRESS] = CPU::INS_LDA_IM;
    memory[CPU::PC_START_ADDRESS + 1] = 0x84;
    cpu.Execute(2, memory);

// Test that the flags are correct
//then:
    EXPECT_EQ( cpu.A, 0x84 );
    EXPECT_EQ( cpu.Z, 0x0 );
    EXPECT_EQ( cpu.N, 0x1 );

}

TEST_F(LDATests, TestThatAfterLoadingAImmediatlyTheFlagsAreCorrectlySetWithDifferentValues)
{
    // When
    memory[CPU::PC_START_ADDRESS] = CPU::INS_LDA_IM;
    memory[CPU::PC_START_ADDRESS + 1] = 0x0;
    cpu.Execute(2, memory);

// Test that the flags are correct
//then:
    EXPECT_EQ( cpu.A, 0x0 );
    EXPECT_EQ( cpu.Z, 0x1 );
    EXPECT_EQ( cpu.N, 0x0 );

}