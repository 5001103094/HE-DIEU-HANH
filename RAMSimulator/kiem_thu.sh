#!/bin/sh
set -eu

cd "$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
sh ./bien_dich.sh
(cd ket_qua_bien_dich && ctest -C Debug --output-on-failure)
echo "Da chay xong 7 bo kiem thu. Xem dong tong ket o tren."
