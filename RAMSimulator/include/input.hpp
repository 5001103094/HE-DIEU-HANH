
#pragma once

#include "models.hpp"
#include <vector>

// TV5 - CV02: Nhap va kiem tra du lieu RAM, tien trinh
// Tra ve true neu nhap day du va hop le
// Tra ve false neu luong nhap bi ket thuc

bool inputData(
    MemoryState& initialMemory,
    std::vector<Request>& requests
);

// TV5 - CV02: Hien thi du lieu da nhap
void displayInputData(
    const MemoryState& initialMemory,
    const std::vector<Request>& requests
);
