
#include "../include/so_sanh.hpp"
#include "../include/bo_nho.hpp"

#include <iostream>
#include <iomanip>

// Tinh cac chi so thong ke
ThongKeSoSanh tinhThongKe(
    const TrangThaiBoNho& boNho,
    const std::vector<KetQuaCapPhat>& danhSachKetQua)
{
    ThongKeSoSanh thongKe;

    for (const KetQuaCapPhat& ketQua : danhSachKetQua)
    {
        if (ketQua.thanhCong)
        {
            ++thongKe.soLanThanhCong;
        }
        else
        {
            ++thongKe.soLanThatBai;
        }
    }

    thongKe.tongDungLuongTrong = tongDungLuongTrongKB(boNho);
    thongKe.vungTrongLonNhat = dungLuongVungLonNhatKB(boNho);

    return thongKe;
}

// Hien thi bang so sanh
void inBangSoSanh(
    const ThongKeSoSanh& ketQuaThuNhat,
    const ThongKeSoSanh& ketQuaPhuHopNhat,
    const ThongKeSoSanh& ketQuaLonNhat)
{
    using std::cout;
    using std::left;
    using std::setw;

    cout << "\n========== BANG SO SANH ==========\n";

    cout << left
        << setw(15) << "Thuat toan"
        << setw(15) << "Thanh cong"
        << setw(15) << "That bai"
        << setw(20) << "Tong RAM trong"
        << setw(20) << "Vung lon nhat"
        << '\n';

    const char* tenThuatToan[] = {
        "First Fit", "Best Fit", "Worst Fit"
    };

    const ThongKeSoSanh thongKe[] = {
        ketQuaThuNhat, ketQuaPhuHopNhat, ketQuaLonNhat
    };

    for (int chiSo = 0; chiSo < 3; ++chiSo)
    {
        cout << left
            << setw(15) << tenThuatToan[chiSo]
            << setw(15) << thongKe[chiSo].soLanThanhCong
            << setw(15) << thongKe[chiSo].soLanThatBai
            << setw(20) << thongKe[chiSo].tongDungLuongTrong
            << setw(20) << thongKe[chiSo].vungTrongLonNhat
            << '\n';
    }

    cout << "==================================\n";
}
