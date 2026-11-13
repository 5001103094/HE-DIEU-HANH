
#include "../include/nhap_du_lieu.hpp"

#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

namespace {

// Nhap so nguyen va kiem tra du lieu
bool nhapSoNguyen(
    const std::string& loiNhac,
    int giaTriNhoNhat,
    int& ketQua)
{
    std::string dongNhap;

    while (true)
    {
        std::cout << loiNhac;

        if (!std::getline(std::cin, dongNhap))
            return false;

        std::istringstream luongDoc(dongNhap);
        long long soNhap = 0;
        std::string duLieuThua;

        if (!(luongDoc >> soNhap) ||
            (luongDoc >> duLieuThua) ||
            soNhap < giaTriNhoNhat ||
            soNhap > std::numeric_limits<int>::max())
        {
            std::cout << "Du lieu khong hop le. "
                      << "Vui long nhap so nguyen "
                      << (giaTriNhoNhat == 0 ? "khong am" : "duong")
                      << ".\n";
            continue;
        }

        ketQua = static_cast<int>(soNhap);
        return true;
    }
}

// Nhap ma tien trinh va kiem tra trung lap

bool nhapMaTienTrinh(
    const std::set<std::string>& maDaDung,
    std::string& ketQua)
{
    static const std::regex mauMa(R"(^P[1-9][0-9]*$)");

    std::string dongNhap;

    while (true)
    {
        std::cout << "Ma tien trinh (vi du P1): ";

        if (!std::getline(std::cin, dongNhap))
            return false;

        // Kiem tra dinh dang P1, P2, P3,...
        if (!std::regex_match(dongNhap, mauMa))
        {
            std::cout
                << "Ma tien trinh khong hop le. "
                << "Vui long nhap dung dinh dang P1, P2, P3,...\n";
        }
        // Kiem tra trung ma tien trinh
        else if (maDaDung.count(dongNhap) != 0)
        {
            std::cout
                << "Ma tien trinh da ton tai. "
                << "Hay nhap ma khac.\n";
        }
        else
        {
            ketQua = dongNhap;
            return true;
        }
    }
}

// Kiem tra cac vung RAM co chong lan khong
bool biChongLan(
    const TrangThaiBoNho& boNho,
    int diaChiBatDau,
    int dungLuongMoiKB)
{
    const long long diaChiKetThucMoi =
        static_cast<long long>(diaChiBatDau) + dungLuongMoiKB;

    for (const VungTrong& vungTrong : boNho)
    {
        const long long diaChiKetThucVung =
            static_cast<long long>(vungTrong.diaChiBatDauKB)
            + vungTrong.dungLuongTrongKB;

        if (diaChiBatDau < diaChiKetThucVung &&
            vungTrong.diaChiBatDauKB < diaChiKetThucMoi)
        {
            return true;
        }
    }

    return false;
}

} // namespace

// Nhap du lieu RAM va tien trinh
bool nhapDuLieu(
    TrangThaiBoNho& boNhoBanDau,
    std::vector<YeuCau>& danhSachYeuCau)
{
    TrangThaiBoNho boNhoMoi;
    std::vector<YeuCau> danhSachYeuCauMoi;

    int soVungTrong = 0;

    if (!nhapSoNguyen(
        "So vung RAM trong: ", 1, soVungTrong))
    {
        return false;
    }

    // Nhap danh sach vung RAM
    for (int chiSo = 1; chiSo <= soVungTrong; ++chiSo)
    {
        std::cout << "\nNhap vung H" << chiSo << ":\n";

        while (true)
        {
            int diaChiBatDauKB = 0;
            int dungLuongTrongKB = 0;

            if (!nhapSoNguyen(
                "Dia chi bat dau (KB): ", 0, diaChiBatDauKB))
            {
                return false;
            }

            if (!nhapSoNguyen(
                "Dung luong trong (KB): ", 1, dungLuongTrongKB))
            {
                return false;
            }

            if (dungLuongTrongKB >
                std::numeric_limits<int>::max() - diaChiBatDauKB)
            {
                std::cout << "Dia chi ket thuc "
                          << "vuot gioi han. Nhap lai.\n";
                continue;
            }

            if (biChongLan(
                boNhoMoi, diaChiBatDauKB, dungLuongTrongKB))
            {
                std::cout << "Vung RAM bi chong lan. "
                          << "Nhap lai.\n";
                continue;
            }

            boNhoMoi.push_back(
                VungTrong{chiSo, diaChiBatDauKB, dungLuongTrongKB});

            break;
        }
    }

    // Nhap so tien trinh
    int soTienTrinh = 0;

    if (!nhapSoNguyen(
        "\nSo tien trinh: ", 1, soTienTrinh))
    {
        return false;
    }

    std::set<std::string> maDaDung;

    // Nhap danh sach tien trinh
    for (int chiSo = 1; chiSo <= soTienTrinh; ++chiSo)
    {
        std::cout << "\nNhap tien trinh thu "
                  << chiSo << ":\n";

        std::string maTienTrinh;
        int dungLuongYeuCauKB = 0;

        if (!nhapMaTienTrinh(maDaDung, maTienTrinh))
            return false;

        if (!nhapSoNguyen(
            "Dung luong yeu cau (KB): ",
            1, dungLuongYeuCauKB))
        {
            return false;
        }

        maDaDung.insert(maTienTrinh);

        danhSachYeuCauMoi.push_back(
            YeuCau{maTienTrinh, dungLuongYeuCauKB});
    }

    // Sap xep RAM theo dia chi bat dau tang dan
    // Giu nguyen ID cua tung vung RAM
    std::sort(
        boNhoMoi.begin(),
        boNhoMoi.end(),
        [](const VungTrong& vungA, const VungTrong& vungB)
        {
            return vungA.diaChiBatDauKB < vungB.diaChiBatDauKB;
        }
    );

    // Chi cap nhat du lieu khi nhap thanh cong
    boNhoBanDau = boNhoMoi;
    danhSachYeuCau = danhSachYeuCauMoi;

    return true;
}

// Hien thi du lieu da nhap
void hienThiDuLieuDaNhap(
    const TrangThaiBoNho& boNhoBanDau,
    const std::vector<YeuCau>& danhSachYeuCau)
{
    std::cout << "\n=== CAC VUNG RAM TRONG ===\n";

    for (const VungTrong& vungTrong : boNhoBanDau)
    {
        std::cout << "H" << vungTrong.ma
                  << ": bat dau " << vungTrong.diaChiBatDauKB
                  << " KB, trong " << vungTrong.dungLuongTrongKB
                  << " KB\n";
    }

    std::cout << "\n=== CAC TIEN TRINH ===\n";

    for (const YeuCau& yeuCau : danhSachYeuCau)
    {
        std::cout << yeuCau.maTienTrinh
                  << ": can " << yeuCau.dungLuongYeuCauKB
                  << " KB\n";
    }
}
