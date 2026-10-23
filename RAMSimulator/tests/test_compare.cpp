
#include "../include/comparison.hpp"
#include "../include/memory.hpp"

#include <cassert>
#include <iostream>
#include <vector>

// TV4 - Kiem tra chuc nang thong ke
void testCalculateStats()
{
    MemoryState memory = {
        { 1, 0, 100 },
        { 2, 100, 250 },
        { 3, 350, 400 }
    };

    std::vector<AllocationResult> results = {
        { "P1", true, 2, 150, "" },
        { "P2", true, 3, 200, "" },
        { "P3", false, -1, -1, "Khong du RAM" }
    };

    ComparisonStats stats = calculateStats(memory, results);

    assert(stats.successCount == 2);
    assert(stats.failureCount == 1);
    assert(stats.totalFree == 750);
    assert(stats.largestHole == 400);

    std::cout << "CALCULATE STATS PASS\n";
}

// TV4 - Kiem tra danh sach rong
void testEmptyResults()
{
    MemoryState memory = {
        { 1, 0, 200 }
    };

    std::vector<AllocationResult> results;

    ComparisonStats stats = calculateStats(memory, results);

    assert(stats.successCount == 0);
    assert(stats.failureCount == 0);
    assert(stats.totalFree == 200);
    assert(stats.largestHole == 200);

    std::cout << "EMPTY RESULTS PASS\n";
}

// TV4 - Kiem tra RAM trong bang 0
void testNoFreeMemory()
{
    MemoryState memory = {
        { 1, 100, 0 },
        { 2, 400, 0 }
    };

    std::vector<AllocationResult> results = {
        { "P1", true, 1, 0, "" },
        { "P2", true, 2, 0, "" }
    };

    ComparisonStats stats = calculateStats(memory, results);

    assert(stats.successCount == 2);
    assert(stats.failureCount == 0);
    assert(stats.totalFree == 0);
    assert(stats.largestHole == 0);

    std::cout << "NO FREE MEMORY PASS\n";
}

int main()
{
    testCalculateStats();
    testEmptyResults();
    testNoFreeMemory();

    std::cout << "\n=== BANG SO SANH MAU ===\n";

    ComparisonStats first{ 5, 0, 777, 200 };
    ComparisonStats best{ 5, 0, 777, 350 };
    ComparisonStats worst{ 4, 1, 1152, 300 };

    printComparison(first, best, worst);

    std::cout << "ALL COMPARISON TESTS PASSED\n";
    return 0;
}
