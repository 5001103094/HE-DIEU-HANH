#pragma once

#include <string>
#include <vector>

// Thong tin mot vung RAM trong
struct VungTrong {
    int ma = 0;
    int diaChiBatDauKB = 0;
    int dungLuongTrongKB = 0;
};

// Thong tin tien trinh yeu cau cap phat RAM
struct YeuCau {
    std::string maTienTrinh;        // Ma tien trinh: P1, P2, P3...
    int dungLuongYeuCauKB = 0;     // Dung luong RAM can cap phat
};

// Ket qua cap phat bo nho cho mot tien trinh
struct KetQuaCapPhat {
    std::string maTienTrinh;        // Ma tien trinh
    bool thanhCong = false;   // true: thanh cong, false: that bai
    int maVung = -1;        // Ma vung duoc chon, -1 neu that bai
    int dungLuongConLaiKB = -1;   // Dung luong con lai tai vung duoc chon
    std::string lyDo;     // Nguyen nhan that bai (neu co)
};

// Danh sach cac vung RAM trong
using TrangThaiBoNho = std::vector<VungTrong>;