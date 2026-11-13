#pragma once

#include "mo_hinh.hpp"
#include <cstddef>

// Tinh tong dung luong RAM trong
long long tongDungLuongTrongKB(const TrangThaiBoNho& boNho);

// Tim vung RAM trong lon nhat
int dungLuongVungLonNhatKB(const TrangThaiBoNho& boNho);

// Sao chep trang thai RAM
TrangThaiBoNho saoChepBoNho(const TrangThaiBoNho& boNho);

// Xac dinh nguyen nhan cap phat that bai
std::string lyDoCapPhatThatBai(
    const TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
);

// Cap phat RAM tu dau vung trong duoc chon
KetQuaCapPhat capPhatTuVungTrong(
    TrangThaiBoNho& boNho,
    std::size_t viTriVung,
    const YeuCau& yeuCau
);

// VONG_DOI_BO_NHO_V1
// Luu lai vung nho dang thuoc ve mot tien trinh.
struct VungDaCapPhat {
    std::string maTienTrinh;
    int maVung = -1;
    int diaChiBatDauKB = 0;
    int dungLuongKB = 0;
};

using DanhSachDaCapPhat = std::vector<VungDaCapPhat>;

// Cap phat va ghi nhan de co the giai phong ve sau.
KetQuaCapPhat capPhatCoTheoDoi(
    TrangThaiBoNho& boNho,
    DanhSachDaCapPhat& daCapPhat,
    std::size_t viTriVung,
    const YeuCau& yeuCau
);

// Giai phong tien trinh, gop cac vung trong lien ke.
bool giaiPhongTienTrinh(
    TrangThaiBoNho& boNho,
    DanhSachDaCapPhat& daCapPhat,
    const std::string& maTienTrinh,
    std::string& loi
);
