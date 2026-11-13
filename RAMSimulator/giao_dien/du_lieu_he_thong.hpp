#ifndef DU_LIEU_HE_THONG_HPP
#define DU_LIEU_HE_THONG_HPP

#include <QtGlobal>
#include <QProcess>
#include <QRegularExpression>
#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVector>

#include <algorithm>
#include <limits>

#ifdef Q_OS_MACOS
#include <mach/mach.h>
#include <sys/sysctl.h>
#elif defined(Q_OS_WIN)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

// Thong tin mot tien trinh dang chay tren may.
struct TienTrinhHeThong {
    QString ma;
    qint64 dungLuongKB;
};

// Doc dung luong RAM hien tai cua he dieu hanh.
static bool docRamHeThong(
    qint64& tongKB,
    qint64& khaDungKB,
    QString& ghiChu
) {
#ifdef Q_OS_MACOS
    uint64_t tongByte = 0;
    size_t kichThuoc = sizeof(tongByte);

    if (sysctlbyname(
            "hw.memsize",
            &tongByte,
            &kichThuoc,
            nullptr,
            0
        ) != 0) {
        return false;
    }

    vm_statistics64_data_t thongKe{};
    mach_msg_type_number_t soPhan =
        HOST_VM_INFO64_COUNT;

    if (host_statistics64(
            mach_host_self(),
            HOST_VM_INFO64,
            reinterpret_cast<host_info64_t>(&thongKe),
            &soPhan
        ) != KERN_SUCCESS) {
        return false;
    }

    vm_size_t kichThuocTrang = 0;

    if (host_page_size(
            mach_host_self(),
            &kichThuocTrang
        ) != KERN_SUCCESS) {
        return false;
    }

    // Free + inactive la uoc tinh bo nho co the thu hoi.
    uint64_t soTrang =
        static_cast<uint64_t>(thongKe.free_count) +
        thongKe.inactive_count;

    tongKB = static_cast<qint64>(tongByte / 1024);

    khaDungKB = static_cast<qint64>(
        soTrang * kichThuocTrang / 1024
    );

    ghiChu = "macOS: free + inactive (ước tính)";

#elif defined(Q_OS_WIN)
    MEMORYSTATUSEX thongKe{};
    thongKe.dwLength = sizeof(thongKe);

    if (!GlobalMemoryStatusEx(&thongKe)) {
        return false;
    }

    tongKB = static_cast<qint64>(
        thongKe.ullTotalPhys / 1024
    );

    khaDungKB = static_cast<qint64>(
        thongKe.ullAvailPhys / 1024
    );

    ghiChu = "Windows: bộ nhớ vật lý khả dụng";

#elif defined(Q_OS_LINUX)
    // Doc RAM thuc te tu he dieu hanh Linux.
    // MemTotal: tong RAM vat ly.
    // MemAvailable: RAM co the su dung (uoc tinh).
    QFile tepThongTin("/proc/meminfo");

    if (!tepThongTin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ghiChu = "Linux: không đọc được /proc/meminfo.";
        return false;
    }

    qint64 tongRamDocDuoc = -1;
    qint64 ramKhaDungDocDuoc = -1;

    const QRegularExpression mauThongTin(
        R"(^\s*(MemTotal|MemAvailable):\s*(\d+)\s+kB\s*$)"
    );

    const QStringList cacDong = QString::fromUtf8(
        tepThongTin.readAll()
    ).split('\n');

    for (const QString& dong : cacDong) {
        const QRegularExpressionMatch ketQua =
            mauThongTin.match(dong);

        if (!ketQua.hasMatch()) {
            continue;
        }

        bool dungSo = false;
        const qint64 dungLuong = ketQua.captured(2)
            .toLongLong(&dungSo);

        if (!dungSo || dungLuong <= 0) {
            ghiChu = "Linux: dung lượng RAM không hợp lệ.";
            return false;
        }

        if (ketQua.captured(1) == "MemTotal") {
            tongRamDocDuoc = dungLuong;
        } else {
            ramKhaDungDocDuoc = dungLuong;
        }
    }

    // Kiem tra du lieu truoc khi dua vao mo hinh.
    if (tongRamDocDuoc <= 0 ||
        ramKhaDungDocDuoc <= 0 ||
        ramKhaDungDocDuoc > tongRamDocDuoc) {
        ghiChu = "Linux: số liệu RAM không hợp lệ hoặc bị thiếu.";
        return false;
    }

    tongKB = tongRamDocDuoc;
    khaDungKB = ramKhaDungDocDuoc;

    ghiChu = "Linux: MemAvailable (ước tính từ /proc/meminfo)";

#else
    Q_UNUSED(tongKB);
    Q_UNUSED(khaDungKB);
    ghiChu = "Hệ điều hành chưa được hỗ trợ.";
    return false;
#endif

    return tongKB > 0 && khaDungKB > 0;
}

