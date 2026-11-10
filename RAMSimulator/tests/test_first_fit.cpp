#include "../include/allocators.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

// Ham ho tro kiem tra hai trang thai RAM
bool sameMemory(const MemoryState& a, const MemoryState& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i].id != b[i].id ||
            a[i].startKB != b[i].startKB ||
            a[i].freeKB != b[i].freeKB) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "========================================\n";
    std::cout << "   RUNNING FIRST FIT TEST SUITE (TV2)   \n";
    std::cout << "========================================\n\n";

    int passedCount = 0;
    int totalCount = 10;

    // TC01: Test case kinh dien (Silberschatz)
    {
        std::cout << "[TC01] Test case kinh dien: ";
        MemoryState memory = {
            {1, 0, 100},
            {2, 100, 500},
            {3, 600, 200},
            {4, 800, 300},
            {5, 1100, 600}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 212 });
        assert(r1.success && r1.holeId == 2 && r1.remainingKB == 288 && memory[1].startKB == 312);

        AllocationResult r2 = firstFit(memory, { "P2", 417 });
        assert(r2.success && r2.holeId == 5 && r2.remainingKB == 183 && memory[4].startKB == 1517);

        AllocationResult r3 = firstFit(memory, { "P3", 112 });
        assert(r3.success && r3.holeId == 2 && r3.remainingKB == 176 && memory[1].startKB == 424);

        AllocationResult r4 = firstFit(memory, { "P4", 426 });
        assert(!r4.success && r4.holeId == -1);
        assert(r4.reason == "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC02: Vua khit hoan toan (Exact Fit)
    {
        std::cout << "[TC02] Vua khit hoan toan: ";
        MemoryState memory = {
            {1, 0, 100},
            {2, 100, 200},
            {3, 300, 300}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 100 });
        assert(r1.success && r1.holeId == 1 && r1.remainingKB == 0 && memory[0].startKB == 100);

        AllocationResult r2 = firstFit(memory, { "P2", 200 });
        assert(r2.success && r2.holeId == 2 && r2.remainingKB == 0 && memory[1].startKB == 300);

        AllocationResult r3 = firstFit(memory, { "P3", 300 });
        assert(r3.success && r3.holeId == 3 && r3.remainingKB == 0 && memory[2].startKB == 600);

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC03: Khong du tong dung luong RAM trong
    {
        std::cout << "[TC03] Khong du tong dung luong RAM trong: ";
        MemoryState memory = {
            {1, 0, 100},
            {2, 100, 200}
        };
        MemoryState before = memory;

        AllocationResult r = firstFit(memory, { "P1", 500 });
        assert(!r.success && r.holeId == -1);
        assert(r.reason == "Khong du tong dung luong RAM trong.");
        assert(sameMemory(memory, before));

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC04: Mot khoi lon chia nhieu lan
    {
        std::cout << "[TC04] Mot khoi lon chia nhieu lan: ";
        MemoryState memory = {
            {1, 0, 1000}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 100 });
        assert(r1.success && r1.holeId == 1 && memory[0].startKB == 100 && memory[0].freeKB == 900);

        AllocationResult r2 = firstFit(memory, { "P2", 100 });
        assert(r2.success && r2.holeId == 1 && memory[0].startKB == 200 && memory[0].freeKB == 800);

        AllocationResult r3 = firstFit(memory, { "P3", 100 });
        assert(r3.success && r3.holeId == 1 && memory[0].startKB == 300 && memory[0].freeKB == 700);

        AllocationResult r4 = firstFit(memory, { "P4", 100 });
        assert(r4.success && r4.holeId == 1 && memory[0].startKB == 400 && memory[0].freeKB == 600);

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC05: Het cho giua chung
    {
        std::cout << "[TC05] Het cho giua chung: ";
        MemoryState memory = {
            {1, 0, 50},
            {2, 50, 50},
            {3, 100, 50}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 50 });
        AllocationResult r2 = firstFit(memory, { "P2", 50 });
        AllocationResult r3 = firstFit(memory, { "P3", 50 });
        assert(r1.success && r2.success && r3.success);

        AllocationResult r4 = firstFit(memory, { "P4", 50 });
        assert(!r4.success && r4.holeId == -1);
        assert(r4.reason == "Khong du tong dung luong RAM trong.");

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC06: Cac khoi bang nhau (Tie-break)
    {
        std::cout << "[TC06] Cac khoi bang nhau (Tie-break): ";
        MemoryState memory = {
            {1, 0, 100},
            {2, 100, 500},
            {3, 600, 100},
            {4, 700, 500}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 90 });
        assert(r1.success && r1.holeId == 1 && memory[0].freeKB == 10);

        AllocationResult r2 = firstFit(memory, { "P2", 90 });
        assert(r2.success && r2.holeId == 2 && memory[1].freeKB == 410);

        AllocationResult r3 = firstFit(memory, { "P3", 90 });
        assert(r3.success && r3.holeId == 2 && memory[1].freeKB == 320);

        AllocationResult r4 = firstFit(memory, { "P4", 90 });
        assert(r4.success && r4.holeId == 2 && memory[1].freeKB == 230);

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC07: Danh sach RAM trong rong
    {
        std::cout << "[TC07] Danh sach RAM trong rong: ";
        MemoryState memory = {};

        AllocationResult r = firstFit(memory, { "P1", 10 });
        assert(!r.success && r.holeId == -1);
        assert(r.reason == "Khong du tong dung luong RAM trong.");

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC08: Yeu cau bang 0 (Bien)
    {
        std::cout << "[TC08] Yeu cau bang 0 (Bien): ";
        MemoryState memory = { {1, 0, 100} };
        MemoryState before = memory;

        AllocationResult r = firstFit(memory, { "P1", 0 });
        assert(!r.success && r.holeId == -1);
        assert(r.reason == "Yeu cau cap phat khong hop le.");
        assert(sameMemory(memory, before));

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC09: Phan manh ngoai (External Fragmentation)
    {
        std::cout << "[TC09] Phan manh ngoai: ";
        MemoryState memory = {
            {1, 0, 300},
            {2, 400, 100},
            {3, 600, 200}
        };

        AllocationResult r1 = firstFit(memory, { "P1", 150 });
        assert(r1.success && r1.holeId == 1 && memory[0].freeKB == 150);

        AllocationResult r2 = firstFit(memory, { "P2", 150 });
        assert(r2.success && r2.holeId == 1 && memory[0].freeKB == 0);

        AllocationResult r3 = firstFit(memory, { "P3", 150 });
        assert(r3.success && r3.holeId == 3 && memory[2].freeKB == 50);

        AllocationResult r4 = firstFit(memory, { "P4", 150 });
        assert(!r4.success && r4.holeId == -1);
        assert(r4.reason == "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

        std::cout << "PASS\n";
        passedCount++;
    }

    // TC10: Du lieu am hoac ma tien trinh rong
    {
        std::cout << "[TC10] Du lieu am hoac ma tien trinh rong: ";
        MemoryState memory = { {1, 0, 100} };
        MemoryState before = memory;

        AllocationResult r1 = firstFit(memory, { "P1", -50 });
        assert(!r1.success && r1.holeId == -1);
        assert(r1.reason == "Yeu cau cap phat khong hop le.");

        AllocationResult r2 = firstFit(memory, { "", 50 });
        assert(!r2.success && r2.holeId == -1);
        assert(r2.reason == "Yeu cau cap phat khong hop le.");

        assert(sameMemory(memory, before));

        std::cout << "PASS\n";
        passedCount++;
    }

    std::cout << "\n----------------------------------------\n";
    std::cout << "KET QUA: " << passedCount << "/" << totalCount << " TESTS PASSED!\n";
    std::cout << "----------------------------------------\n";

    return (passedCount == totalCount) ? 0 : 1;
}

