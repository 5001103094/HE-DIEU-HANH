
#include "../include/allocators.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>

// Kiem tra hai trang thai RAM co giong nhau khong
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
    // TC01: Chon vung nho nhat du lon
    {
        MemoryState memory = {
            {1, 0, 100},
            {2, 150, 50},
            {3, 250, 200}
        };

        AllocationResult r = bestFit(memory, { "P1", 45 });

        assert(r.success);
        assert(r.holeId == 2);
        assert(r.remainingKB == 5);
        assert(memory[1].startKB == 195);
        assert(memory[1].freeKB == 5);
        assert(memory[0].freeKB == 100);
        assert(memory[2].freeKB == 200);

        std::cout << "TC01: PASS\n";
    }

    // TC02: Hai vung bang nhau, chon startKB nho hon
    {
        MemoryState memory = {
            {1, 80, 20},
            {2, 50, 20},
            {3, 0, 40}
        };

        AllocationResult r = bestFit(memory, { "P2", 18 });

        assert(r.success);
        assert(r.holeId == 2);
        assert(memory[1].startKB == 68);
        assert(memory[1].freeKB == 2);

        std::cout << "TC02: PASS\n";
    }

    // TC03: Cap phat vua du dung luong
    {
        MemoryState memory = { {1, 100, 30} };

        AllocationResult r = bestFit(memory, { "P3", 30 });

        assert(r.success);
        assert(r.remainingKB == 0);
        assert(memory[0].startKB == 130);
        assert(memory[0].freeKB == 0);

        std::cout << "TC03: PASS\n";
    }

    // TC04: Khong co vung du lon (phan manh ngoai)
    {
        MemoryState memory = {
            {1, 0, 40},
            {2, 50, 2},
            {3, 70, 20}
        };
        MemoryState before = memory;

        AllocationResult r = bestFit(memory, { "P4", 45 });

        assert(!r.success);
        assert(r.holeId == -1);
        assert(sameMemory(memory, before));

        std::cout << "TC04: PASS\n";
    }

    // TC05: Yeu cau khong hop le
    {
        MemoryState memory = { {1, 0, 100} };
        MemoryState before = memory;

        AllocationResult r = bestFit(memory, { "P5", 0 });

        assert(!r.success);
        assert(sameMemory(memory, before));

        std::cout << "TC05: PASS\n";
    }

    // TC06: Cap phat nhieu tien trinh lien tiep
    {
        MemoryState memory = { {1, 0, 100} };

        AllocationResult r1 = bestFit(memory, { "P1", 30 });
        AllocationResult r2 = bestFit(memory, { "P2", 40 });

        assert(r1.success && r2.success);
        assert(memory[0].startKB == 70);
        assert(memory[0].freeKB == 30);

        std::cout << "TC06: PASS\n";
    }

    std::cout << "\nALL BEST FIT TESTS PASSED!\n";
    return 0;
}