// Lay danh sach tien trinh dang chay.
// Chi doc thong tin, khong tac dong vao tien trinh.
static bool docTienTrinhHeThong(
    QVector<TienTrinhHeThong>& danhSach,
    QString& loi
) {
    QProcess tienTrinh;

#ifdef Q_OS_WIN
    QString lenh =
        "Get-Process | "
        "Sort-Object WorkingSet64 -Descending | "
        "Select-Object -First 10 | "
        "ForEach-Object { "
        "\"$($_.Id)|$($_.ProcessName)|"
        "$([math]::Ceiling($_.WorkingSet64/1KB))\" "
        "}";

    tienTrinh.start(
        "powershell.exe",
        QStringList{
            "-NoProfile",
            "-NonInteractive",
            "-Command",
            lenh
        }
    );
#else
    tienTrinh.start(
        "ps",
        QStringList{
            "-axo",
            "pid=,rss=,comm="
        }
    );
#endif

    if (!tienTrinh.waitForFinished(15000) ||
        tienTrinh.exitStatus() != QProcess::NormalExit ||
        tienTrinh.exitCode() != 0) {

        loi = "Không đọc được danh sách tiến trình.";
        return false;
    }

    QString ketQua = QString::fromLocal8Bit(
        tienTrinh.readAllStandardOutput()
    );

    QStringList cacDong = ketQua.split('\n');

    QRegularExpression mauMac(
        R"(^\s*(\d+)\s+(\d+)\s+(.+?)\s*$)"
    );

    for (const QString& dong : cacDong) {
        QString ma;
        qint64 dungLuong = 0;

#ifdef Q_OS_WIN
        QStringList cacCot = dong.trimmed().split('|');

        if (cacCot.size() != 3) {
            continue;
        }

        bool dungSo = false;
        dungLuong = cacCot.at(2).trimmed()
            .toLongLong(&dungSo);

        if (!dungSo) {
            continue;
        }

        ma = cacCot.at(1).trimmed()
            + "_"
            + cacCot.at(0).trimmed();
#else
        QRegularExpressionMatch khop =
            mauMac.match(dong);

        if (!khop.hasMatch()) {
            continue;
        }

        bool dungSo = false;

        dungLuong = khop.captured(2)
            .toLongLong(&dungSo);

        if (!dungSo) {
            continue;
        }

        QString ten = QFileInfo(
            khop.captured(3).trimmed()
        ).fileName();

        ma = ten.left(28) + "_" + khop.captured(1);
#endif

        if (ma.isEmpty() ||
            dungLuong <= 0 ||
            dungLuong > std::numeric_limits<int>::max()) {
            continue;
        }

        danhSach.push_back({
            ma,
            dungLuong
        });
    }

    std::sort(
        danhSach.begin(),
        danhSach.end(),
        [](const TienTrinhHeThong& a,
           const TienTrinhHeThong& b) {
            return a.dungLuongKB > b.dungLuongKB;
        }
    );

    // Lay 5 tien trinh su dung nhieu RAM nhat.
    if (danhSach.size() > 5) {
        danhSach.resize(5);
    }

    if (danhSach.isEmpty()) {
        loi = "Không tìm thấy tiến trình có số liệu RAM.";
        return false;
    }

    return true;
}

#endif
