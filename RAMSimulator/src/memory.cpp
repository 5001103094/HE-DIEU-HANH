#include "../include/memory.hpp"

// 1. Tinh tong dung luong RAM con trong
long long totalFreeKB(const MemoryState& memory)
{
    long long total = 0;

    for (const Hole& hole : memory)
    {
        total += hole.freeKB;
    }

    return total;
}

// 2. Tim vung RAM trong lon nhat
int largestHoleKB(const MemoryState& memory)
{
    int largest = 0;

    for (const Hole& hole : memory)
    {
        if (hole.freeKB > largest)
        {
            largest = hole.freeKB;
        }
    }

    return largest;
}

// 3. Sao chep trang thai RAM
MemoryState copyMemory(const MemoryState& memory)
{
    return memory;
}

// 4. Xac dinh nguyen nhan cap phat that bai
std::string allocationFailureReason(
    const MemoryState& memory,
    const Request& request)
{
    if (request.pid.empty() || request.requiredKB <= 0)
    {
        return "Yeu cau cap phat khong hop le.";
    }

    if (totalFreeKB(memory) < request.requiredKB)
    {
        return "Khong du tong dung luong RAM trong.";
    }

    if (largestHoleKB(memory) < request.requiredKB)
    {
        return "Phan manh ngoai: khong co vung RAM lien tuc du lon.";
    }

    return "";
}

// 5. Cap phat RAM tu dau vung trong duoc chon
AllocationResult allocateFromHole(
    MemoryState& memory,
    std::size_t holeIndex,
    const Request& request)
{
    AllocationResult result;
    result.pid = request.pid;

    if (request.pid.empty() || request.requiredKB <= 0)
    {
        result.reason = "Yeu cau cap phat khong hop le.";
        return result;
    }

    if (holeIndex >= memory.size())
    {
        result.reason = "Vung RAM khong ton tai.";
        return result;
    }

    Hole& selectedHole = memory[holeIndex];

    if (selectedHole.freeKB < request.requiredKB)
    {
        result.reason = "Vung RAM khong du dung luong.";
        return result;
    }

    // Cap phat tu dau vung RAM trong
    selectedHole.startKB += request.requiredKB;
    selectedHole.freeKB -= request.requiredKB;

    result.success = true;
    result.holeId = selectedHole.id;
    result.remainingKB = selectedHole.freeKB;
    result.reason = "";

    return result;
}