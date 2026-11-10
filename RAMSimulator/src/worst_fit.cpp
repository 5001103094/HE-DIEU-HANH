
#include "../include/allocators.hpp"
#include "../include/memory.hpp"

// TV4 - Thuat toan Worst Fit
AllocationResult worstFit(
    MemoryState& memory,
    const Request& request)
{
    // 1. Kiem tra yeu cau hop le
    if (request.pid.empty() || request.requiredKB <= 0)
    {
        AllocationResult result;
        result.pid = request.pid;
        result.reason = "Yeu cau cap phat khong hop le.";
        return result;
    }

    // 2. Tim vung RAM trong lon nhat
    int selectedIndex = -1;

    for (int i = 0; i < static_cast<int>(memory.size()); ++i)
    {
        if (memory[i].freeKB >= request.requiredKB)
        {
            if (selectedIndex == -1 ||
                memory[i].freeKB > memory[selectedIndex].freeKB ||
                (memory[i].freeKB == memory[selectedIndex].freeKB &&
                    memory[i].startKB < memory[selectedIndex].startKB))
            {
                selectedIndex = i;
            }
        }
    }

    // 3. Xu ly khi khong tim duoc vung phu hop
    if (selectedIndex == -1)
    {
        AllocationResult result;
        result.pid = request.pid;
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // 4. Goi ham cap phat chung cua TV1
    return allocateFromHole(
        memory,
        static_cast<std::size_t>(selectedIndex),
        request
    );
}
