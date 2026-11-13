
#pragma once

#include "bo_nho.hpp"
#include <vector>
#include <string>
#include <cstddef>

enum class LoaiSuKienRam {
    CapPhat,
    GiaiPhong
};

struct SuKienRam {
    LoaiSuKienRam loai;
    std::string maTienTrinh;
    int dungLuongKB = 0;
};

struct BaoCaoLichSu {
    int capPhatThanhCong = 0;
    int capPhatThatBai = 0;
    int giaiPhongThanhCong = 0;
    int giaiPhongBoQua = 0;
    int soLanPhanManhNgoai = 0;
    int soLanThieuTongRam = 0;
    int soTienTrinhDangChiem = 0;
    int soVungTrong = 0;
    long long tongRamTrongKB = 0;
    int vungTrongLonNhatKB = 0;
};

// Chay lai cung lich su tren mot thuat toan.
// loaiThuatToan: 0 = First Fit, 1 = Best Fit, 2 = Worst Fit.
inline BaoCaoLichSu moPhongLichSu(
    const TrangThaiBoNho& ramBanDau,
    const std::vector<SuKienRam>& lichSu,
    int loaiThuatToan
) {
    TrangThaiBoNho ram = saoChepBoNho(ramBanDau);
    DanhSachDaCapPhat dangSoHuu;
    BaoCaoLichSu baoCao;

    for (const SuKienRam& suKien : lichSu) {
        if (suKien.loai == LoaiSuKienRam::GiaiPhong) {
            std::string loi;

            if (giaiPhongTienTrinh(
                    ram, dangSoHuu,
                    suKien.maTienTrinh, loi)) {
                ++baoCao.giaiPhongThanhCong;
            } else {
                ++baoCao.giaiPhongBoQua;
            }

            continue;
        }

        YeuCau yeuCau{
            suKien.maTienTrinh,
            suKien.dungLuongKB
        };

        std::size_t viTriChon = ram.size();

        for (std::size_t i = 0; i < ram.size(); ++i) {
            const VungTrong& vung = ram[i];

            if (yeuCau.dungLuongYeuCauKB <= 0 ||
                vung.dungLuongTrongKB <
                    yeuCau.dungLuongYeuCauKB) {
                continue;
            }

            if (viTriChon == ram.size()) {
                viTriChon = i;

                if (loaiThuatToan == 0) {
                    break;
                }

                continue;
            }

            const VungTrong& hienTai = ram[viTriChon];

            bool thayThe = false;

            if (loaiThuatToan == 1) {
                thayThe =
                    vung.dungLuongTrongKB <
                    hienTai.dungLuongTrongKB;
            } else if (loaiThuatToan == 2) {
                thayThe =
                    vung.dungLuongTrongKB >
                    hienTai.dungLuongTrongKB;
            }

            if (loaiThuatToan != 0 &&
                vung.dungLuongTrongKB ==
                hienTai.dungLuongTrongKB) {
                thayThe =
                    vung.diaChiBatDauKB <
                    hienTai.diaChiBatDauKB;
            }

            if (thayThe) {
                viTriChon = i;
            }
        }

        KetQuaCapPhat ketQua;

        if (viTriChon < ram.size()) {
            ketQua = capPhatCoTheoDoi(
                ram, dangSoHuu, viTriChon, yeuCau
            );
        } else {
            ketQua.maTienTrinh = yeuCau.maTienTrinh;
            ketQua.lyDo = lyDoCapPhatThatBai(
                ram, yeuCau
            );
        }

        if (ketQua.thanhCong) {
            ++baoCao.capPhatThanhCong;
        } else {
            ++baoCao.capPhatThatBai;

            if (ketQua.lyDo.find("Phan manh ngoai") !=
                std::string::npos) {
                ++baoCao.soLanPhanManhNgoai;
            }

            if (ketQua.lyDo.find("Khong du tong") !=
                std::string::npos) {
                ++baoCao.soLanThieuTongRam;
            }
        }
    }

    baoCao.soTienTrinhDangChiem =
        static_cast<int>(dangSoHuu.size());

    baoCao.tongRamTrongKB =
        tongDungLuongTrongKB(ram);

    baoCao.vungTrongLonNhatKB =
        dungLuongVungLonNhatKB(ram);

    for (const VungTrong& vung : ram) {
        if (vung.dungLuongTrongKB > 0) {
            ++baoCao.soVungTrong;
        }
    }

    return baoCao;
}
