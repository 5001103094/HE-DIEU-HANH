
#include "include/allocators.hpp"
#include <cstddef>

// CV02 - Thuat toan Best Fit - TV3
AllocationResult bestFit(
    MemoryState& memory,
    const Request& request
) {
    AllocationResult result;
    result.pid = request.pid;

    // Buoc 1: Kiem tra yeu cau cap phat
    if (request.pid.empty() || request.requiredKB <= 0) {
        result.reason = "Yeu cau cap phat khong hop le";
        return result;
    }

    // Buoc 2: Khoi tao vi tri vung nho
    std::size_t bestIndex = memory.size();

    // Buoc 3: Duyet danh sach cac vung RAM trong
    for (std::size_t i = 0; i < memory.size(); ++i) {
        const Hole& hole = memory[i];

        // Bo qua vung khong du dung luong
        if (hole.freeKB < request.requiredKB) {
            continue;
        }

        // Chon vung nho nhat du lon
        // Neu bang kich thuoc, uu tien startKB nho nhat
        if (bestIndex == memory.size() ||
            hole.freeKB < memory[bestIndex].freeKB ||
            (hole.freeKB == memory[bestIndex].freeKB &&
                hole.startKB < memory[bestIndex].startKB)) {
            bestIndex = i;
        }
    }

    // Buoc 4: Khong tim thay vung phu hop
    if (bestIndex == memory.size()) {
        result.reason = "Khong co vung RAM trong du lon";
        return result;
    }

    // Buoc 5: Lay vung nho duoc chon
    Hole& selected = memory[bestIndex];

    result.success = true;
    result.holeId = selected.id;

    // Buoc 6: Cap phat tu dau vung nho
    selected.startKB += request.requiredKB;
    selected.freeKB -= request.requiredKB;

    // Buoc 7: Ghi nhan dung luong con lai
    result.remainingKB = selected.freeKB;

    return result;
}
