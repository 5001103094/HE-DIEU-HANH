
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "include/bo_nho.hpp"
#include "include/nhap_du_lieu.hpp"
#include "include/so_sanh.hpp"
#include "include/thuat_toan_cap_phat.hpp"

// Hien thi cac chuc nang cua chuong trinh
void hienThiMenu()
{
    std::cout << "\n========================================\n";
    std::cout << "       MO PHONG CAP PHAT RAM\n";
    std::cout << "========================================\n";
    std::cout << "1. Nhap du lieu RAM va tien trinh\n";
    std::cout << "2. Chay thuat toan First Fit\n";
    std::cout << "3. Chay thuat toan Best Fit\n";
    std::cout << "4. Chay thuat toan Worst Fit\n";
    std::cout << "5. Chay ca ba thuat toan\n";
    std::cout << "6. So sanh ket qua cap phat\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "========================================\n";
    std::cout << "Nhap lua chon: ";
}

using HamCapPhat =
    KetQuaCapPhat (*)(TrangThaiBoNho&, const YeuCau&);

// Chay mot thuat toan tren ban sao RAM
void chayThuatToan(
    const std::string& tenThuatToan,
    const TrangThaiBoNho& boNhoBanDau,
    const std::vector<YeuCau>& danhSachYeuCau,
    HamCapPhat hamCapPhat)
{
    if (boNhoBanDau.empty() || danhSachYeuCau.empty())
    {
        std::cout << "\nChua co du lieu RAM hoac tien trinh.\n";
        std::cout << "Vui long chon 1 de nhap du lieu.\n";
        return;
    }

    // Moi thuat toan su dung RAM ban dau doc lap
    TrangThaiBoNho boNho = saoChepBoNho(boNhoBanDau);

    int soLanThanhCong = 0;
    int soLanThatBai = 0;

    std::cout << "\n=== " << tenThuatToan << " ===\n";

    for (const YeuCau& yeuCau : danhSachYeuCau)
    {
        KetQuaCapPhat ketQua = hamCapPhat(boNho, yeuCau);

        std::cout << "\nTien trinh: " << ketQua.maTienTrinh
                  << " - Yeu cau: " << yeuCau.dungLuongYeuCauKB
                  << " KB\n";

        if (ketQua.thanhCong)
        {
            ++soLanThanhCong;

            std::cout << "Cap phat thanh cong tai H"
                      << ketQua.maVung << "\n";
            std::cout << "Dung luong con lai tai vung: "
                      << ketQua.dungLuongConLaiKB << " KB\n";
        }
        else
        {
            ++soLanThatBai;

            std::cout << "Cap phat that bai.\n";
            std::cout << "Nguyen nhan: "
                      << ketQua.lyDo << "\n";
        }
    }

    std::cout << "\n=== THONG KE " << tenThuatToan
              << " ===\n";

    std::cout << "Thanh cong: " << soLanThanhCong << "\n";
    std::cout << "That bai: " << soLanThatBai << "\n";
    std::cout << "Tong RAM trong: "
              << tongDungLuongTrongKB(boNho) << " KB\n";
    std::cout << "Vung trong lon nhat: "
              << dungLuongVungLonNhatKB(boNho) << " KB\n";
}

// Chay thuat toan tren ban sao RAM va thong ke ket qua bang ham dung chung.
ThongKeSoSanh tinhTongKet(
    const TrangThaiBoNho& boNhoBanDau,
    const std::vector<YeuCau>& danhSachYeuCau,
    HamCapPhat hamCapPhat)
{
    TrangThaiBoNho boNho = saoChepBoNho(boNhoBanDau);
    std::vector<KetQuaCapPhat> danhSachKetQua;
    danhSachKetQua.reserve(danhSachYeuCau.size());

    for (const YeuCau& yeuCau : danhSachYeuCau)
    {
        danhSachKetQua.push_back(hamCapPhat(boNho, yeuCau));
    }

    return tinhThongKe(boNho, danhSachKetQua);
}

