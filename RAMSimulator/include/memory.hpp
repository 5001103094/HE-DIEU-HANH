#pragma once

#include "models.hpp"
#include <cstddef>

// TV1 - Tinh tong dung luong RAM trong
long long totalFreeKB(const MemoryState& memory);

// TV1 - Tim vung RAM trong lon nhat
int largestHoleKB(const MemoryState& memory);

// TV1 - Sao chep trang thai RAM
MemoryState copyMemory(const MemoryState& memory);

// TV1 - Xac dinh nguyen nhan cap phat that bai
std::string allocationFailureReason(
    const MemoryState& memory,
    const Request& request
);

// TV1 - Cap phat RAM tu dau vung trong duoc chon
AllocationResult allocateFromHole(
    MemoryState& memory,
    std::size_t holeIndex,
    const Request& request
);