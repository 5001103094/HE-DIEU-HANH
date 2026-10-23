
#include "../include/comparison.hpp"
#include "../include/memory.hpp"

#include <iostream>
#include <iomanip>

// TV4 - Tinh cac chi so thong ke
ComparisonStats calculateStats(
    const MemoryState& memory,
    const std::vector<AllocationResult>& results)
{
    ComparisonStats stats;

    for (const AllocationResult& result : results)
    {
        if (result.success)
        {
            ++stats.successCount;
        }
        else
        {
            ++stats.failureCount;
        }
    }

    stats.totalFree = totalFreeKB(memory);
    stats.largestHole = largestHoleKB(memory);

    return stats;
}

// TV4 - Hien thi bang so sanh
void printComparison(
    const ComparisonStats& first,
    const ComparisonStats& best,
    const ComparisonStats& worst)
{
    using std::cout;
    using std::left;
    using std::setw;

    cout << "\n========== BANG SO SANH ==========\n";

    cout << left
        << setw(15) << "Thuat toan"
        << setw(15) << "Thanh cong"
        << setw(15) << "That bai"
        << setw(20) << "Tong RAM trong"
        << setw(20) << "Vung lon nhat"
        << '\n';

    const char* names[] = {
        "First Fit", "Best Fit", "Worst Fit"
    };

    const ComparisonStats stats[] = {
        first, best, worst
    };

    for (int i = 0; i < 3; ++i)
    {
        cout << left
            << setw(15) << names[i]
            << setw(15) << stats[i].successCount
            << setw(15) << stats[i].failureCount
            << setw(20) << stats[i].totalFree
            << setw(20) << stats[i].largestHole
            << '\n';
    }

    cout << "==================================\n";
}