// So sanh ba thuat toan
void soSanhThuatToan(
    const TrangThaiBoNho& boNhoBanDau,
    const std::vector<YeuCau>& danhSachYeuCau)
{
    if (boNhoBanDau.empty() || danhSachYeuCau.empty())
    {
        std::cout << "\nChua co du lieu.\n";
        std::cout << "Vui long chon 1 de nhap du lieu.\n";
        return;
    }

    ThongKeSoSanh ketQuaDauTien =
        tinhTongKet(boNhoBanDau, danhSachYeuCau, capPhatDauTien);

    ThongKeSoSanh ketQuaVuaNhat =
        tinhTongKet(boNhoBanDau, danhSachYeuCau, capPhatVuaNhat);

    ThongKeSoSanh ketQuaLonNhat =
        tinhTongKet(boNhoBanDau, danhSachYeuCau, capPhatLonNhat);

    std::cout << "\n=== BANG SO SANH THUAT TOAN ===\n";

    std::cout << std::left
              << std::setw(15) << "Thuat toan"
              << std::setw(12) << "Thanh cong"
              << std::setw(12) << "That bai"
              << std::setw(16) << "Tong RAM trong"
              << "Vung lon nhat\n";

    auto inDong = [](const std::string& ten,
                       const ThongKeSoSanh& ketQua)
    {
        std::cout << std::left
                  << std::setw(15) << ten
                  << std::setw(12) << ketQua.soLanThanhCong
                  << std::setw(12) << ketQua.soLanThatBai
                  << std::setw(16) << ketQua.tongDungLuongTrong
                  << ketQua.vungTrongLonNhat << "\n";
    };

    inDong("First Fit", ketQuaDauTien);
    inDong("Best Fit", ketQuaVuaNhat);
    inDong("Worst Fit", ketQuaLonNhat);

    std::cout << "\nDon vi dung luong: KB\n";
}

// Xu ly lua chon cua nguoi dung
void xuLyLuaChon(
    const std::string& luaChon,
    TrangThaiBoNho& boNhoBanDau,
    std::vector<YeuCau>& danhSachYeuCau)
{
    if (luaChon == "1")
    {
        std::cout << "\n[Nhap du lieu RAM va tien trinh]\n";

        if (nhapDuLieu(boNhoBanDau, danhSachYeuCau))
        {
            std::cout << "\nNhap du lieu thanh cong!\n";
            hienThiDuLieuDaNhap(boNhoBanDau, danhSachYeuCau);
        }
        else
        {
            std::cout << "\nQua trinh nhap bi ket thuc.\n";
        }
    }
    else if (luaChon == "2")
    {
        chayThuatToan(
            "FIRST FIT",
            boNhoBanDau,
            danhSachYeuCau,
            capPhatDauTien
        );
    }
    else if (luaChon == "3")
    {
        chayThuatToan(
            "BEST FIT",
            boNhoBanDau,
            danhSachYeuCau,
            capPhatVuaNhat
        );
    }
    else if (luaChon == "4")
    {
        chayThuatToan(
            "WORST FIT",
            boNhoBanDau,
            danhSachYeuCau,
            capPhatLonNhat
        );
    }
    else if (luaChon == "5")
    {
        if (boNhoBanDau.empty() || danhSachYeuCau.empty())
        {
            std::cout << "\nChua co du lieu. "
                    << "Vui long chon 1 de nhap du lieu.\n";
        }
        else
        {
            chayThuatToan(
                "FIRST FIT",
                boNhoBanDau,
                danhSachYeuCau,
                capPhatDauTien
            );

            chayThuatToan(
                "BEST FIT",
                boNhoBanDau,
                danhSachYeuCau,
                capPhatVuaNhat
            );

            chayThuatToan(
                "WORST FIT",
                boNhoBanDau,
                danhSachYeuCau,
                capPhatLonNhat
            );
        }
    }
    else if (luaChon == "6")
    {
        soSanhThuatToan(boNhoBanDau, danhSachYeuCau);
    }
    else
    {
        std::cout << "\nLua chon khong hop le!\n";
        std::cout << "Vui long nhap so tu 0 den 6.\n";
    }
}

// Dieu khien luong chay chuong trinh
int main()
{
    std::string luaChon;

    TrangThaiBoNho boNhoBanDau;
    std::vector<YeuCau> danhSachYeuCau;

    while (true)
    {
        hienThiMenu();

        if (!std::getline(std::cin, luaChon))
        {
            break;
        }

        if (luaChon == "0")
        {
            std::cout << "\nKet thuc chuong trinh.\n";
            break;
        }

        xuLyLuaChon(luaChon, boNhoBanDau, danhSachYeuCau);

        std::cout << "\nNhan Enter de quay lai menu...";

        if (!std::getline(std::cin, luaChon))
        {
            break;
        }
    }

    return 0;
}
