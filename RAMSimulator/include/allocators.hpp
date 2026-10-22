#pragma once

#include "models.hpp"

// First Fit - TV2
AllocationResult firstFit(
    MemoryState& memory,
    const Request& request
);

// Best Fit - TV3
AllocationResult bestFit(
    MemoryState& memory,
    const Request& request
);

// Worst Fit - TV4
AllocationResult worstFit(
    MemoryState& memory,
    const Request& request
);