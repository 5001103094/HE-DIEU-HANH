
#pragma once

#include "mo_hinh.hpp"
#include <vector>

// Thong ke ket qua mot thuat toan
struct ThongKeSoSanh
{
    int soLanThanhCong = 0;
    int soLanThatBai = 0;
    long long tongDungLuongTrong = 0;
    int vungTrongLonNhat = 0;
};

// Tinh cac chi so thong ke
ThongKeSoSanh tinhThongKe(
    const TrangThaiBoNho& boNho,
    const std::vector<KetQuaCapPhat>& danhSachKetQua
);

// Hien thi bang so sanh ba thuat toan
void inBangSoSanh(
    const ThongKeSoSanh& ketQuaThuNhat,
    const ThongKeSoSanh& ketQuaPhuHopNhat,
    const ThongKeSoSanh& ketQuaLonNhat
);
