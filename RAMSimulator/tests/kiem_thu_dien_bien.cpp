
#include "../include/thuat_toan_cap_phat.hpp"
#include "../include/dien_bien_cap_phat.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // TC07: Kiem tra hien thi cap phat thanh cong
    {
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 150, 50},
            {3, 250, 200}
        };

        TrangThaiBoNho truoc = boNho;
        YeuCau yeuCau{ "P1", 45 };

        KetQuaCapPhat ketQua = capPhatVuaNhat(boNho, yeuCau);

        std::ostringstream noiXuat;
        hienThiDienBienCapPhatVuaNhat(
            truoc, yeuCau, ketQua, boNho, noiXuat
        );

        std::string noiDung = noiXuat.str();

        assert(ketQua.thanhCong);
        assert(noiDung.find("Tien trinh: P1") != std::string::npos);
        assert(noiDung.find("Chon H2") != std::string::npos);
        assert(noiDung.find("[150, 195) KB") != std::string::npos);
        assert(noiDung.find("5 KB") != std::string::npos);

        // Ham trace khong duoc thay doi RAM
        assert(truoc[1].diaChiBatDauKB == 150);
        assert(truoc[1].dungLuongTrongKB == 50);
        assert(boNho[1].diaChiBatDauKB == 195);
        assert(boNho[1].dungLuongTrongKB == 5);

        std::cout << "TC07: PASS\n";
    }

    // TC08: Kiem tra hien thi phan manh ngoai
    {
        TrangThaiBoNho boNho = {
            {1, 0, 40},
            {2, 50, 2},
            {3, 70, 20}
        };

        TrangThaiBoNho truoc = boNho;
        YeuCau yeuCau{ "P2", 45 };

        KetQuaCapPhat ketQua = capPhatVuaNhat(boNho, yeuCau);

        std::ostringstream noiXuat;
        hienThiDienBienCapPhatVuaNhat(
            truoc, yeuCau, ketQua, boNho, noiXuat
        );

        std::string noiDung = noiXuat.str();

        assert(!ketQua.thanhCong);
        assert(noiDung.find("THAT BAI") != std::string::npos);
        assert(noiDung.find("phan manh ngoai")
            != std::string::npos);

        // Cap phat that bai khong thay doi RAM
        assert(boNho.size() == truoc.size());
        assert(boNho[0].dungLuongTrongKB == 40);
        assert(boNho[1].dungLuongTrongKB == 2);
        assert(boNho[2].dungLuongTrongKB == 20);

        std::cout << "TC08: PASS\n";
    }

    std::cout << "\nALL TRACE TESTS PASSED!\n";
    return 0;
}
