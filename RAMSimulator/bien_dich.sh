#!/bin/sh
set -eu

# Dung cho macOS/Linux. Duong dan lay theo vi tri tep, khong phu thuoc Terminal.
cd "$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"

if ! command -v cmake >/dev/null 2>&1; then
    echo "Chua tim thay CMake. Hay cai CMake va trinh bien dich C++17." >&2
    exit 1
fi

cmake -S . -B ket_qua_bien_dich -DCMAKE_BUILD_TYPE=Debug
cmake --build ket_qua_bien_dich --config Debug
echo "Bien dich hoan tat: ket_qua_bien_dich/mo_phong_bo_nho"
