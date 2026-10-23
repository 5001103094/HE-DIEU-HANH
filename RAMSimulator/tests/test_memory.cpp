#include <iostream>
#include <cassert>
#include "../include/memory.hpp"

int main()
{
    // Tao ba vung RAM trong
    MemoryState original = {
        {1, 0, 100},
        {2, 200, 250},
        {3, 500, 400}
    };

    // Test 1: Tinh tong RAM trong
    assert(totalFreeKB(original) == 750);
    std::cout << "TEST 1: PASS\n";

    // Test 2: Tim vung RAM trong lon nhat
    assert(largestHoleKB(original) == 400);
    std::cout << "TEST 2: PASS\n";

    // Test 3: Sao chep trang thai RAM
    MemoryState memory = copyMemory(original);

    Request p1 = { "P1", 150 };

    AllocationResult result =
        allocateFromHole(memory, 1, p1);

    assert(result.success == true);
    assert(result.holeId == 2);
    assert(result.remainingKB == 100);

    std::cout << "TEST 3: PASS\n";

    // Test 4: Cap nhat dia chi va dung luong
    assert(memory[1].startKB == 350);
    assert(memory[1].freeKB == 100);

    std::cout << "TEST 4: PASS\n";

    // Test 5: RAM goc khong bi thay doi
    assert(original[1].startKB == 200);
    assert(original[1].freeKB == 250);

    std::cout << "TEST 5: PASS\n";

    // Test 6: Phat hien phan manh ngoai
    MemoryState fragmented = {
        {1, 0, 60},
        {2, 80, 90},
        {3, 190, 40}
    };

    Request p2 = { "P2", 120 };

    assert(allocationFailureReason(fragmented, p2) ==
        "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

    std::cout << "TEST 6: PASS\n";

    // Test 7: Cap phat that bai khong lam thay doi RAM
    Request p3 = { "P3", 500 };

    AllocationResult failed =
        allocateFromHole(memory, 1, p3);

    assert(failed.success == false);
    assert(memory[1].startKB == 350);
    assert(memory[1].freeKB == 100);

    std::cout << "TEST 7: PASS\n";

    std::cout << "\nHOAN THANH KIEM THU MEMORY!\n";

    return 0;
}