
#include "../include/allocators.hpp"
#include "../include/memory.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

void testTC01()
{
    MemoryState memory = {
        { 1, 0, 300 },
        { 2, 300, 600 },
        { 3, 900, 350 },
        { 4, 1250, 200 },
        { 5, 1450, 750 },
        { 6, 2200, 125 }
    };

    std::vector<Request> requests = {
        { "P1", 115 },{ "P2", 500 },{ "P3", 358 },
        { "P4", 200 },{ "P5", 375 }
    };

    int success = 0;
    for (const Request& request : requests)
    {
        AllocationResult result = worstFit(memory, request);
        if (result.success) ++success;
    }

    assert(success == 4);
    assert(totalFreeKB(memory) == 1152);
    assert(largestHoleKB(memory) == 300);
    std::cout << "TC01 PASS\n";
}

void testTC02()
{
    MemoryState memory = {
        { 1, 0, 100 },{ 2, 100, 250 },{ 3, 350, 400 }
    };

    AllocationResult result = worstFit(memory, { "P1", 250 });

    assert(result.success);
    assert(result.holeId == 3);
    assert(result.remainingKB == 150);
    assert(memory[2].startKB == 600);
    std::cout << "TC02 PASS\n";
}

void testTC03()
{
    MemoryState memory = {
        { 1, 0, 50 },{ 2, 50, 70 }
    };

    AllocationResult result = worstFit(memory, { "P1", 150 });

    assert(!result.success);
    assert(result.reason ==
        "Khong du tong dung luong RAM trong.");
    assert(totalFreeKB(memory) == 120);
    std::cout << "TC03 PASS\n";
}

void testTC04()
{
    MemoryState memory = {
        { 1, 0, 60 },{ 2, 60, 90 },{ 3, 150, 40 }
    };

    AllocationResult result = worstFit(memory, { "P1", 120 });

    assert(!result.success);
    assert(result.reason ==
        "Phan manh ngoai: khong co vung RAM lien tuc du lon.");
    assert(totalFreeKB(memory) == 190);
    std::cout << "TC04 PASS\n";
}

void testTC05()
{
    MemoryState memory = {
        { 1, 0, 200 },{ 2, 200, 200 },{ 3, 400, 400 }
    };

    AllocationResult result = worstFit(memory, { "P1", 150 });

    assert(result.success);
    assert(result.holeId == 3);
    assert(result.remainingKB == 250);
    std::cout << "TC05 PASS\n";
}

void testTC06()
{
    MemoryState memory = {
        { 1, 0, 100 },{ 2, 100, 400 },{ 3, 500, 220 }
    };

    AllocationResult p1 = worstFit(memory, { "P1", 200 });
    AllocationResult p2 = worstFit(memory, { "P2", 210 });

    assert(p1.success && p1.holeId == 2);
    assert(p2.success && p2.holeId == 3);
    assert(totalFreeKB(memory) == 310);
    std::cout << "TC06 PASS\n";
}

void testInvalid()
{
    MemoryState memory = { { 1, 0, 200 } };

    AllocationResult r1 = worstFit(memory, { "P1", 0 });
    AllocationResult r2 = worstFit(memory, { "P2", -10 });
    AllocationResult r3 = worstFit(memory, { "", 50 });

    assert(!r1.success);
    assert(!r2.success);
    assert(!r3.success);
    assert(memory[0].freeKB == 200);
    std::cout << "INVALID PASS\n";
}

void testTieBreak()
{
    MemoryState memory = {
        { 1, 500, 300 },
        { 2, 100, 300 },
        { 3, 900, 100 }
    };

    AllocationResult result = worstFit(memory, { "P1", 150 });

    // Khi kich thuoc bang nhau, chon startKB nho nhat.
    assert(result.success);
    assert(result.holeId == 2);
    std::cout << "TIE BREAK PASS\n";
}

void testIndependentMemory()
{
    MemoryState original = {
        { 1, 0, 300 },{ 2, 300, 500 }
    };

    MemoryState copy = copyMemory(original);
    worstFit(copy, { "P1", 250 });

    assert(original[0].freeKB == 300);
    assert(original[1].freeKB == 500);
    std::cout << "INDEPENDENT MEMORY PASS\n";
}

int main()
{
    testTC01();
    testTC02();
    testTC03();
    testTC04();
    testTC05();
    testTC06();
    testInvalid();
    testTieBreak();
    testIndependentMemory();

    std::cout << "ALL WORST FIT TESTS PASSED\n";
    return 0;
}
