
#include "include/thuat_toan_cap_phat.hpp"
#include "include/bo_nho.hpp"
#include <cstddef>

// Thuat toan Best Fit
KetQuaCapPhat capPhatVuaNhat(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
) {
    KetQuaCapPhat ketQua;
    ketQua.maTienTrinh = yeuCau.maTienTrinh;

    // Buoc 1: Kiem tra yeu cau cap phat
    if (yeuCau.maTienTrinh.empty() || yeuCau.dungLuongYeuCauKB <= 0) {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    // Buoc 2: Khoi tao vi tri vung nho
    std::size_t viTriVuaNhat = boNho.size();

    // Buoc 3: Duyet danh sach cac vung RAM trong
    for (std::size_t chiSo = 0; chiSo < boNho.size(); ++chiSo) {
        const VungTrong& vungTrong = boNho[chiSo];

        // Bo qua vung khong du dung luong
        if (vungTrong.dungLuongTrongKB < yeuCau.dungLuongYeuCauKB) {
            continue;
        }

        // Chon vung nho nhat du lon
        // Neu bang kich thuoc, uu tien dia chi bat dau nho nhat
        if (viTriVuaNhat == boNho.size() ||
            vungTrong.dungLuongTrongKB < boNho[viTriVuaNhat].dungLuongTrongKB ||
            (vungTrong.dungLuongTrongKB == boNho[viTriVuaNhat].dungLuongTrongKB &&
                vungTrong.diaChiBatDauKB < boNho[viTriVuaNhat].diaChiBatDauKB)) {
            viTriVuaNhat = chiSo;
        }
    }

    // Buoc 4: Khong tim thay vung phu hop
    if (viTriVuaNhat == boNho.size()) {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    // Su dung ham cap phat chung de cap nhat RAM.
    return capPhatTuVungTrong(boNho, viTriVuaNhat, yeuCau);
}
