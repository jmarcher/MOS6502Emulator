#include "gtest/gtest.h"
#include "CPU.h"
#include "Memory.h"
class SimpleLoadAndJumpTests : public testing::Test
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

TEST_F(SimpleLoadAndJumpTests, TestThatTheFlagsAreCorrectlySetAfterLDA )
{

// when:
    memory[CPU::PC_START_ADDRESS] = CPU::INS_JPR;
    memory[CPU::PC_START_ADDRESS + 1] = 0x42;
    memory[CPU::PC_START_ADDRESS + 2] = 0x42;
    memory[0x4242] = CPU::INS_LDA_IM;
    memory[0x4243] = 0x84;
    cpu.Execute(9, memory);

// Test that the flags are correct
//then:
    EXPECT_EQ( cpu.A, 0x84 );
    EXPECT_EQ( cpu.Z, 0x0 );
    EXPECT_EQ( cpu.N, 0x1 );
}

TEST_F(SimpleLoadAndJumpTests, TestThatTheFlagsAreCorrectlySetAfterLDAWithNEqualsZero )
{

// when:
    memory[CPU::PC_START_ADDRESS] = CPU::INS_JPR;
    memory[CPU::PC_START_ADDRESS + 1] = 0x42;
    memory[CPU::PC_START_ADDRESS + 2] = 0x42;
    memory[0x4242] = CPU::INS_LDA_IM;
    memory[0x4243] = 0x0;
    cpu.Execute(9, memory);

// Test that the flags are correct
//then:
    EXPECT_EQ( cpu.A, 0x0 );
    EXPECT_EQ( cpu.Z, 0x1 );
    EXPECT_EQ( cpu.N, 0x0 );
}

TEST_F(SimpleLoadAndJumpTests, ItSouldPrintAnErrorWhenOptCodeNotRecognized )
{
    testing::internal::CaptureStderr();
// when:
    memory[CPU::PC_START_ADDRESS] = 0x02;
    cpu.Execute(1, memory);
    std::string output = testing::internal::GetCapturedStderr();
// Test that the flags are correct
//then:
    EXPECT_EQ( output, "Instruction not handled: \x2\n" );
}