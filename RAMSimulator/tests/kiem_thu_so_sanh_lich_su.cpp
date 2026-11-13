
#include "so_sanh_lich_su.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

bool bangNhau(
    const BaoCaoLichSu& a,
    const BaoCaoLichSu& b
) {
    return
        a.capPhatThanhCong == b.capPhatThanhCong &&
        a.capPhatThatBai == b.capPhatThatBai &&
        a.giaiPhongThanhCong == b.giaiPhongThanhCong &&
        a.giaiPhongBoQua == b.giaiPhongBoQua &&
        a.soLanPhanManhNgoai == b.soLanPhanManhNgoai &&
        a.soLanThieuTongRam == b.soLanThieuTongRam &&
        a.soTienTrinhDangChiem == b.soTienTrinhDangChiem &&
        a.soVungTrong == b.soVungTrong &&
        a.tongRamTrongKB == b.tongRamTrongKB &&
        a.vungTrongLonNhatKB == b.vungTrongLonNhatKB;
}

void kiemTra(
    const BaoCaoLichSu& ketQua,
    const BaoCaoLichSu& mongDoi,
    const char* ten
) {
    if (!bangNhau(ketQua, mongDoi)) {
        std::cerr << "FAIL - " << ten << '\n';
        std::exit(EXIT_FAILURE);
    }

    std::cout << "PASS - " << ten << '\n';
}

int main() {
    // Cung mot trang thai RAM ban dau.
    const TrangThaiBoNho ramBanDau = {
        {1, 0, 100},
        {2, 110, 500},
        {3, 830, 300}
    };

    // Bay su kien da kiem chung tren giao dien.
    const std::vector<SuKienRam> lichSu = {
        {LoaiSuKienRam::CapPhat, "P1", 212},
        {LoaiSuKienRam::CapPhat, "P2", 417},
        {LoaiSuKienRam::GiaiPhong, "P1", 0},
        {LoaiSuKienRam::CapPhat, "P3", 250},
        {LoaiSuKienRam::GiaiPhong, "P2", 0},
        {LoaiSuKienRam::CapPhat, "P4", 400},
        {LoaiSuKienRam::CapPhat, "P5", 500}
    };

    // Thu tu: cap thanh cong, cap that bai,
    // giai phong thanh cong, giai phong bo qua,
    // phan manh ngoai, thieu tong RAM,
    // so tien trinh dang chiem, so vung trong,
    // tong RAM trong, vung trong lon nhat.
    const BaoCaoLichSu mongDoiFF = {
        2, 3, 1, 1, 3, 0, 1, 3, 650, 300
    };

    const BaoCaoLichSu mongDoiBF = {
        4, 1, 2, 0, 0, 1, 2, 3, 250, 100
    };

    const BaoCaoLichSu mongDoiWF = {
        2, 3, 1, 1, 3, 0, 1, 3, 650, 300
    };

    kiemTra(
        moPhongLichSu(ramBanDau, lichSu, 0),
        mongDoiFF,
        "First Fit - 7 su kien"
    );

    kiemTra(
        moPhongLichSu(ramBanDau, lichSu, 1),
        mongDoiBF,
        "Best Fit - 7 su kien"
    );

    kiemTra(
        moPhongLichSu(ramBanDau, lichSu, 2),
        mongDoiWF,
        "Worst Fit - 7 su kien"
    );

    // Giai phong tien trinh khong ton tai
    // khong duoc lam tang RAM.
    const std::vector<SuKienRam> lichSuKhongHopLe = {
        {LoaiSuKienRam::GiaiPhong, "KHONG_TON_TAI", 0}
    };

    const BaoCaoLichSu mongDoiBoQua = {
        0, 0, 0, 1, 0, 0, 0, 3, 900, 500
    };

    kiemTra(
        moPhongLichSu(ramBanDau, lichSuKhongHopLe, 0),
        mongDoiBoQua,
        "Giai phong khong ton tai"
    );

    // Chay mo phong khong duoc sua RAM ban dau.
    if (ramBanDau.size() != 3 ||
        tongDungLuongTrongKB(ramBanDau) != 900 ||
        ramBanDau[0].diaChiBatDauKB != 0 ||
        ramBanDau[1].diaChiBatDauKB != 110 ||
        ramBanDau[2].diaChiBatDauKB != 830) {

        std::cerr << "FAIL - RAM ban dau bi thay doi\n";
        return EXIT_FAILURE;
    }

    std::cout << "PASS - Bao toan RAM ban dau\n";

    // KIEM_THU_HAI_KHOANG_TRONG_V2
    // Su dung pham vi rieng de khong trung ten bien.
    {
        const TrangThaiBoNho ramKiemTra = {
            {1, 0, 100},
            {2, 110, 500},
            {3, 830, 300}
        };

        const std::vector<SuKienRam> lichSuKiemTra = {
            {LoaiSuKienRam::CapPhat, "P1", 250},
            {LoaiSuKienRam::CapPhat, "P2", 30},
            {LoaiSuKienRam::GiaiPhong, "P1", 0},
            {LoaiSuKienRam::CapPhat, "P3", 15},
            {LoaiSuKienRam::GiaiPhong, "P3", 0}
        };

        const BaoCaoLichSu mongDoiFF = {
            3, 0, 2, 0, 0, 0, 1, 3, 870, 500
        };

        const BaoCaoLichSu mongDoiBF = {
            3, 0, 2, 0, 0, 0, 1, 4, 870, 500
        };

        const BaoCaoLichSu mongDoiWF = {
            3, 0, 2, 0, 0, 0, 1, 3, 870, 500
        };

        kiemTra(
            moPhongLichSu(ramKiemTra, lichSuKiemTra, 0),
            mongDoiFF,
            "First Fit - giai phong va gop vung"
        );

        kiemTra(
            moPhongLichSu(ramKiemTra, lichSuKiemTra, 1),
            mongDoiBF,
            "Best Fit - hai khoang trong tai H3"
        );

        kiemTra(
            moPhongLichSu(ramKiemTra, lichSuKiemTra, 2),
            mongDoiWF,
            "Worst Fit - giai phong va gop vung"
        );
    }

    return EXIT_SUCCESS;
}
