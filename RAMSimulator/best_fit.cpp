
#include "include/allocators.hpp"
#include "include/memory.hpp"
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
        result.reason = allocationFailureReason(memory, request);
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
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // Buoc 5: Goi ham cap phat chung cua TV1
    return allocateFromHole(memory, bestIndex, request);
}
