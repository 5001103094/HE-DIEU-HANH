#include "../include/bo_nho.hpp"

// 1. Tinh tong dung luong RAM con trong
long long tongDungLuongTrongKB(const TrangThaiBoNho& boNho)
{
    long long tongSo = 0;

    for (const VungTrong& vungTrong : boNho)
    {
        tongSo += vungTrong.dungLuongTrongKB;
    }

    return tongSo;
}

// 2. Tim vung RAM trong lon nhat
int dungLuongVungLonNhatKB(const TrangThaiBoNho& boNho)
{
    int giaTriLonNhat = 0;

    for (const VungTrong& vungTrong : boNho)
    {
        if (vungTrong.dungLuongTrongKB > giaTriLonNhat)
        {
            giaTriLonNhat = vungTrong.dungLuongTrongKB;
        }
    }

    return giaTriLonNhat;
}

// 3. Sao chep trang thai RAM
TrangThaiBoNho saoChepBoNho(const TrangThaiBoNho& boNho)
{
    return boNho;
}

// 4. Xac dinh nguyen nhan cap phat that bai
std::string lyDoCapPhatThatBai(
    const TrangThaiBoNho& boNho,
    const YeuCau& yeuCau)
{
    if (yeuCau.maTienTrinh.empty() || yeuCau.dungLuongYeuCauKB <= 0)
    {
        return "Yeu cau cap phat khong hop le.";
    }

    if (tongDungLuongTrongKB(boNho) < yeuCau.dungLuongYeuCauKB)
    {
        return "Khong du tong dung luong RAM trong.";
    }

    if (dungLuongVungLonNhatKB(boNho) < yeuCau.dungLuongYeuCauKB)
    {
        return "Phan manh ngoai: khong co vung RAM lien tuc du lon.";
    }

    return "";
}

// 5. Cap phat RAM tu dau vung trong duoc chon
KetQuaCapPhat capPhatTuVungTrong(
    TrangThaiBoNho& boNho,
    std::size_t viTriVung,
    const YeuCau& yeuCau)
{
    KetQuaCapPhat ketQua;
    ketQua.maTienTrinh = yeuCau.maTienTrinh;

    if (yeuCau.maTienTrinh.empty() || yeuCau.dungLuongYeuCauKB <= 0)
    {
        ketQua.lyDo = "Yeu cau cap phat khong hop le.";
        return ketQua;
    }

    if (viTriVung >= boNho.size())
    {
        ketQua.lyDo = "Vung RAM khong ton tai.";
        return ketQua;
    }

    VungTrong& vungDaChon = boNho[viTriVung];

    if (vungDaChon.dungLuongTrongKB < yeuCau.dungLuongYeuCauKB)
    {
        ketQua.lyDo = "Vung RAM khong du dung luong.";
        return ketQua;
    }

    // Cap phat tu dau vung RAM trong
    vungDaChon.diaChiBatDauKB += yeuCau.dungLuongYeuCauKB;
    vungDaChon.dungLuongTrongKB -= yeuCau.dungLuongYeuCauKB;

    ketQua.thanhCong = true;
    ketQua.maVung = vungDaChon.ma;
    ketQua.dungLuongConLaiKB = vungDaChon.dungLuongTrongKB;
    ketQua.lyDo = "";

    return ketQua;
}

// VONG_DOI_BO_NHO_V1
#include <algorithm>
#include <limits>

