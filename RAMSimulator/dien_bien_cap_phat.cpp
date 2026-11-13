
#include "include/dien_bien_cap_phat.hpp"
#include "include/bo_nho.hpp"
#include <ostream>
#include <cstddef>

// Hien thi qua trinh cap phat Best Fit
// Chi hien thi ket qua, khong thay doi trang thai RAM.
void hienThiDienBienCapPhatVuaNhat(
    const TrangThaiBoNho& boNhoTruoc,
    const YeuCau& yeuCau,
    const KetQuaCapPhat& ketQua,
    const TrangThaiBoNho& boNhoSau,
    std::ostream& noiXuat
) {
    noiXuat << "\n========== BEST FIT TRACE ==========\n";
    noiXuat << "Tien trinh: " << yeuCau.maTienTrinh << '\n';
    noiXuat << "Yeu cau: " << yeuCau.dungLuongYeuCauKB << " KB\n";

    // Buoc 1: Hien thi RAM truoc cap phat
    noiXuat << "\nBuoc 1. Cac vung RAM truoc cap phat:\n";

    const long long tongDungLuongTrong = tongDungLuongTrongKB(boNhoTruoc);
    const int vungTrongLonNhat = dungLuongVungLonNhatKB(boNhoTruoc);

    if (boNhoTruoc.empty()) {
        noiXuat << "(Khong co vung RAM trong)\n";
    }

    for (const VungTrong& vung : boNhoTruoc) {
        noiXuat << "H" << vung.ma
            << ": bat dau=" << vung.diaChiBatDauKB
            << " KB, trong=" << vung.dungLuongTrongKB << " KB";

        if (yeuCau.dungLuongYeuCauKB <= 0) {
            noiXuat << " -> YEU CAU KHONG HOP LE";
        }
        else if (vung.dungLuongTrongKB >= yeuCau.dungLuongYeuCauKB) {
            noiXuat << " -> DU";
        }
        else {
            noiXuat << " -> KHONG DU";
        }

        noiXuat << '\n';
    }

    // Buoc 2: Hien thi ket qua Best Fit
    noiXuat << "\nBuoc 2. Ket qua lua chon:\n";

    if (ketQua.thanhCong) {
        noiXuat << "THANH CONG: Chon H"
            << ketQua.maVung << '\n';

        // Tim khoang RAM thay doi, khong chi dua vao ma H.
        bool daTimThay = false;

        for (std::size_t i = 0;
             i < boNhoTruoc.size() && i < boNhoSau.size();
             ++i) {

            const VungTrong& vung = boNhoTruoc[i];
            const VungTrong& sau = boNhoSau[i];

            if (vung.ma != ketQua.maVung ||
                sau.ma != vung.ma ||
                static_cast<long long>(sau.diaChiBatDauKB) -
                    vung.diaChiBatDauKB !=
                    yeuCau.dungLuongYeuCauKB ||
                static_cast<long long>(vung.dungLuongTrongKB) -
                    sau.dungLuongTrongKB !=
                    yeuCau.dungLuongYeuCauKB) {
                continue;
            }

            noiXuat << "Vung truoc: bat dau="
                << vung.diaChiBatDauKB
                << " KB, trong="
                << vung.dungLuongTrongKB << " KB\n";

            noiXuat << "Dia chi da cap: ["
                << vung.diaChiBatDauKB << ", "
                << (static_cast<long long>(vung.diaChiBatDauKB)
                    + yeuCau.dungLuongYeuCauKB)
                << ") KB\n";

            daTimThay = true;
            break;
        }

        if (!daTimThay) {
            noiXuat << "Khong xac dinh duoc dia chi cap phat.\n";
        }

        noiXuat << "Dung luong con lai tai vung da chon: "
            << ketQua.dungLuongConLaiKB << " KB\n";
    }
    else {
        noiXuat << "THAT BAI";

        if (!ketQua.lyDo.empty()) {
            noiXuat << ": " << ketQua.lyDo;
        }

        noiXuat << '\n';

        if (yeuCau.dungLuongYeuCauKB > 0) {
            if (tongDungLuongTrong < yeuCau.dungLuongYeuCauKB) {
                noiXuat << "Tong RAM trong khong du.\n";
            }
            else if (vungTrongLonNhat < yeuCau.dungLuongYeuCauKB) {
                noiXuat << "RAM trong du tong dung luong "
                    << "nhung bi phan manh ngoai.\n";
            }
        }
    }

    // Buoc 3: Hien thi RAM boNhoSau cap phat
    noiXuat << "\nBuoc 3. RAM sau thao tac:\n";

    if (boNhoSau.empty()) {
        noiXuat << "(Khong con vung RAM trong)\n";
    }

    for (const VungTrong& vung : boNhoSau) {
        noiXuat << "H" << vung.ma
            << ": bat dau=" << vung.diaChiBatDauKB
            << " KB, trong=" << vung.dungLuongTrongKB << " KB\n";
    }

    noiXuat << "====================================\n";
}
