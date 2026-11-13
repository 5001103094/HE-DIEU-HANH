#pragma once

#include "mo_hinh.hpp"
#include <iosfwd>

// In dien bien cap phat Best Fit ma khong thay doi trang thai bo nho.
void hienThiDienBienCapPhatVuaNhat(
    const TrangThaiBoNho& boNhoTruoc,
    const YeuCau& yeuCau,
    const KetQuaCapPhat& ketQua,
    const TrangThaiBoNho& boNhoSau,
    std::ostream& noiXuat
);
