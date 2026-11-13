#pragma once

#include "mo_hinh.hpp"

// First Fit
KetQuaCapPhat capPhatDauTien(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
);

// Best Fit
KetQuaCapPhat capPhatVuaNhat(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
);

// Worst Fit
KetQuaCapPhat capPhatLonNhat(
    TrangThaiBoNho& boNho,
    const YeuCau& yeuCau
);