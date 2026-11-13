
#include "../include/thuat_toan_cap_phat.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>

// Kiem tra hai trang thai RAM co giong nhau khong
bool boNhoGiongNhau(const TrangThaiBoNho& vungA, const TrangThaiBoNho& vungB) {
    if (vungA.size() != vungB.size()) return false;

    for (std::size_t chiSo = 0; chiSo < vungA.size(); ++chiSo) {
        if (vungA[chiSo].ma != vungB[chiSo].ma ||
            vungA[chiSo].diaChiBatDauKB != vungB[chiSo].diaChiBatDauKB ||
            vungA[chiSo].dungLuongTrongKB != vungB[chiSo].dungLuongTrongKB) {
            return false;
        }
    }
    return true;
}

int main() {
    // TC01: Chon vung nho nhat du lon
    {
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 150, 50},
            {3, 250, 200}
        };

        KetQuaCapPhat ketQuaThu = capPhatVuaNhat(boNho, { "P1", 45 });

        assert(ketQuaThu.thanhCong);
        assert(ketQuaThu.maVung == 2);
        assert(ketQuaThu.dungLuongConLaiKB == 5);
        assert(boNho[1].diaChiBatDauKB == 195);
        assert(boNho[1].dungLuongTrongKB == 5);
        assert(boNho[0].dungLuongTrongKB == 100);
        assert(boNho[2].dungLuongTrongKB == 200);

        std::cout << "TC01: PASS\n";
    }

    // TC02: Hai vung bang nhau, chon startKB nho hon
    {
        TrangThaiBoNho boNho = {
            {1, 80, 20},
            {2, 50, 20},
            {3, 0, 40}
        };

        KetQuaCapPhat ketQuaThu = capPhatVuaNhat(boNho, { "P2", 18 });

        assert(ketQuaThu.thanhCong);
        assert(ketQuaThu.maVung == 2);
        assert(boNho[1].diaChiBatDauKB == 68);
        assert(boNho[1].dungLuongTrongKB == 2);

        std::cout << "TC02: PASS\n";
    }

    // TC03: Cap phat vua du dung luong
    {
        TrangThaiBoNho boNho = { {1, 100, 30} };

        KetQuaCapPhat ketQuaThu = capPhatVuaNhat(boNho, { "P3", 30 });

        assert(ketQuaThu.thanhCong);
        assert(ketQuaThu.dungLuongConLaiKB == 0);
        assert(boNho[0].diaChiBatDauKB == 130);
        assert(boNho[0].dungLuongTrongKB == 0);

        std::cout << "TC03: PASS\n";
    }

    // TC04: Khong co vung du lon (phan manh ngoai)
    {
        TrangThaiBoNho boNho = {
            {1, 0, 40},
            {2, 50, 2},
            {3, 70, 20}
        };
        TrangThaiBoNho truoc = boNho;

        KetQuaCapPhat ketQuaThu = capPhatVuaNhat(boNho, { "P4", 45 });

        assert(!ketQuaThu.thanhCong);
        assert(ketQuaThu.maVung == -1);
        assert(boNhoGiongNhau(boNho, truoc));

        std::cout << "TC04: PASS\n";
    }

    // TC05: Yeu cau khong hop le
    {
        TrangThaiBoNho boNho = { {1, 0, 100} };
        TrangThaiBoNho truoc = boNho;

        KetQuaCapPhat ketQuaThu = capPhatVuaNhat(boNho, { "P5", 0 });

        assert(!ketQuaThu.thanhCong);
        assert(boNhoGiongNhau(boNho, truoc));

        std::cout << "TC05: PASS\n";
    }

    // TC06: Cap phat nhieu tien trinh lien tiep
    {
        TrangThaiBoNho boNho = { {1, 0, 100} };

        KetQuaCapPhat ketQua1 = capPhatVuaNhat(boNho, { "P1", 30 });
        KetQuaCapPhat ketQua2 = capPhatVuaNhat(boNho, { "P2", 40 });

        assert(ketQua1.thanhCong && ketQua2.thanhCong);
        assert(boNho[0].diaChiBatDauKB == 70);
        assert(boNho[0].dungLuongTrongKB == 30);

        std::cout << "TC06: PASS\n";
    }

    std::cout << "\nALL BEST FIT TESTS PASSED!\n";
    return 0;
}
