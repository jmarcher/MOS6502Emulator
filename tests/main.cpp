#if 0
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
#endif

#include "gtest/gtest.h"

#if GTEST_OS_ESP8266 || GTEST_OS_ESP32
#if GTEST_OS_ESP8266
extern "C" {
#endif
    void setup() {
        testing::InitGoogleTest();
    }

    void loop() { RUN_ALL_TESTS(); }

#if GTEST_OS_ESP8266
}
#endif

#else

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
