#include "include/allocators.hpp"
#include "include/memory.hpp"
#include <cstddef>

// Thuat toan First Fit - TV2
// Tim va chon vung RAM trong dau tien co kich thuoc >= yeu cau
AllocationResult firstFit(
    MemoryState& memory,
    const Request& request
) {
    AllocationResult result;
    result.pid = request.pid;

    // TODO: Cai dat chi tiet thuat toan First Fit tai Buoc 3
    // Tam thoi tra ve ket qua mac dinh (success = false, chua cap phat)

    return result;
}

