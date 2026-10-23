
#pragma once

#include "models.hpp"
#include <vector>

// TV4 - Thong ke ket qua mot thuat toan
struct ComparisonStats
{
    int successCount = 0;
    int failureCount = 0;
    long long totalFree = 0;
    int largestHole = 0;
};

// TV4 - Tinh cac chi so thong ke
ComparisonStats calculateStats(
    const MemoryState& memory,
    const std::vector<AllocationResult>& results
);

// TV4 - Hien thi bang so sanh ba thuat toan
void printComparison(
    const ComparisonStats& first,
    const ComparisonStats& best,
    const ComparisonStats& worst
);
