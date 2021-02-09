#include "gtest/gtest.h"
#include "CPU.h"
#include "Memory.h"
using namespace MOS6502;
class ResetMemoryTests : public testing::Test
{
public:
    Memory mem;
    CPU cpu;

    virtual void SetUp()
    {
        cpu.Reset( mem );
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ResetMemoryTests, TestResetStatusOfCPU )
{

// when:
cpu.Reset( mem );

// Test some random addresses
//then:
EXPECT_EQ( mem[0x0FFF], 0x0 );
EXPECT_EQ( mem[0x1000], 0x0 );
EXPECT_EQ( mem[0x1001], 0x0 );
EXPECT_EQ( mem[0x1002], 0x0 );
//....
EXPECT_EQ( mem[0x1009], 0x0 );
EXPECT_EQ( mem[0x100A], 0x0 );
EXPECT_EQ( mem[0x100B], 0x0 );
EXPECT_EQ( mem[0x100C], 0x0 );
EXPECT_EQ( mem[0xFFFF], 0x0 );
}
