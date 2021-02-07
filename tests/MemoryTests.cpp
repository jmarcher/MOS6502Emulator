#include "gtest/gtest.h"
#include "Memory.h"
class MemoryTests : public testing::Test
{
public:
    Memory memory;

    virtual void SetUp()
    {
        memory.Initialise();
    }

    virtual void TearDown()
    {
    }
};

TEST_F(MemoryTests, TestMemoryFunctions)
{
    const unsigned int address = memory[0x1];
    ASSERT_EQ(memory[0x0], 0x0);
    ASSERT_EQ(address, 0x0);
}