#pragma once

#include <string>
#include <vector>

// Thong tin mot vung RAM trong
struct Hole {
    int id = 0;
    int startKB = 0;
    int freeKB = 0;
};

// Thong tin tien trinh yeu cau cap phat RAM
struct Request {
    std::string pid;        // Ma tien trinh: P1, P2, P3...
    int requiredKB = 0;     // Dung luong RAM can cap phat
};

// Ket qua cap phat bo nho cho mot tien trinh
struct AllocationResult {
    std::string pid;        // Ma tien trinh
    bool success = false;   // true: thanh cong, false: that bai
    int holeId = -1;        // Ma vung duoc chon, -1 neu that bai
    int remainingKB = -1;   // Dung luong con lai tai vung duoc chon
    std::string reason;     // Nguyen nhan that bai (neu co)
};

// Danh sach cac vung RAM trong
using MemoryState = std::vector<Hole>;