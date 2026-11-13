
#include "../include/so_sanh.hpp"
#include "../include/bo_nho.hpp"

#include <cassert>
#include <iostream>
#include <vector>

// Kiem tra chuc nang thong ke
void kiemThuTinhThongKe()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 100 },
        { 2, 100, 250 },
        { 3, 350, 400 }
    };

    std::vector<KetQuaCapPhat> danhSachKetQua = {
        { "P1", true, 2, 150, "" },
        { "P2", true, 3, 200, "" },
        { "P3", false, -1, -1, "Khong du RAM" }
    };

    ThongKeSoSanh thongKe = tinhThongKe(boNho, danhSachKetQua);

    assert(thongKe.soLanThanhCong == 2);
    assert(thongKe.soLanThatBai == 1);
    assert(thongKe.tongDungLuongTrong == 750);
    assert(thongKe.vungTrongLonNhat == 400);

    std::cout << "CALCULATE STATS PASS\n";
}

// Kiem tra danh sach rong
void kiemThuKetQuaRong()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 200 }
    };

    std::vector<KetQuaCapPhat> danhSachKetQua;

    ThongKeSoSanh thongKe = tinhThongKe(boNho, danhSachKetQua);

    assert(thongKe.soLanThanhCong == 0);
    assert(thongKe.soLanThatBai == 0);
    assert(thongKe.tongDungLuongTrong == 200);
    assert(thongKe.vungTrongLonNhat == 200);

    std::cout << "EMPTY RESULTS PASS\n";
}

// Kiem tra RAM trong bang 0
void kiemThuHetBoNhoTrong()
{
    TrangThaiBoNho boNho = {
        { 1, 100, 0 },
        { 2, 400, 0 }
    };

    std::vector<KetQuaCapPhat> danhSachKetQua = {
        { "P1", true, 1, 0, "" },
        { "P2", true, 2, 0, "" }
    };

    ThongKeSoSanh thongKe = tinhThongKe(boNho, danhSachKetQua);

    assert(thongKe.soLanThanhCong == 2);
    assert(thongKe.soLanThatBai == 0);
    assert(thongKe.tongDungLuongTrong == 0);
    assert(thongKe.vungTrongLonNhat == 0);

    std::cout << "NO FREE MEMORY PASS\n";
}

int main()
{
    kiemThuTinhThongKe();
    kiemThuKetQuaRong();
    kiemThuHetBoNhoTrong();

    std::cout << "\n=== BANG SO SANH MAU ===\n";

    ThongKeSoSanh ketQuaThuNhat{ 5, 0, 777, 200 };
    ThongKeSoSanh ketQuaPhuHopNhat{ 5, 0, 777, 350 };
    ThongKeSoSanh ketQuaLonNhat{ 4, 1, 1152, 300 };

    inBangSoSanh(ketQuaThuNhat, ketQuaPhuHopNhat, ketQuaLonNhat);

    std::cout << "ALL COMPARISON TESTS PASSED\n";
    return 0;
}