// 6. Cap phat va luu thong tin vung da cap.
KetQuaCapPhat capPhatCoTheoDoi(
    TrangThaiBoNho& boNho,
    DanhSachDaCapPhat& daCapPhat,
    std::size_t viTriVung,
    const YeuCau& yeuCau)
{
    KetQuaCapPhat ketQua;
    ketQua.maTienTrinh = yeuCau.maTienTrinh;

    for (const VungDaCapPhat& muc : daCapPhat) {
        if (muc.maTienTrinh == yeuCau.maTienTrinh) {
            ketQua.lyDo = "Tien trinh da duoc cap phat.";
            return ketQua;
        }
    }

    if (viTriVung < boNho.size() &&
        yeuCau.dungLuongYeuCauKB > 0 &&
        yeuCau.dungLuongYeuCauKB <=
            boNho[viTriVung].dungLuongTrongKB) {

        const VungTrong& vung = boNho[viTriVung];

        long long ketThuc =
            static_cast<long long>(vung.diaChiBatDauKB)
            + yeuCau.dungLuongYeuCauKB;

        if (vung.diaChiBatDauKB < 0 ||
            ketThuc > std::numeric_limits<int>::max()) {
            ketQua.lyDo = "Dia chi RAM khong hop le.";
            return ketQua;
        }
    }

    int diaChiDaCap = viTriVung < boNho.size()
        ? boNho[viTriVung].diaChiBatDauKB
        : -1;

    // Su dung lai ham cap phat cu, khong doi thuat toan.
    ketQua = capPhatTuVungTrong(
        boNho, viTriVung, yeuCau
    );

    if (ketQua.thanhCong) {
        daCapPhat.push_back({
            yeuCau.maTienTrinh,
            ketQua.maVung,
            diaChiDaCap,
            yeuCau.dungLuongYeuCauKB
        });
    }

    return ketQua;
}

// 7. Giai phong va gop vung RAM trong.
bool giaiPhongTienTrinh(
    TrangThaiBoNho& boNho,
    DanhSachDaCapPhat& daCapPhat,
    const std::string& maTienTrinh,
    std::string& loi)
{
    loi.clear();

    auto it = std::find_if(
        daCapPhat.begin(),
        daCapPhat.end(),
        [&](const VungDaCapPhat& muc) {
            return muc.maTienTrinh == maTienTrinh;
        }
    );

    if (it == daCapPhat.end()) {
        loi = "Tien trinh khong ton tai hoac da giai phong.";
        return false;
    }

    // Lam viec tren ban sao de tranh sua RAM khi co loi.
    TrangThaiBoNho tam = boNho;

    tam.push_back({
        it->maVung,
        it->diaChiBatDauKB,
        it->dungLuongKB
    });

    std::sort(
        tam.begin(),
        tam.end(),
        [](const VungTrong& a, const VungTrong& b) {
            return a.diaChiBatDauKB < b.diaChiBatDauKB;
        }
    );

    TrangThaiBoNho daGop;

    for (const VungTrong& vung : tam) {
        long long ketThuc =
            static_cast<long long>(vung.diaChiBatDauKB)
            + vung.dungLuongTrongKB;

        if (vung.diaChiBatDauKB < 0 ||
            vung.dungLuongTrongKB < 0 ||
            ketThuc > std::numeric_limits<int>::max()) {
            loi = "Dia chi hoac dung luong RAM khong hop le.";
            return false;
        }

        if (vung.dungLuongTrongKB == 0) {
            continue;
        }

        if (daGop.empty()) {
            daGop.push_back(vung);
            continue;
        }

        VungTrong& truoc = daGop.back();

        long long ketThucTruoc =
            static_cast<long long>(truoc.diaChiBatDauKB)
            + truoc.dungLuongTrongKB;

        if (vung.diaChiBatDauKB < ketThucTruoc) {
            loi = "Vung giai phong chong len RAM da trong.";
            return false;
        }

        if (vung.diaChiBatDauKB == ketThucTruoc) {
            long long tong =
                static_cast<long long>(truoc.dungLuongTrongKB)
                + vung.dungLuongTrongKB;

            if (tong > std::numeric_limits<int>::max()) {
                loi = "Dung luong sau khi gop vuot gioi han.";
                return false;
            }

            truoc.dungLuongTrongKB = static_cast<int>(tong);
        } else {
            daGop.push_back(vung);
        }
    }

    boNho.swap(daGop);
    daCapPhat.erase(it);

    return true;
}
