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

    // Test 8: Tong RAM khong du
    MemoryState tooSmall = { {1, 0, 50}, {2, 100, 70} };
    Request p4 = { "P4", 150 };

    assert(allocationFailureReason(tooSmall, p4) ==
        "Khong du tong dung luong RAM trong.");

    std::cout << "TEST 8: PASS\n";

    // Test 9: Dung luong cap phat bang 0
    int oldStart = memory[0].startKB;
    int oldFree = memory[0].freeKB;

    AllocationResult zeroSize =
        allocateFromHole(memory, 0, { "P0", 0 });

    assert(!zeroSize.success);
    assert(memory[0].startKB == oldStart);
    assert(memory[0].freeKB == oldFree);

    std::cout << "TEST 9: PASS\n";

    // Test 10: Dung luong am va ma tien trinh rong
    assert(!allocateFromHole(memory, 0, { "P5", -10 }).success);
    assert(!allocateFromHole(memory, 0, { "", 10 }).success);

    std::cout << "TEST 10: PASS\n";

    // Test 11: Chi so vung RAM khong ton tai
    AllocationResult badHole =
        allocateFromHole(memory, memory.size(), { "P6", 20 });

    assert(!badHole.success);
    assert(badHole.reason == "Vung RAM khong ton tai.");

    std::cout << "TEST 11: PASS\n";

    // Test 12: Vung RAM duoc chon khong du
    AllocationResult insufficientHole =
        allocateFromHole(memory, 0, { "P7", 200 });

    assert(!insufficientHole.success);
    assert(insufficientHole.reason == "Vung RAM khong du dung luong.");
    assert(memory[0].startKB == oldStart);
    assert(memory[0].freeKB == oldFree);

    std::cout << "TEST 12: PASS\n";

    std::cout << "\nHOAN THANH KIEM THU MEMORY!\n";

    return 0;
}