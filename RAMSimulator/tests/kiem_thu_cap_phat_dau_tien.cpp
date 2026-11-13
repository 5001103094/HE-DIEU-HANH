#include "../include/thuat_toan_cap_phat.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

// Ham ho tro kiem tra hai trang thai RAM
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
    std::cout << "========================================\n";
    std::cout << "   KIEM THU THUAT TOAN FIRST FIT   \n";
    std::cout << "========================================\n\n";

    int soCaDat = 0;
    int tongSoCa = 10;

    // TC01: Test case kinh dien (Silberschatz)
    {
        std::cout << "[TC01] Test case kinh dien: ";
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 100, 500},
            {3, 600, 200},
            {4, 800, 300},
            {5, 1100, 600}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 212 });
        assert(ketQua1.thanhCong && ketQua1.maVung == 2 && ketQua1.dungLuongConLaiKB == 288 && boNho[1].diaChiBatDauKB == 312);

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 417 });
        assert(ketQua2.thanhCong && ketQua2.maVung == 5 && ketQua2.dungLuongConLaiKB == 183 && boNho[4].diaChiBatDauKB == 1517);

        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 112 });
        assert(ketQua3.thanhCong && ketQua3.maVung == 2 && ketQua3.dungLuongConLaiKB == 176 && boNho[1].diaChiBatDauKB == 424);

        KetQuaCapPhat ketQua4 = capPhatDauTien(boNho, { "P4", 426 });
        assert(!ketQua4.thanhCong && ketQua4.maVung == -1);
        assert(ketQua4.lyDo == "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC02: Vua khit hoan toan (Exact Fit)
    {
        std::cout << "[TC02] Vua khit hoan toan: ";
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 100, 200},
            {3, 300, 300}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 100 });
        assert(ketQua1.thanhCong && ketQua1.maVung == 1 && ketQua1.dungLuongConLaiKB == 0 && boNho[0].diaChiBatDauKB == 100);

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 200 });
        assert(ketQua2.thanhCong && ketQua2.maVung == 2 && ketQua2.dungLuongConLaiKB == 0 && boNho[1].diaChiBatDauKB == 300);

        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 300 });
        assert(ketQua3.thanhCong && ketQua3.maVung == 3 && ketQua3.dungLuongConLaiKB == 0 && boNho[2].diaChiBatDauKB == 600);

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC03: Khong du tong dung luong RAM trong
    {
        std::cout << "[TC03] Khong du tong dung luong RAM trong: ";
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 100, 200}
        };
        TrangThaiBoNho truoc = boNho;

        KetQuaCapPhat ketQuaThu = capPhatDauTien(boNho, { "P1", 500 });
        assert(!ketQuaThu.thanhCong && ketQuaThu.maVung == -1);
        assert(ketQuaThu.lyDo == "Khong du tong dung luong RAM trong.");
        assert(boNhoGiongNhau(boNho, truoc));

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC04: Mot khoi lon chia nhieu lan
    {
        std::cout << "[TC04] Mot khoi lon chia nhieu lan: ";
        TrangThaiBoNho boNho = {
            {1, 0, 1000}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 100 });
        assert(ketQua1.thanhCong && ketQua1.maVung == 1 && boNho[0].diaChiBatDauKB == 100 && boNho[0].dungLuongTrongKB == 900);

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 100 });
        assert(ketQua2.thanhCong && ketQua2.maVung == 1 && boNho[0].diaChiBatDauKB == 200 && boNho[0].dungLuongTrongKB == 800);

        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 100 });
        assert(ketQua3.thanhCong && ketQua3.maVung == 1 && boNho[0].diaChiBatDauKB == 300 && boNho[0].dungLuongTrongKB == 700);

        KetQuaCapPhat ketQua4 = capPhatDauTien(boNho, { "P4", 100 });
        assert(ketQua4.thanhCong && ketQua4.maVung == 1 && boNho[0].diaChiBatDauKB == 400 && boNho[0].dungLuongTrongKB == 600);

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC05: Het cho giua chung
    {
        std::cout << "[TC05] Het cho giua chung: ";
        TrangThaiBoNho boNho = {
            {1, 0, 50},
            {2, 50, 50},
            {3, 100, 50}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 50 });
        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 50 });
        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 50 });
        assert(ketQua1.thanhCong && ketQua2.thanhCong && ketQua3.thanhCong);

        KetQuaCapPhat ketQua4 = capPhatDauTien(boNho, { "P4", 50 });
        assert(!ketQua4.thanhCong && ketQua4.maVung == -1);
        assert(ketQua4.lyDo == "Khong du tong dung luong RAM trong.");

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC06: Cac khoi bang nhau (Tie-break)
    {
        std::cout << "[TC06] Cac khoi bang nhau (Tie-break): ";
        TrangThaiBoNho boNho = {
            {1, 0, 100},
            {2, 100, 500},
            {3, 600, 100},
            {4, 700, 500}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 90 });
        assert(ketQua1.thanhCong && ketQua1.maVung == 1 && boNho[0].dungLuongTrongKB == 10);

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 90 });
        assert(ketQua2.thanhCong && ketQua2.maVung == 2 && boNho[1].dungLuongTrongKB == 410);

        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 90 });
        assert(ketQua3.thanhCong && ketQua3.maVung == 2 && boNho[1].dungLuongTrongKB == 320);

        KetQuaCapPhat ketQua4 = capPhatDauTien(boNho, { "P4", 90 });
        assert(ketQua4.thanhCong && ketQua4.maVung == 2 && boNho[1].dungLuongTrongKB == 230);

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC07: Danh sach RAM trong rong
    {
        std::cout << "[TC07] Danh sach RAM trong rong: ";
        TrangThaiBoNho boNho = {};

        KetQuaCapPhat ketQuaThu = capPhatDauTien(boNho, { "P1", 10 });
        assert(!ketQuaThu.thanhCong && ketQuaThu.maVung == -1);
        assert(ketQuaThu.lyDo == "Khong du tong dung luong RAM trong.");

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC08: Yeu cau bang 0 (Bien)
    {
        std::cout << "[TC08] Yeu cau bang 0 (Bien): ";
        TrangThaiBoNho boNho = { {1, 0, 100} };
        TrangThaiBoNho truoc = boNho;

        KetQuaCapPhat ketQuaThu = capPhatDauTien(boNho, { "P1", 0 });
        assert(!ketQuaThu.thanhCong && ketQuaThu.maVung == -1);
        assert(ketQuaThu.lyDo == "Yeu cau cap phat khong hop le.");
        assert(boNhoGiongNhau(boNho, truoc));

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC09: Phan manh ngoai (External Fragmentation)
    {
        std::cout << "[TC09] Phan manh ngoai: ";
        TrangThaiBoNho boNho = {
            {1, 0, 300},
            {2, 400, 100},
            {3, 600, 200}
        };

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", 150 });
        assert(ketQua1.thanhCong && ketQua1.maVung == 1 && boNho[0].dungLuongTrongKB == 150);

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "P2", 150 });
        assert(ketQua2.thanhCong && ketQua2.maVung == 1 && boNho[0].dungLuongTrongKB == 0);

        KetQuaCapPhat ketQua3 = capPhatDauTien(boNho, { "P3", 150 });
        assert(ketQua3.thanhCong && ketQua3.maVung == 3 && boNho[2].dungLuongTrongKB == 50);

        KetQuaCapPhat ketQua4 = capPhatDauTien(boNho, { "P4", 150 });
        assert(!ketQua4.thanhCong && ketQua4.maVung == -1);
        assert(ketQua4.lyDo == "Phan manh ngoai: khong co vung RAM lien tuc du lon.");

        std::cout << "PASS\n";
        soCaDat++;
    }

    // TC10: Du lieu am hoac ma tien trinh rong
    {
        std::cout << "[TC10] Du lieu am hoac ma tien trinh rong: ";
        TrangThaiBoNho boNho = { {1, 0, 100} };
        TrangThaiBoNho truoc = boNho;

        KetQuaCapPhat ketQua1 = capPhatDauTien(boNho, { "P1", -50 });
        assert(!ketQua1.thanhCong && ketQua1.maVung == -1);
        assert(ketQua1.lyDo == "Yeu cau cap phat khong hop le.");

        KetQuaCapPhat ketQua2 = capPhatDauTien(boNho, { "", 50 });
        assert(!ketQua2.thanhCong && ketQua2.maVung == -1);
        assert(ketQua2.lyDo == "Yeu cau cap phat khong hop le.");

        assert(boNhoGiongNhau(boNho, truoc));

        std::cout << "PASS\n";
        soCaDat++;
    }

    std::cout << "\n----------------------------------------\n";
    std::cout << "KET QUA: " << soCaDat << "/" << tongSoCa << " TESTS PASSED!\n";
    std::cout << "----------------------------------------\n";

    return (soCaDat == tongSoCa) ? 0 : 1;
}
