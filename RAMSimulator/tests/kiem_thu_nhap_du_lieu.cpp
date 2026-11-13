#include "../include/nhap_du_lieu.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Doi luong nhap/xuat tam thoi de kiem thu ham nhapDuLieu() khong can go tay.
bool thuNhapDuLieu(
    const std::string& duLieuNhap,
    TrangThaiBoNho& boNho,
    std::vector<YeuCau>& danhSachYeuCau,
    std::string& thongBao)
{
    std::istringstream luongNhap(duLieuNhap);
    std::ostringstream luongXuat;
    std::streambuf* luongNhapCu = std::cin.rdbuf(luongNhap.rdbuf());
    std::streambuf* luongXuatCu = std::cout.rdbuf(luongXuat.rdbuf());
    std::cin.clear();

    bool thanhCong = nhapDuLieu(boNho, danhSachYeuCau);

    std::cin.rdbuf(luongNhapCu);
    std::cout.rdbuf(luongXuatCu);
    std::cin.clear();
    thongBao = luongXuat.str();
    return thanhCong;
}

int main()
{
    // Kiem tra nhap hop le: sap xep vung theo dia chi va giu nguyen ma H.
    {
        TrangThaiBoNho boNho;
        std::vector<YeuCau> danhSachYeuCau;
        std::string thongBao;
        bool thanhCong = thuNhapDuLieu(
            "2\n100\n40\n0\n50\n2\nP1\n30\nP2\n60\n",
            boNho, danhSachYeuCau, thongBao);
        assert(thanhCong);
        assert(boNho.size() == 2);
        assert(boNho[0].ma == 2 && boNho[0].diaChiBatDauKB == 0);
        assert(boNho[1].ma == 1 && boNho[1].diaChiBatDauKB == 100);
        assert(danhSachYeuCau.size() == 2);
        assert(danhSachYeuCau[0].maTienTrinh == "P1");
        assert(danhSachYeuCau[1].dungLuongYeuCauKB == 60);
    }
    std::cout << "NHAP HOP LE: PASS\n";

    // Kiem tra trung ma tien trinh, vung chong lan va so nguyen khong hop le.
    {
        TrangThaiBoNho boNho;
        std::vector<YeuCau> danhSachYeuCau;
        std::string thongBao;
        bool thanhCong = thuNhapDuLieu(
            "0\n2\n0\n50\n30\n20\n60\n20\n2\nP1\n5\nP1\nP2\n10\n",
            boNho, danhSachYeuCau, thongBao);
        assert(thanhCong);
        assert(boNho.size() == 2 && boNho[1].diaChiBatDauKB == 60);
        assert(danhSachYeuCau[1].maTienTrinh == "P2");
        assert(thongBao.find("chong lan") != std::string::npos);
        assert(thongBao.find("da ton tai") != std::string::npos);
        assert(thongBao.find("khong hop le") != std::string::npos);
    }
    std::cout << "NHAP SAI VA NHAP LAI: PASS\n";

    // Neu du lieu dang nhap bi ngat, phai giu nguyen trang thai cu.
    {
        TrangThaiBoNho boNho = {{9, 500, 100}};
        std::vector<YeuCau> danhSachYeuCau = {{"P9", 20}};
        std::string thongBao;
        bool thanhCong = thuNhapDuLieu("2\n0\n40\n", boNho, danhSachYeuCau, thongBao);
        assert(!thanhCong);
        assert(boNho.size() == 1 && boNho[0].ma == 9);
        assert(danhSachYeuCau.size() == 1 && danhSachYeuCau[0].maTienTrinh == "P9");
    }
    std::cout << "NHAP BI NGAT: PASS\n";
    return 0;
}
