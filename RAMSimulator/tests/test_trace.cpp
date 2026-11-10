
#include "../include/allocators.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

// Ham hien thi da viet trong trace.cpp
void printBestFitTrace(
    const MemoryState& before,
    const Request& request,
    const AllocationResult& result,
    const MemoryState& after,
    std::ostream& out
);

int main() {
    // TC07: Kiem tra hien thi cap phat thanh cong
    {
        MemoryState memory = {
            {1, 0, 100},
            {2, 150, 50},
            {3, 250, 200}
        };

        MemoryState before = memory;
        Request request{ "P1", 45 };

        AllocationResult result = bestFit(memory, request);

        std::ostringstream output;
        printBestFitTrace(
            before, request, result, memory, output
        );

        std::string text = output.str();

        assert(result.success);
        assert(text.find("Tien trinh: P1") != std::string::npos);
        assert(text.find("Chon H2") != std::string::npos);
        assert(text.find("[150, 195) KB") != std::string::npos);
        assert(text.find("5 KB") != std::string::npos);

        // Ham trace khong duoc thay doi RAM
        assert(before[1].startKB == 150);
        assert(before[1].freeKB == 50);
        assert(memory[1].startKB == 195);
        assert(memory[1].freeKB == 5);

        std::cout << "TC07: PASS\n";
    }

    // TC08: Kiem tra hien thi phan manh ngoai
    {
        MemoryState memory = {
            {1, 0, 40},
            {2, 50, 2},
            {3, 70, 20}
        };

        MemoryState before = memory;
        Request request{ "P2", 45 };

        AllocationResult result = bestFit(memory, request);

        std::ostringstream output;
        printBestFitTrace(
            before, request, result, memory, output
        );

        std::string text = output.str();

        assert(!result.success);
        assert(text.find("THAT BAI") != std::string::npos);
        assert(text.find("phan manh ngoai")
            != std::string::npos);

        // Cap phat that bai khong thay doi RAM
        assert(memory.size() == before.size());
        assert(memory[0].freeKB == 40);
        assert(memory[1].freeKB == 2);
        assert(memory[2].freeKB == 20);

        std::cout << "TC08: PASS\n";
    }

    std::cout << "\nALL TRACE TESTS PASSED!\n";
    return 0;
}
