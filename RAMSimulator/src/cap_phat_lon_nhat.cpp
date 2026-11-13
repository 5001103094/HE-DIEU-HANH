#include "../include/thuat_toan_cap_phat.hpp"
#include "../include/bo_nho.hpp"

#include <cstddef>

// Worst Fit: chon vung trong lon nhat du dap ung yeu cau.
// Neu co nhieu vung bang nhau, chon vung co dia chi bat dau nho nhat.
KetQuaCapPhat capPhatLonNhat(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau)
{
    KetQuaCapPhat ketQua;
    ketQua.maTienTrinh = yeuCau.maTienTrinh;

    if (yeuCau.maTienTrinh.empty() || yeuCau.dungLuongYeuCauKB <= 0)
    {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    // Gia tri boNho.size() cho biet chua tim thay vung phu hop.
    std::size_t viTriLonNhat = boNho.size();

    for (std::size_t chiSo = 0; chiSo < boNho.size(); ++chiSo)
    {
        const VungTrong& vungDangXet = boNho[chiSo];
        if (vungDangXet.dungLuongTrongKB < yeuCau.dungLuongYeuCauKB)
        {
            continue;
        }

        if (viTriLonNhat == boNho.size() ||
            vungDangXet.dungLuongTrongKB > boNho[viTriLonNhat].dungLuongTrongKB ||
            (vungDangXet.dungLuongTrongKB == boNho[viTriLonNhat].dungLuongTrongKB &&
             vungDangXet.diaChiBatDauKB < boNho[viTriLonNhat].diaChiBatDauKB))
        {
            viTriLonNhat = chiSo;
        }
    }

    if (viTriLonNhat == boNho.size())
    {
        ketQua.lyDo = lyDoCapPhatThatBai(boNho, yeuCau);
        return ketQua;
    }

    return capPhatTuVungTrong(boNho, viTriLonNhat, yeuCau);
}
