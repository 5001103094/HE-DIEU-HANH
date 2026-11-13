
#pragma once

#include "mo_hinh.hpp"
#include <vector>

// Nhap va kiem tra du lieu RAM, tien trinh
// Tra ve true neu nhap day du va hop le
// Tra ve false neu luong nhap bi ket thuc

bool nhapDuLieu(
    TrangThaiBoNho& boNhoBanDau,
    std::vector<YeuCau>& danhSachYeuCau
);

// Hien thi du lieu da nhap
void hienThiDuLieuDaNhap(
    const TrangThaiBoNho& boNhoBanDau,
    const std::vector<YeuCau>& danhSachYeuCau
);
