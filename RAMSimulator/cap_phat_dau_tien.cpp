#include "include/thuat_toan_cap_phat.hpp"
#include "include/bo_nho.hpp"
#include <cstddef>

// Thuat toan First Fit
// Chon vung RAM trong dau tien (theo thu tu dia chi tu thap den cao) co dung luong >= yeu cau
KetQuaCapPhat capPhatDauTien(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
) {
    KetQuaCapPhat ketQua;
    ketQua.maTienTrinh = yeuCau.maTienTrinh;

    // Buoc 1: Kiem tra tinh hop le cua yeu cau cap phat
    if (yeuCau.maTienTrinh.empty() || yeuCau.dungLuongYeuCauKB <= 0) {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    // Buoc 2: Khoi tao vi tri vung nho tim duoc
    std::size_t viTriTimThay = boNho.size();

    // Buoc 3: Duyet tuan tu tu dau danh sach (dia chi thap den cao)
    for (std::size_t chiSo = 0; chiSo < boNho.size(); ++chiSo) {
        // Tim vung trong dau tien co dung luong du dap ung
        if (boNho[chiSo].dungLuongTrongKB >= yeuCau.dungLuongYeuCauKB) {
            viTriTimThay = chiSo;
            break; // First Fit: chon vung dau tien va dung tim kiem ngay
        }
    }

    // Buoc 4: Neu khong tim thay vung phu hop
    if (viTriTimThay == boNho.size()) {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    // Su dung ham cap phat chung de cap nhat RAM.
    return capPhatTuVungTrong(boNho, viTriTimThay, yeuCau);
}
