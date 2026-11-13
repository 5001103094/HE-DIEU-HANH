
#include "../include/thuat_toan_cap_phat.hpp"
#include "../include/bo_nho.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

void kiemThuTC01()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 300 },
        { 2, 300, 600 },
        { 3, 900, 350 },
        { 4, 1250, 200 },
        { 5, 1450, 750 },
        { 6, 2200, 125 }
    };

    std::vector<YeuCau> danhSachYeuCau = {
        { "P1", 115 },{ "P2", 500 },{ "P3", 358 },
        { "P4", 200 },{ "P5", 375 }
    };

    int thanhCong = 0;
    for (const YeuCau& yeuCau : danhSachYeuCau)
    {
        KetQuaCapPhat ketQua = capPhatLonNhat(boNho, yeuCau);
        if (ketQua.thanhCong) ++thanhCong;
    }

    assert(thanhCong == 4);
    assert(tongDungLuongTrongKB(boNho) == 1152);
    assert(dungLuongVungLonNhatKB(boNho) == 300);
    std::cout << "TC01 PASS\n";
}

void kiemThuTC02()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 100 },{ 2, 100, 250 },{ 3, 350, 400 }
    };

    KetQuaCapPhat ketQua = capPhatLonNhat(boNho, { "P1", 250 });

    assert(ketQua.thanhCong);
    assert(ketQua.maVung == 3);
    assert(ketQua.dungLuongConLaiKB == 150);
    assert(boNho[2].diaChiBatDauKB == 600);
    std::cout << "TC02 PASS\n";
}

void kiemThuTC03()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 50 },{ 2, 50, 70 }
    };

    KetQuaCapPhat ketQua = capPhatLonNhat(boNho, { "P1", 150 });

    assert(!ketQua.thanhCong);
    assert(ketQua.lyDo ==
        "Khong du tong dung luong RAM trong.");
    assert(tongDungLuongTrongKB(boNho) == 120);
    std::cout << "TC03 PASS\n";
}

void kiemThuTC04()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 60 },{ 2, 60, 90 },{ 3, 150, 40 }
    };

    KetQuaCapPhat ketQua = capPhatLonNhat(boNho, { "P1", 120 });

    assert(!ketQua.thanhCong);
    assert(ketQua.lyDo ==
        "Phan manh ngoai: khong co vung RAM lien tuc du lon.");
    assert(tongDungLuongTrongKB(boNho) == 190);
    std::cout << "TC04 PASS\n";
}

void kiemThuTC05()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 200 },{ 2, 200, 200 },{ 3, 400, 400 }
    };

    KetQuaCapPhat ketQua = capPhatLonNhat(boNho, { "P1", 150 });

    assert(ketQua.thanhCong);
    assert(ketQua.maVung == 3);
    assert(ketQua.dungLuongConLaiKB == 250);
    std::cout << "TC05 PASS\n";
}

void kiemThuTC06()
{
    TrangThaiBoNho boNho = {
        { 1, 0, 100 },{ 2, 100, 400 },{ 3, 500, 220 }
    };

    KetQuaCapPhat yeuCau1 = capPhatLonNhat(boNho, { "P1", 200 });
    KetQuaCapPhat ketQua2 = capPhatLonNhat(boNho, { "P2", 210 });

    assert(yeuCau1.thanhCong && yeuCau1.maVung == 2);
    assert(ketQua2.thanhCong && ketQua2.maVung == 3);
    assert(tongDungLuongTrongKB(boNho) == 310);
    std::cout << "TC06 PASS\n";
}

void kiemThuYeuCauKhongHopLe()
{
    TrangThaiBoNho boNho = { { 1, 0, 200 } };

    KetQuaCapPhat ketQua1 = capPhatLonNhat(boNho, { "P1", 0 });
    KetQuaCapPhat ketQua2 = capPhatLonNhat(boNho, { "P2", -10 });
    KetQuaCapPhat ketQua3 = capPhatLonNhat(boNho, { "", 50 });

    assert(!ketQua1.thanhCong);
    assert(!ketQua2.thanhCong);
    assert(!ketQua3.thanhCong);
    assert(boNho[0].dungLuongTrongKB == 200);
    std::cout << "INVALID PASS\n";
}

void kiemThuCungDungLuong()
{
    TrangThaiBoNho boNho = {
        { 1, 500, 300 },
        { 2, 100, 300 },
        { 3, 900, 100 }
    };

    KetQuaCapPhat ketQua = capPhatLonNhat(boNho, { "P1", 150 });

    // Khi kich thuoc bang nhau, chon startKB nho nhat.
    assert(ketQua.thanhCong);
    assert(ketQua.maVung == 2);
    std::cout << "TIE BREAK PASS\n";
}

void kiemThuBoNhoDocLap()
{
    TrangThaiBoNho banDau = {
        { 1, 0, 300 },{ 2, 300, 500 }
    };

    TrangThaiBoNho banSao = saoChepBoNho(banDau);
    capPhatLonNhat(banSao, { "P1", 250 });

    assert(banDau[0].dungLuongTrongKB == 300);
    assert(banDau[1].dungLuongTrongKB == 500);
    std::cout << "INDEPENDENT MEMORY PASS\n";
}

int main()
{
    kiemThuTC01();
    kiemThuTC02();
    kiemThuTC03();
    kiemThuTC04();
    kiemThuTC05();
    kiemThuTC06();
    kiemThuYeuCauKhongHopLe();
    kiemThuCungDungLuong();
    kiemThuBoNhoDocLap();

    std::cout << "ALL WORST FIT TESTS PASSED\n";
    return 0;
}
