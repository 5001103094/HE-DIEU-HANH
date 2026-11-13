#include <iostream>
#include <cassert>
#include "../include/bo_nho.hpp"

int main()
{
    // Tao ba vung RAM trong
    TrangThaiBoNho banDau = {
        {1, 0, 100},
        {2, 200, 250},
        {3, 500, 400}
    };

    // Test 1: Tinh tong RAM trong
    assert(tongDungLuongTrongKB(banDau) == 750);
    std::cout << "TEST 1: PASS\n";

    // Test 2: Tim vung RAM trong lon nhat
    assert(dungLuongVungLonNhatKB(banDau) == 400);
    std::cout << "TEST 2: PASS\n";

    // Test 3: Sao chep trang thai RAM
    TrangThaiBoNho boNho = saoChepBoNho(banDau);

    YeuCau yeuCau1 = { "P1", 150 };

    KetQuaCapPhat ketQua =
        capPhatTuVungTrong(boNho, 1, yeuCau1);

    assert(ketQua.thanhCong == true);
    assert(ketQua.maVung == 2);
    assert(ketQua.dungLuongConLaiKB == 100);

    std::cout << "TEST 3: PASS\n";

    // Test 4: Cap nhat dia chi va dung luong
    assert(boNho[1].diaChiBatDauKB == 350);
    assert(boNho[1].dungLuongTrongKB == 100);

    std::cout << "TEST 4: PASS\n";

    // Test 5: RAM goc khong bi thay doi
    assert(banDau[1].diaChiBatDauKB == 200);
    assert(banDau[1].dungLuongTrongKB == 250);

    std::cout << "TEST 5: PASS\n";

    // Test 6: Phat hien phan manh ngoai
    TrangThaiBoNho boNhoBiPhanManh = {
        {1, 0, 60},
        {2, 80, 90},
        {3, 190, 40}
    };

    YeuCau yeuCau2 = { "P2", 120 };

    assert(lyDoCapPhatThatBai(boNhoBiPhanManh, yeuCau2) ==
        "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

    std::cout << "TEST 6: PASS\n";

    // Test 7: Cap phat that bai khong lam thay doi RAM
    YeuCau yeuCau3 = { "P3", 500 };

    KetQuaCapPhat ketQuaThatBai =
        capPhatTuVungTrong(boNho, 1, yeuCau3);

    assert(ketQuaThatBai.thanhCong == false);
    assert(boNho[1].diaChiBatDauKB == 350);
    assert(boNho[1].dungLuongTrongKB == 100);

    std::cout << "TEST 7: PASS\n";

    // Test 8: Tong RAM khong du
    TrangThaiBoNho boNhoKhongDu = { {1, 0, 50}, {2, 100, 70} };
    YeuCau yeuCau4 = { "P4", 150 };

    assert(lyDoCapPhatThatBai(boNhoKhongDu, yeuCau4) ==
        "Khong du tong dung luong RAM trong.");

    std::cout << "TEST 8: PASS\n";

    // Test 9: Dung luong cap phat bang 0
    int diaChiBanDau = boNho[0].diaChiBatDauKB;
    int dungLuongBanDau = boNho[0].dungLuongTrongKB;

    KetQuaCapPhat ketQuaDungLuongBangKhong =
        capPhatTuVungTrong(boNho, 0, { "P0", 0 });

    assert(!ketQuaDungLuongBangKhong.thanhCong);
    assert(boNho[0].diaChiBatDauKB == diaChiBanDau);
    assert(boNho[0].dungLuongTrongKB == dungLuongBanDau);

    std::cout << "TEST 9: PASS\n";

    // Test 10: Dung luong am va ma tien trinh rong
    assert(!capPhatTuVungTrong(boNho, 0, { "P5", -10 }).thanhCong);
    assert(!capPhatTuVungTrong(boNho, 0, { "", 10 }).thanhCong);

    std::cout << "TEST 10: PASS\n";

    // Test 11: Chi so vung RAM khong ton tai
    KetQuaCapPhat ketQuaVungKhongTonTai =
        capPhatTuVungTrong(boNho, boNho.size(), { "P6", 20 });

    assert(!ketQuaVungKhongTonTai.thanhCong);
    assert(ketQuaVungKhongTonTai.lyDo == "Vung RAM khong ton tai.");

    std::cout << "TEST 11: PASS\n";

    // Test 12: Vung RAM duoc chon khong du
    KetQuaCapPhat ketQuaVungKhongDu =
        capPhatTuVungTrong(boNho, 0, { "P7", 200 });

    assert(!ketQuaVungKhongDu.thanhCong);
    assert(ketQuaVungKhongDu.lyDo == "Vung RAM khong du dung luong.");
    assert(boNho[0].diaChiBatDauKB == diaChiBanDau);
    assert(boNho[0].dungLuongTrongKB == dungLuongBanDau);

    std::cout << "TEST 12: PASS\n";

    std::cout << "\nHOAN THANH KIEM THU BO NHO!\n";

    return 0;
}