#include "include/allocators.hpp"
#include "include/memory.hpp"
#include <cstddef>

// Thuat toan First Fit - TV2
// Chon vung RAM trong dau tien (theo thu tu dia chi tu thap den cao) co dung luong >= yeu cau
AllocationResult firstFit(
    MemoryState& memory,
    const Request& request
) {
    AllocationResult result;
    result.pid = request.pid;

    // Buoc 1: Kiem tra tinh hop le cua yeu cau cap phat
    if (request.pid.empty() || request.requiredKB <= 0) {
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // Buoc 2: Khoi tao vi tri vung nho tim duoc
    std::size_t foundIndex = memory.size();

    // Buoc 3: Duyet tuan tu tu dau danh sach (dia chi thap den cao)
    for (std::size_t i = 0; i < memory.size(); ++i) {
        // Tim vung trong dau tien co dung luong du dap ung
        if (memory[i].freeKB >= request.requiredKB) {
            foundIndex = i;
            break; // First Fit: chon vung dau tien va dung tim kiem ngay
        }
    }

    // Buoc 4: Neu khong tim thay vung phu hop
    if (foundIndex == memory.size()) {
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // Buoc 5: Thuc hien cap phat bang cach goi ham dung chung cua TV1
    return allocateFromHole(memory, foundIndex, request);
}
