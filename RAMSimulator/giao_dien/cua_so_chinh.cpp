#include "mo_hinh.hpp"
#include "bo_nho.hpp"
#include "so_sanh_lich_su.hpp"
#include "thuat_toan_cap_phat.hpp"
#include "du_lieu_he_thong.hpp"
#include <QDateTime>

#include <QApplication>
#include <QFrame>
#include <QTimer>
#include <QSlider>
#include <QSizePolicy>
#include <QProgressBar>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QPolygonF>
#include <QScrollArea>
#include <QAbstractItemView>
#include <QBrush>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QInputDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include <QLabel>
#include <QMessageBox>
#include <QPen>
#include <QPushButton>
#include <QSet>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

// Icon duoc ve bang Qt: khong can tai tep anh, font icon hay them thu vien.
// Chi phuc vu hien thi; khong thay doi logic cap phat RAM.
static QIcon taoBieuTuong(const QString& loai, const QColor& mau) {
    QPixmap anh(48, 48);
    anh.fill(Qt::transparent);
    QPainter ve(&anh);
    ve.setRenderHint(QPainter::Antialiasing, true);
    ve.scale(2.0, 2.0);
    QPen net(mau, 1.75, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    ve.setPen(net);
    ve.setBrush(Qt::NoBrush);

    if (loai == "chip") {
        ve.drawRoundedRect(QRectF(5.5, 5.5, 13, 13), 2, 2);
        ve.drawRoundedRect(QRectF(9, 9, 6, 6), 1, 1);
        for (int i : {8, 12, 16}) {
            ve.drawLine(i, 2.5, i, 5.5);
            ve.drawLine(i, 18.5, i, 21.5);
            ve.drawLine(2.5, i, 5.5, i);
            ve.drawLine(18.5, i, 21.5, i);
        }
    } else if (loai == "home") {
        ve.drawLine(3.5, 11, 12, 4);
        ve.drawLine(12, 4, 20.5, 11);
        ve.drawLine(6.5, 10, 6.5, 20);
        ve.drawLine(17.5, 10, 17.5, 20);
        ve.drawLine(6.5, 20, 17.5, 20);
        ve.drawRect(QRectF(10, 13.5, 4, 6.5));
    } else if (loai == "chart") {
        ve.drawLine(3, 20, 21, 20);
        ve.drawRoundedRect(QRectF(5, 12, 3.5, 8), 0.7, 0.7);
        ve.drawRoundedRect(QRectF(10.5, 6, 3.5, 14), 0.7, 0.7);
        ve.drawRoundedRect(QRectF(16, 9, 3.5, 11), 0.7, 0.7);
    } else if (loai == "list") {
        for (int y : {6, 12, 18}) {
            ve.drawRoundedRect(QRectF(3, y - 1, 3, 3), 0.7, 0.7);
            ve.drawLine(QPointF(10, y + 0.5), QPointF(21, y + 0.5));
        }
    } else if (loai == "history") {
        ve.drawEllipse(QRectF(4, 4, 16, 16));
        ve.drawLine(12, 7, 12, 12);
        ve.drawLine(12, 12, 16, 14);
    } else if (loai == "info") {
        ve.drawEllipse(QRectF(4, 4, 16, 16));
        ve.setBrush(mau);
        ve.drawEllipse(QRectF(11.1, 7.3, 1.8, 1.8));
        ve.setBrush(Qt::NoBrush);
        ve.drawLine(12, 11, 12, 17);
    } else if (loai == "database") {
        ve.drawEllipse(QRectF(4, 4.5, 16, 5));
        ve.drawLine(4, 7, 4, 17);
        ve.drawLine(20, 7, 20, 17);
        ve.drawArc(QRectF(4, 10, 16, 5), 180 * 16, 180 * 16);
        ve.drawArc(QRectF(4, 14.5, 16, 5), 180 * 16, 180 * 16);
    } else if (loai == "play") {
        ve.setPen(Qt::NoPen);
        ve.setBrush(mau);
        ve.drawPolygon(QPolygonF{QPointF(7, 4.5), QPointF(19, 12), QPointF(7, 19.5)});
    } else if (loai == "step") {
        ve.setPen(Qt::NoPen);
        ve.setBrush(mau);
        ve.drawPolygon(QPolygonF{QPointF(4, 5), QPointF(16, 12), QPointF(4, 19)});
        ve.setPen(net);
        ve.drawLine(19, 5, 19, 19);
    } else if (loai == "pause") {
        ve.setPen(Qt::NoPen);
        ve.setBrush(mau);
        ve.drawRoundedRect(QRectF(6, 5, 4, 14), 1, 1);
        ve.drawRoundedRect(QRectF(14, 5, 4, 14), 1, 1);
    } else if (loai == "refresh") {
        ve.drawArc(QRectF(4.5, 4.5, 15, 15), 45 * 16, 280 * 16);
        ve.drawLine(18.5, 4, 19, 9);
        ve.drawLine(19, 9, 14, 8.5);
    } else if (loai == "check") {
        ve.drawEllipse(QRectF(3.5, 3.5, 17, 17));
        ve.drawLine(7.5, 12, 10.5, 15);
        ve.drawLine(10.5, 15, 16.5, 9);
    } else if (loai == "plus") {
        ve.drawRoundedRect(QRectF(3.5, 3.5, 17, 17), 3, 3);
        ve.drawLine(12, 7.5, 12, 16.5);
        ve.drawLine(7.5, 12, 16.5, 12);
    } else if (loai == "minus") {
        ve.drawRoundedRect(QRectF(3.5, 3.5, 17, 17), 3, 3);
        ve.drawLine(7.5, 12, 16.5, 12);
    } else if (loai == "memory") {
        ve.drawRoundedRect(QRectF(3, 5, 18, 14), 2, 2);
        ve.drawLine(6.5, 9, 17.5, 9);
        ve.drawLine(6.5, 13, 17.5, 13);
        ve.drawLine(8, 19, 8, 21);
        ve.drawLine(16, 19, 16, 21);
    } else if (loai == "exit") {
        ve.drawRoundedRect(QRectF(4, 4, 12, 16), 1, 1);
        ve.drawLine(10, 12, 21, 12);
        ve.drawLine(17, 8, 21, 12);
        ve.drawLine(17, 16, 21, 12);
    }
    ve.end();
    return QIcon(anh);
}

static void ganBieuTuong(QPushButton* nut, const QString& loai,
                        const QColor& mau, int kichThuoc = 17) {
    nut->setIcon(taoBieuTuong(loai, mau));
    nut->setIconSize(QSize(kichThuoc, kichThuoc));
}

// Vong tron RAM chi dung de HIEN THI, khong tham gia tinh toan/cap phat.
class VongTronRam : public QWidget {
public:
    explicit VongTronRam(QWidget* cha = nullptr) : QWidget(cha) {
        setMinimumSize(108, 108);
        setMaximumSize(124, 124);
        setToolTip("RAM khả dụng ước tính tại thời điểm đọc từ hệ điều hành.");
    }

    void capNhat(qint64 tongMB, qint64 khaDungMB) {
        tong = std::max<qint64>(0, tongMB);
        khaDung = std::clamp<qint64>(khaDungMB, 0, tong);
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter ve(this);
        ve.setRenderHint(QPainter::Antialiasing, true);
        const int canh = std::min(width(), height());
        QRectF hinh((width()-canh)/2.0 + 13, (height()-canh)/2.0 + 13,
                    canh-26.0, canh-26.0);
        QPen vien(QColor("#e0ebf8"), 13, Qt::SolidLine, Qt::RoundCap);
        ve.setPen(vien);
        ve.drawArc(hinh, 0, 360*16);
        if (tong > 0) {
            double tiLeKhaDung = static_cast<double>(khaDung) / tong;
            vien.setColor(QColor("#1264e7"));
            ve.setPen(vien);
            ve.drawArc(hinh, 90*16, static_cast<int>(-360*16*tiLeKhaDung));
        }
        ve.setPen(QColor("#103765"));
        QFont phong = font();
        phong.setBold(true);
        phong.setPointSize(16);
        ve.setFont(phong);
        ve.drawText(rect().adjusted(0,-10,0,0), Qt::AlignCenter,
            tong > 0 ? QString::number(100.0*khaDung/tong, 'f', 1) + "%" : "--");
        phong.setBold(false);
        phong.setPointSize(9);
        ve.setFont(phong);
        ve.setPen(QColor("#526b85"));
        ve.drawText(rect().adjusted(0,40,0,0), Qt::AlignHCenter|Qt::AlignVCenter,
                    "Khả dụng");
    }
private:
    qint64 tong = 0;
    qint64 khaDung = 0;
};

// Du lieu lay tu hai bang tren giao dien.
struct DuLieuMoPhong {
    TrangThaiBoNho boNho;
    std::vector<YeuCau> tienTrinh;
    QStringList tenVung;
};

// Luu thong tin cac tien trinh da cap phat.
struct PhanBoDaThucHien {
    int maVung;
    QString tenTienTrinh;
    int diaChiBatDauKB;
    int dungLuongKB;
};

// Tao bang du lieu.
QTableWidget* taoBang(const QStringList& tieuDe) {
    QTableWidget* bang = new QTableWidget();

    bang->setColumnCount(tieuDe.size());
    bang->setHorizontalHeaderLabels(tieuDe);

    bang->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    bang->verticalHeader()->setVisible(false);

    bang->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    bang->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    bang->setLayoutDirection(Qt::LeftToRight);

    return bang;
}

// Lay noi dung mot o trong bang.
QString layChu(QTableWidget* bang, int dong, int cot) {
    QTableWidgetItem* o = bang->item(dong, cot);

    if (o == nullptr) {
        return QString();
    }

    return o->text().trimmed();
}

// Them mot dong moi vao bang.
void themDong(QTableWidget* bang) {
    int dongMoi = bang->rowCount();

    bang->insertRow(dongMoi);

    for (int cot = 0; cot < bang->columnCount(); cot++) {
        bang->setItem(
            dongMoi,
            cot,
            new QTableWidgetItem()
        );
    }

    bang->setCurrentCell(dongMoi, 0);
    bang->editItem(bang->item(dongMoi, 0));
}

// Xoa dong dang duoc chon.
void xoaDong(QTableWidget* bang, QWidget* cuaSo) {
    int dong = bang->currentRow();

    if (dong < 0) {
        QMessageBox::information(
            cuaSo,
            "Thông báo",
            "Hãy chọn dòng cần xóa."
        );
        return;
    }

    bang->removeRow(dong);
}

// Hien thi thong bao loi du lieu.
bool baoLoi(
    QWidget* cuaSo,
    QTableWidget* bang,
    int dong,
    int cot,
    const QString& noiDung
) {
    QMessageBox::warning(
        cuaSo,
        "Dữ liệu không hợp lệ",
        noiDung
    );

    bang->setCurrentCell(dong, cot);
    return false;
}

// Doc va kiem tra toan bo du lieu tu giao dien.
bool docVaKiemTraDuLieu(
    QWidget* cuaSo,
    QTableWidget* bangRam,
    QTableWidget* bangTienTrinh,
    DuLieuMoPhong& duLieu
) {
    DuLieuMoPhong banMoi;

    // Phai co RAM va tien trinh.
    if (
        bangRam->rowCount() == 0 ||
        bangTienTrinh->rowCount() == 0
    ) {
        QMessageBox::warning(
            cuaSo,
            "Dữ liệu không hợp lệ",
            "Cần ít nhất một vùng RAM và một tiến trình."
        );
        return false;
    }

    // Kiem tra danh sach vung RAM.
    QSet<QString> cacMaRam;

    for (int dong = 0; dong < bangRam->rowCount(); dong++) {
        QString tenVung = layChu(bangRam, dong, 0);

        // Ma vung RAM khong duoc rong.
        if (tenVung.isEmpty()) {
            return baoLoi(
                cuaSo,
                bangRam,
                dong,
                0,
                QString("Vùng RAM dòng %1: mã không được để trống.")
                    .arg(dong + 1)
            );
        }

        // Ma vung RAM khong duoc trung.
        if (cacMaRam.contains(tenVung.toCaseFolded())) {
            return baoLoi(
                cuaSo,
                bangRam,
                dong,
                0,
                QString("Mã vùng RAM '%1' bị trùng.")
                    .arg(tenVung)
            );
        }

        cacMaRam.insert(tenVung.toCaseFolded());

        bool dungDiaChi = false;
        bool dungDungLuong = false;

        int diaChi = layChu(bangRam, dong, 1)
            .toInt(&dungDiaChi);

        int dungLuong = layChu(bangRam, dong, 2)
            .toInt(&dungDungLuong);

        // Dia chi bat dau phai khong am.
        if (!dungDiaChi || diaChi < 0) {
            return baoLoi(
                cuaSo,
                bangRam,
                dong,
                1,
                QString(
                    "Vùng RAM dòng %1: "
                    "địa chỉ phải là số nguyên không âm."
                ).arg(dong + 1)
            );
        }

        // Dung luong RAM phai lon hon 0.
        if (!dungDungLuong || dungLuong <= 0) {
            return baoLoi(
                cuaSo,
                bangRam,
                dong,
                2,
                QString(
                    "Vùng RAM dòng %1: "
                    "dung lượng phải là số nguyên dương."
                ).arg(dong + 1)
            );
        }

        // Chan vuot gioi han so nguyen.
        if (
            static_cast<long long>(diaChi) + dungLuong >
            std::numeric_limits<int>::max()
        ) {
            return baoLoi(
                cuaSo,
                bangRam,
                dong,
                2,
                QString(
                    "Vùng RAM dòng %1: "
                    "địa chỉ cuối vượt giới hạn số nguyên."
                ).arg(dong + 1)
            );
        }

        // Luu vung RAM vao du lieu mo phong.
        banMoi.boNho.push_back({
            dong + 1,
            diaChi,
            dungLuong
        });

        banMoi.tenVung.append(tenVung);
    }

    // Kiem tra hai vung RAM co chong lan hay khong.
    for (
        int dong1 = 0;
        dong1 < static_cast<int>(banMoi.boNho.size());
        dong1++
    ) {
        const VungTrong& vung1 = banMoi.boNho[dong1];

        long long cuoi1 =
            static_cast<long long>(vung1.diaChiBatDauKB) +
            vung1.dungLuongTrongKB;

        for (
            int dong2 = dong1 + 1;
            dong2 < static_cast<int>(banMoi.boNho.size());
            dong2++
        ) {
            const VungTrong& vung2 = banMoi.boNho[dong2];

            long long cuoi2 =
                static_cast<long long>(vung2.diaChiBatDauKB) +
                vung2.dungLuongTrongKB;

            if (
                vung1.diaChiBatDauKB < cuoi2 &&
                vung2.diaChiBatDauKB < cuoi1
            ) {
                return baoLoi(
                    cuaSo,
                    bangRam,
                    dong2,
                    1,
                    QString(
                        "Vùng RAM dòng %1 và dòng %2 "
                        "bị chồng lấn địa chỉ."
                    )
                        .arg(dong1 + 1)
                        .arg(dong2 + 1)
                );
            }
        }
    }

    // Sap xep cac vung RAM theo dia chi tang dan.
    std::stable_sort(
        banMoi.boNho.begin(),
        banMoi.boNho.end(),
        [](const VungTrong& trai, const VungTrong& phai) {
            return trai.diaChiBatDauKB <
                   phai.diaChiBatDauKB;
        }
    );

    // Kiem tra danh sach tien trinh.
    QSet<QString> cacMaTienTrinh;

    for (
        int dong = 0;
        dong < bangTienTrinh->rowCount();
        dong++
    ) {
        QString tenTienTrinh =
            layChu(bangTienTrinh, dong, 0);

        if (tenTienTrinh.isEmpty()) {
            return baoLoi(
                cuaSo,
                bangTienTrinh,
                dong,
                0,
                QString(
                    "Tiến trình dòng %1: "
                    "mã không được để trống."
                ).arg(dong + 1)
            );
        }

        if (
            cacMaTienTrinh.contains(
                tenTienTrinh.toCaseFolded()
            )
        ) {
            return baoLoi(
                cuaSo,
                bangTienTrinh,
                dong,
                0,
                QString("Tiến trình: mã '%1' bị trùng.")
                    .arg(tenTienTrinh)
            );
        }

        cacMaTienTrinh.insert(
            tenTienTrinh.toCaseFolded()
        );

        bool hopLe = false;

        int dungLuong = layChu(bangTienTrinh, dong, 1)
            .toInt(&hopLe);

        if (!hopLe || dungLuong <= 0) {
            return baoLoi(
                cuaSo,
                bangTienTrinh,
                dong,
                1,
                QString(
                    "Tiến trình dòng %1: "
                    "dung lượng phải là số nguyên dương."
                ).arg(dong + 1)
            );
        }

        banMoi.tienTrinh.push_back({
            tenTienTrinh.toStdString(),
            dungLuong
        });
    }

    duLieu = std::move(banMoi);
    return true;
}

// Ve so do cac vung RAM va tien trinh da cap phat.

// Chuyen thong bao tu loi C++ sang tieng Viet co dau tren giao dien.
static QString hienThiLyDoTiengViet(const std::string& lyDo)
{
    QString thongBao = QString::fromStdString(lyDo);

    thongBao.replace(
        "Khong du tong dung luong RAM trong.",
        "Không đủ tổng dung lượng RAM trống."
    );
    thongBao.replace(
        "Phan manh ngoai: khong co vung RAM lien tuc du lon.",
        "Phân mảnh ngoài: không có vùng RAM liên tục đủ lớn."
    );
    thongBao.replace(
        "Yeu cau cap phat khong hop le.",
        "Yêu cầu cấp phát không hợp lệ."
    );
    thongBao.replace(
        "Vung RAM khong ton tai.",
        "Vùng RAM không tồn tại."
    );
    thongBao.replace(
        "Vung RAM khong du dung luong.",
        "Vùng RAM không đủ dung lượng."
    );
    thongBao.replace(
        "Tien trinh da duoc cap phat.",
        "Tiến trình đã được cấp phát."
    );
    thongBao.replace(
        "Tien trinh khong ton tai hoac da giai phong.",
        "Tiến trình không tồn tại hoặc đã giải phóng."
    );
    thongBao.replace(
        "Dia chi RAM khong hop le.",
        "Địa chỉ RAM không hợp lệ."
    );
    thongBao.replace(
        "Dia chi hoac dung luong RAM khong hop le.",
        "Địa chỉ hoặc dung lượng RAM không hợp lệ."
    );
    thongBao.replace(
        "Vung giai phong chong len RAM da trong.",
        "Vùng giải phóng chồng lên RAM đã trống."
    );
    thongBao.replace(
        "Dung luong sau khi gop vuot gioi han.",
        "Dung lượng sau khi gộp vượt giới hạn."
    );

    return thongBao;
}

void veSoDo(
    QGraphicsScene* canh,
    const DuLieuMoPhong& duLieu,
    const std::vector<PhanBoDaThucHien>& daCapPhat,
    const TrangThaiBoNho& ramConLai,
    int maVungDangXet = -1,
    int maVungDuocChon = -1,
    int maVungUngVien = -1
) {
    canh->clear();

    const qreal chieuDaiToiDa = 770.0;

    int dungLuongLonNhat = 1;

    for (const VungTrong& vung : duLieu.boNho) {
        dungLuongLonNhat = std::max(
            dungLuongLonNhat,
            vung.dungLuongTrongKB
        );
    }

    int dongHienThi = 0;

    for (const VungTrong& vung : duLieu.boNho) {
        int dongNguon = vung.ma - 1;

        QString tenVung =
            duLieu.tenVung.at(dongNguon);

        qreal y = 18.0 + 67.0 * dongHienThi;
        dongHienThi++;

        qreal x = 255.0;

        qreal tiLe =
            chieuDaiToiDa / dungLuongLonNhat;

        qreal chieuDai =
            vung.dungLuongTrongKB * tiLe;

        QString nhanVung =
            QString("%1\nĐịa chỉ logic: %2–%3 | %4 KB")
                .arg(tenVung)
                .arg(vung.diaChiBatDauKB)
                .arg(vung.diaChiBatDauKB
                     + vung.dungLuongTrongKB - 1)
                .arg(vung.dungLuongTrongKB);

        QGraphicsTextItem* nhan =
            canh->addText(nhanVung);

        nhan->setDefaultTextColor(
            QColor("#374151")
        );

        nhan->setPos(0, y);

        // Vung RAM trong ban dau.
        QGraphicsRectItem* hinhVungTrong = canh->addRect(
            x,
            y + 1,
            chieuDai,
            40,
            QPen(QColor("#64748b")),
            QBrush(QColor("#dbeafe"))
        );
        hinhVungTrong->setToolTip(
            QString("%1 | Địa chỉ logic: %2–%3 | Tổng %4 KB")
                .arg(tenVung)
                .arg(vung.diaChiBatDauKB)
                .arg(vung.diaChiBatDauKB + vung.dungLuongTrongKB - 1)
                .arg(vung.dungLuongTrongKB)
        );

        QStringList nhanOQuaNho;
        int daSuDungKB = 0;

        // Ve tung tien trinh da duoc cap phat.
        for (const PhanBoDaThucHien& phanBo : daCapPhat) {
            if (phanBo.maVung != vung.ma) {
                continue;
            }

            qreal viTriX =
                x + (phanBo.diaChiBatDauKB - vung.diaChiBatDauKB) * tiLe;

            qreal doDai =
                phanBo.dungLuongKB * tiLe;

            int diaChiDau =
                phanBo.diaChiBatDauKB;

            int diaChiCuoi =
                diaChiDau + phanBo.dungLuongKB - 1;

            QGraphicsRectItem* hinhTienTrinh =
                canh->addRect(
                    viTriX,
                    y + 1,
                    doDai,
                    40,
                    QPen(QColor("#15803d")),
                    QBrush(QColor("#22a06b"))
                );

            hinhTienTrinh->setToolTip(
                QString("%1 | Địa chỉ: %2–%3 | %4 KB")
                    .arg(phanBo.tenTienTrinh)
                    .arg(diaChiDau)
                    .arg(diaChiCuoi)
                    .arg(phanBo.dungLuongKB)
            );

            // NHAN_P_DAY_DU_V4
            QString maHienThi = phanBo.tenTienTrinh;

            for (int i = 0;
                 i < static_cast<int>(duLieu.tienTrinh.size());
                 ++i) {
                if (QString::fromStdString(
                        duLieu.tienTrinh[i].maTienTrinh)
                    == phanBo.tenTienTrinh) {
                    maHienThi = QString("P%1").arg(i + 1);
                    break;
                }
            }

            QFont phongChu("Arial");
            phongChu.setPixelSize(11);
            phongChu.setBold(true);

            QGraphicsSimpleTextItem* nhanTienTrinh =
                canh->addSimpleText(maHienThi, phongChu);

            nhanTienTrinh->setBrush(QBrush(QColor("#ffffff")));
            nhanTienTrinh->setToolTip(hinhTienTrinh->toolTip());

            qreal rong = nhanTienTrinh->boundingRect().width();
            qreal cao = nhanTienTrinh->boundingRect().height();

            if (doDai >= rong + 4) {
                nhanTienTrinh->setPos(
                    viTriX + (doDai - rong) / 2,
                    y + 1 + (40 - cao) / 2
                );
            } else {
                canh->removeItem(nhanTienTrinh);
                delete nhanTienTrinh;
                nhanOQuaNho.append(maHienThi);
            }

            daSuDungKB += phanBo.dungLuongKB;
        }

        if (!nhanOQuaNho.isEmpty()) {
            QGraphicsSimpleTextItem* ghiChu = canh->addSimpleText(
                "Đoạn hẹp: " + nhanOQuaNho.join(", ")
            );
            ghiChu->setBrush(QBrush(QColor("#24466b")));
            ghiChu->setPos(x, y + 44);
        }


        // TICH_HOP_GIAI_PHONG_V1
        // Doc cac khoang trong thuc te cua bo nho mo phong.
        int conLai = 0;
        QStringList cacKhoangTrong;

        for (const VungTrong& khoang : ramConLai) {
            const long long batDau = std::max<long long>(
                khoang.diaChiBatDauKB, vung.diaChiBatDauKB
            );

            const long long ketThuc = std::min<long long>(
                static_cast<long long>(khoang.diaChiBatDauKB)
                    + khoang.dungLuongTrongKB,
                static_cast<long long>(vung.diaChiBatDauKB)
                    + vung.dungLuongTrongKB
            );

            if (ketThuc > batDau) {
                conLai += static_cast<int>(ketThuc - batDau);
                cacKhoangTrong << QString("%1–%2")
                    .arg(batDau).arg(ketThuc - 1);
            }
        }

        QString thongTinConLai;

        if (cacKhoangTrong.isEmpty()) {
            thongTinConLai = "Còn 0 KB";
        } else if (cacKhoangTrong.size() == 1) {
            thongTinConLai = QString("Còn %1 KB")
                .arg(conLai);
        } else {
            thongTinConLai = QString("Còn %1 KB (%2 khoảng trống)")
                .arg(conLai).arg(cacKhoangTrong.size());
        }

        QGraphicsTextItem* nhanConLai =
            canh->addText(thongTinConLai);

        nhanConLai->setDefaultTextColor(
            QColor("#374151")
        );
        nhanConLai->setToolTip(
            "Các khoảng RAM trống: " + cacKhoangTrong.join(", ")
        );

        nhanConLai->setPos(
            x + chieuDai + 8,
            y + 10
        );

        // Highlight duoc ve SAU cac o da cap phat de khong bi che.
        // Cam: dang kiem tra, xanh duong: ung vien, xanh la: da chon.
        QColor mauVien;
        QString giaiThich;
        if (vung.ma == maVungDangXet) {
            mauVien = QColor("#f59e0b");
            giaiThich = "ĐANG KIỂM TRA";
        } else if (vung.ma == maVungDuocChon) {
            mauVien = QColor("#16a34a");
            giaiThich = "VÙNG ĐƯỢC CHỌN";
        } else if (vung.ma == maVungUngVien) {
            mauVien = QColor("#2563eb");
            giaiThich = "ỨNG VIÊN TẠM THỜI";
        }
        if (!giaiThich.isEmpty()) {
            QPen vien(mauVien);
            vien.setWidthF(3.0);
            QGraphicsRectItem* vienNoiBat = canh->addRect(
                x - 3, y - 2, chieuDai + 6, 46,
                vien, QBrush(Qt::NoBrush)
            );
            // Vien chi phuc vu hieu ung nhan manh. Khong che tooltip
            // ten tien trinh, dia chi va dung luong cua cac khoi da cap phat.
            vienNoiBat->setZValue(-1);
            vienNoiBat->setAcceptedMouseButtons(Qt::NoButton);
        }
    }

    canh->setSceneRect(
        canh->itemsBoundingRect().adjusted(
            -8, -8, 10, 12
        )
    );
}

// Ham chinh cua ung dung Qt.
int main(int soThamSo, char* danhSachThamSo[]) {
    QApplication ungDung(
        soThamSo,
        danhSachThamSo
    );

    QWidget cuaSo;
    cuaSo.setWindowTitle(
        "RAMSimulator – Dashboard hai khung"
    );
    cuaSo.resize(1510, 830);

    // GIAO DIEN TIENG VIET HOAN THIEN
    cuaSo.setObjectName("cuaSo");

    cuaSo.setStyleSheet(R"CSS(
        QWidget { font-family: "Segoe UI", Arial; font-size: 12px; color: #142f52; }
        QWidget#cuaSo, QWidget#noiDung { background-color: #f4f7fc; }
        QFrame#thanhDauTrang { background: #ffffff; border: 1px solid #dce7f5;
            border-radius: 13px; }
        QFrame#thanhTrangThai { background: #f8fbff; border-top: 1px solid #e5edf6; }
        QGroupBox { background-color: #ffffff; border: 1px solid #dae6f6;
            border-radius: 12px; margin-top: 13px; padding: 5px; font-weight: 600; }
        QGroupBox::title { subcontrol-origin: margin; left: 14px;
            padding: 0 5px; color: #153b6c; font-size: 12px; font-weight: bold; }
        QGroupBox#khungDieuKhien, QGroupBox#khungSoDo {
            margin-top: 0px;
        }
        QGroupBox#khungKetQua, QGroupBox#khungSoSanh {
            margin-top: 12px; padding: 5px; }
        QGroupBox#khungKetQua::title, QGroupBox#khungSoSanh::title {
            left: 10px; padding: 0 3px; }
        QFrame#theThongKe { background: #f8fbff; border: 1px solid #e3edf8;
            border-radius: 10px; }
        QTableWidget { background: #ffffff; alternate-background-color: #f4f8fe;
            gridline-color: #e9eff8; border: 1px solid #dde9f7;
            selection-background-color: #d9ebff; selection-color: #103964; }
        QTableWidget::item { padding: 2px 4px; }
        QHeaderView::section { background: #eaf2fd; color: #1a4576;
            padding: 5px 3px; font-weight: bold; border: 1px solid #dbe7f5; }
        QPushButton { background: #f0f6ff; border: 1px solid #d1e1f3;
            border-radius: 9px; color: #23466b; padding: 5px 9px; min-height: 25px; }
        QPushButton:hover { background: #e1edfd; border-color: #adccef; }
        QPushButton:pressed { background: #cee3fb; }
        QPushButton:disabled { background: #eef1f5; border-color: #e3e8ef;
            color: #8493a5; }
        QPushButton#nutBatDau, QPushButton#nutLayDuLieuThuc {
            background: #1168db; border: 1px solid #1168db;
            color: white; font-weight: bold; }
        QPushButton#nutBatDau:hover, QPushButton#nutLayDuLieuThuc:hover {
            background: #0956bf; border-color: #0956bf; }
        QPushButton#nutSoSanh, QPushButton#nutSoSanhLichSu {
            background: #e7f0ff; border-color: #c2d6f3; color: #1452ab;
            font-weight: bold; }
        QPushButton#nutDiToiMoPhong, QPushButton#nutDiToiSoDo,
        QPushButton#nutDiToiKetQua, QPushButton#nutThongTin {
            background: #f4f8fe; border: 1px solid #e2ebf6; font-weight: bold;
            color: #23416b; }
        QPushButton#nutDiToiMoPhong { background: #1168db;
            border-color: #1168db; color: white; }
        QPushButton#nutGiaiPhong, QPushButton#nutYeuCauMoi {
            background: #e6f7ef; border-color: #bde5d3; color: #0b7456; }
        QComboBox { background: white; border: 1px solid #c9daee;
            border-radius: 7px; padding: 6px; }
        QGraphicsView { background: #ffffff; border: 1px solid #e0e9f6; border-radius: 8px; }
        QProgressBar { background: #e9f1fd; border: 1px solid #cfddf1;
            border-radius: 6px; text-align: center; min-height: 20px; }
        QProgressBar::chunk { background: #20ad81; border-radius: 5px; }
        QPushButton#nutThuGonDuLieu { background: #f3f8ff; border-color: #d5e6f9;
            color: #275484; font-weight: 600; }
        QToolTip { color: #173a62; background-color: #fbfdff;
            border: 1px solid #cbdcf3; padding: 5px; }
        QSlider::groove:horizontal { background: #e1eaf6; height: 5px; border-radius: 2px; }
        QSlider::handle:horizontal { background: #1671df; width: 14px;
            margin: -5px 0; border-radius: 7px; border: 2px solid white; }
    )CSS");

    // Thanh dau trang co dinh: chi cuon/cho xem thong tin, khong sua nghiep vu.
    QVBoxLayout* boCucNgoai = new QVBoxLayout(&cuaSo);
    boCucNgoai->setContentsMargins(12, 6, 12, 6);
    boCucNgoai->setSpacing(4);

    QFrame* thanhDauTrang = new QFrame(&cuaSo);
    thanhDauTrang->setObjectName("thanhDauTrang");
    QHBoxLayout* hangTieuDe = new QHBoxLayout(thanhDauTrang);
    hangTieuDe->setContentsMargins(13, 6, 11, 6);
    hangTieuDe->setSpacing(9);

    QLabel* bieuTuong = new QLabel();
    bieuTuong->setObjectName("bieuTuongUngDung");
    bieuTuong->setFixedSize(40, 40);
    bieuTuong->setAlignment(Qt::AlignCenter);
    bieuTuong->setPixmap(taoBieuTuong("chip", QColor("#1264e7")).pixmap(29, 29));
    bieuTuong->setStyleSheet("background: #eaf3ff; border: 1px solid #d8e9ff; "
                            "border-radius: 10px;");
    hangTieuDe->addWidget(bieuTuong);

    QVBoxLayout* boCucNhan = new QVBoxLayout();
    boCucNhan->setSpacing(0);
    QLabel* tieuDe = new QLabel("RAMSimulator");
    tieuDe->setStyleSheet("font-size: 21px; font-weight: bold; color: #102d60;");
    QLabel* gioiThieu = new QLabel("Chương 9 – Main Memory");
    gioiThieu->setStyleSheet("font-size: 11px; color: #536d8b;");
    boCucNhan->addWidget(tieuDe);
    boCucNhan->addWidget(gioiThieu);
    hangTieuDe->addLayout(boCucNhan, 1);

    QPushButton* nutDiToiMoPhong = new QPushButton("Mô phỏng");
    QPushButton* nutDiToiSoDo = new QPushButton("So sánh thuật toán");
    QPushButton* nutDiToiKetQua = new QPushButton("Kết quả cấp phát");
    QPushButton* nutThongTin = new QPushButton("Thông tin");
    nutDiToiMoPhong->setObjectName("nutDiToiMoPhong");
    nutDiToiSoDo->setObjectName("nutDiToiSoDo");
    nutDiToiKetQua->setObjectName("nutDiToiKetQua");
    nutThongTin->setObjectName("nutThongTin");
    for (QPushButton* nut : {nutDiToiMoPhong, nutDiToiSoDo,
                             nutDiToiKetQua, nutThongTin}) {
        nut->setMinimumHeight(30);
        hangTieuDe->addWidget(nut);
    }
    ganBieuTuong(nutDiToiMoPhong, "home", QColor("#ffffff"), 17);
    ganBieuTuong(nutDiToiSoDo, "chart", QColor("#2b5484"), 17);
    ganBieuTuong(nutDiToiKetQua, "list", QColor("#2b5484"), 17);
    ganBieuTuong(nutThongTin, "info", QColor("#2b5484"), 17);
    boCucNgoai->addWidget(thanhDauTrang);

    QScrollArea* vungCuon = new QScrollArea(&cuaSo);
    vungCuon->setWidgetResizable(true);
    vungCuon->setFrameShape(QFrame::NoFrame);
    QWidget* noiDung = new QWidget();
    noiDung->setObjectName("noiDung");
    QVBoxLayout* boCuc = new QVBoxLayout(noiDung);
    boCuc->setContentsMargins(2, 1, 2, 1);
    boCuc->setSpacing(3);
    vungCuon->setWidget(noiDung);
    boCucNgoai->addWidget(vungCuon, 1);

    // DASHBOARD RAM V3

    QLabel* nhanGiamSat = new QLabel("Giám sát RAM và tiến trình");

    nhanGiamSat->setStyleSheet(
        "font-size: 15px; "
        "font-weight: bold; "
        "color: #204b75; "
        "border-left: 3px solid #1a71e2; padding-left: 9px; "
        "padding-top: 5px; padding-bottom: 3px;"
    );

    // Keep the navigation anchor parented; titles on the cards are sufficient.
    boCuc->addWidget(nhanGiamSat);
    nhanGiamSat->hide();

    // Giám sát + tiến trình trên cùng một hàng, tương tự giao diện mẫu.
    QHBoxLayout* hangGiamSat = new QHBoxLayout();
    hangGiamSat->setSpacing(7);
    QGroupBox* khungThongTin = new QGroupBox("Thông tin RAM hệ thống");
    QVBoxLayout* boCucThongTin = new QVBoxLayout(khungThongTin);
    boCucThongTin->setContentsMargins(10, 7, 10, 8);
    boCucThongTin->setSpacing(4);
    VongTronRam* bieuDoRam = new VongTronRam(khungThongTin);

    // Cac chi so duoc cap nhat tu he dieu hanh.
    QLabel* giaTriTongRam = nullptr;
    QLabel* giaTriRamKhaDung = nullptr;
    QLabel* giaTriTienTrinh = nullptr;
    QLabel* giaTriCapNhat = nullptr;

    auto taoTheThongKe = [&](
        const QString& ten,
        QLabel*& giaTri
    ) -> QFrame* {

        QFrame* the = new QFrame(noiDung);
        the->setObjectName("theThongKe");

        the->setStyleSheet(
            "QFrame#theThongKe { "
            "background: white; "
            "border: 1px solid #cfdeef; "
            "border-radius: 10px; "
            "}"
        );

        the->setMinimumHeight(51);

        QVBoxLayout* boCucThe =
            new QVBoxLayout(the);

        boCucThe->setContentsMargins(
            9, 4, 9, 4
        );
        boCucThe->setSpacing(1);

        QLabel* nhan = new QLabel(ten);
        nhan->setStyleSheet(
            "font-size: 11px; "
            "color: #526780; "
            "border: none;"
        );

        giaTri = new QLabel("—");
        giaTri->setStyleSheet(
            "font-size: 14px; "
            "font-weight: bold; "
            "color: #123b66; "
            "border: none;"
        );

        boCucThe->addWidget(nhan);
        boCucThe->addWidget(giaTri);

        return the;
    };

    QGridLayout* hangThongKe = new QGridLayout();
    hangThongKe->setSpacing(5);

    hangThongKe->addWidget(
        taoTheThongKe("TỔNG RAM", giaTriTongRam), 0, 0);

    hangThongKe->addWidget(
        taoTheThongKe("RAM KHẢ DỤNG (ƯỚC TÍNH)", giaTriRamKhaDung), 0, 1);

    hangThongKe->addWidget(
        taoTheThongKe("TIẾN TRÌNH", giaTriTienTrinh), 1, 0);

    hangThongKe->addWidget(
        taoTheThongKe("CẬP NHẬT", giaTriCapNhat), 1, 1);

    QHBoxLayout* thongKeVaVong = new QHBoxLayout();
    thongKeVaVong->setSpacing(7);
    thongKeVaVong->addLayout(hangThongKe, 4);
    thongKeVaVong->addWidget(bieuDoRam, 1);
    boCucThongTin->addLayout(thongKeVaVong);

    // Cac chi so va nut doc he dieu hanh nam chung mot hang, tiet kiem chieu cao.
    QPushButton* nutLayDuLieuThuc =
        new QPushButton("Lấy dữ liệu hệ thống");
    nutLayDuLieuThuc->setObjectName("nutLayDuLieuThuc");
    ganBieuTuong(nutLayDuLieuThuc, "database", QColor("#ffffff"), 18);
    nutLayDuLieuThuc->setMinimumHeight(30);
    nutLayDuLieuThuc->setMinimumWidth(190);
    nutLayDuLieuThuc->setMaximumWidth(270);
    nutLayDuLieuThuc->setToolTip("Đọc RAM và danh sách tiến trình từ hệ điều hành.");
    QHBoxLayout* hangNguonHeThong = new QHBoxLayout();
    hangNguonHeThong->addWidget(nutLayDuLieuThuc, 3);
    boCucThongTin->addLayout(hangNguonHeThong);

    // ==========================
    // BANG DU LIEU RAM
    // ==========================

    // Chi an/hien KHU VUC BANG; doi tuong QTableWidget va du lieu duoc giu nguyen.
    QWidget* khungDuLieuDauVao = new QWidget(noiDung);
    QHBoxLayout* boCucHaiBang = new QHBoxLayout(khungDuLieuDauVao);
    boCucHaiBang->setContentsMargins(0, 0, 0, 0);
    boCucHaiBang->setSpacing(7);

    QGroupBox* khungRam =
        new QGroupBox("Danh sách vùng RAM trống");

    QVBoxLayout* boCucRam =
        new QVBoxLayout(khungRam);

    QTableWidget* bangRam = taoBang({
        "Mã vùng",
        "Địa chỉ bắt đầu (KB)",
        "Dung lượng (KB)"
    });

    bangRam->setFixedHeight(132);
    bangRam->setAlternatingRowColors(true);
    bangRam->verticalHeader()->setDefaultSectionSize(30);
    boCucRam->addWidget(bangRam);

    QHBoxLayout* hangNutRam =
        new QHBoxLayout();

    QPushButton* nutThemRam =
        new QPushButton("Thêm vùng RAM");

    QPushButton* nutXoaRam =
        new QPushButton("Xóa vùng RAM");

    ganBieuTuong(nutThemRam, "plus", QColor("#2367ba"));
    ganBieuTuong(nutXoaRam, "minus", QColor("#925f6d"));
    hangNutRam->addWidget(nutThemRam);
    hangNutRam->addWidget(nutXoaRam);

    boCucRam->addLayout(hangNutRam);

    // ==========================
    // BANG DU LIEU TIEN TRINH
    // ==========================

    QGroupBox* khungTienTrinh =
        new QGroupBox("Danh sách tiến trình");

    QVBoxLayout* boCucTienTrinh =
        new QVBoxLayout(khungTienTrinh);
    boCucTienTrinh->setContentsMargins(10, 7, 10, 8);

    QTableWidget* bangTienTrinh = taoBang({
        "Mã tiến trình",
        "Dung lượng (KB)"
    });

    bangTienTrinh->setFixedHeight(152);
    bangTienTrinh->setAlternatingRowColors(true);
    bangTienTrinh->verticalHeader()->setDefaultSectionSize(24);
    boCucTienTrinh->addWidget(bangTienTrinh);

    QHBoxLayout* hangNutTienTrinh =
        new QHBoxLayout();

    QPushButton* nutThemTienTrinh =
        new QPushButton("Thêm tiến trình");

    QPushButton* nutXoaTienTrinh =
        new QPushButton("Xóa tiến trình");

    ganBieuTuong(nutThemTienTrinh, "plus", QColor("#2367ba"));
    ganBieuTuong(nutXoaTienTrinh, "minus", QColor("#925f6d"));
    hangNutTienTrinh->addWidget(nutThemTienTrinh);
    hangNutTienTrinh->addWidget(nutXoaTienTrinh);

    boCucTienTrinh->addLayout(hangNutTienTrinh);

    // Dua hai bang vao cua so.
    khungRam->setTitle("Danh sách vùng RAM logic");
    khungTienTrinh->setTitle("Danh sách yêu cầu cấp phát");

    boCucHaiBang->addWidget(khungRam);
    hangGiamSat->addWidget(khungThongTin, 5);
    hangGiamSat->addWidget(khungTienTrinh, 6);
    // Cap chieu cao de tranh hai the du lieu phinh to khong can thiet.
    khungThongTin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    khungTienTrinh->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    khungThongTin->setMaximumHeight(240);
    khungTienTrinh->setMaximumHeight(240);
    boCuc->addLayout(hangGiamSat);

    QPushButton* nutThuGonDuLieu = new QPushButton("Nhập vùng RAM  ▾");
    nutThuGonDuLieu->setObjectName("nutThuGonDuLieu");
    ganBieuTuong(nutThuGonDuLieu, "memory", QColor("#2d608d"));
    nutThuGonDuLieu->setMinimumHeight(30);
    nutThuGonDuLieu->setCheckable(true);
    nutThuGonDuLieu->setChecked(false);
    khungDuLieuDauVao->hide();
    // Nut nhap RAM nam canh nut lay du lieu: khong chiem mot hang lon.
    hangNguonHeThong->addWidget(nutThuGonDuLieu, 2);
    boCuc->addWidget(khungDuLieuDauVao);
    QObject::connect(nutThuGonDuLieu, &QPushButton::toggled,
        &cuaSo, [=](bool moBang) {
            khungDuLieuDauVao->setVisible(moBang);
            nutThuGonDuLieu->setText(moBang
                ? "Ẩn vùng RAM  ▴"
                : "Nhập vùng RAM  ▾");
        });

    auto taoTieuDeSection = [](const QString& tieuDe,
                           const QString& loaiIcon) -> QWidget* {
    QFrame* khung = new QFrame();
    khung->setObjectName("tieuDeDashboard");

    QHBoxLayout* hang = new QHBoxLayout(khung);
    hang->setContentsMargins(12, 5, 12, 5);
    hang->setSpacing(9);

    QLabel* icon = new QLabel();
    icon->setPixmap(
        taoBieuTuong(loaiIcon, QColor("#1768d8")).pixmap(19, 19)
    );
    hang->addWidget(icon);

    QLabel* chu = new QLabel(tieuDe);
    chu->setObjectName("chuTieuDeDashboard");
    hang->addWidget(chu);

    QFrame* duongKe = new QFrame();
    duongKe->setFixedHeight(1);
    duongKe->setStyleSheet(
        "background: #d9e6f6; border: none;"
    );
    hang->addWidget(duongKe, 1);

    khung->setStyleSheet(
        "QFrame#tieuDeDashboard {"
        "background: #f3f8ff;"
        "border: 1px solid #d9e6f6;"
        "border-radius: 10px;"
        "}"
        "QLabel#chuTieuDeDashboard {"
        "background: transparent;"
        "border: none;"
        "color: #174775;"
        "font-size: 15px;"
        "font-weight: bold;"
        "}"
    );

    return khung;
};

boCuc->addWidget(
    taoTieuDeSection("Mô phỏng cấp phát RAM", "play")
);
    QGroupBox* khungDieuKhien = new QGroupBox();
    khungDieuKhien->setObjectName("khungDieuKhien");
    QVBoxLayout* boCucDieuKhien = new QVBoxLayout(khungDieuKhien);
    boCucDieuKhien->setSpacing(4);
    boCucDieuKhien->setContentsMargins(9, 5, 9, 6);
    boCuc->addWidget(khungDieuKhien);

    // ==========================
    // CAC NUT DIEU KHIEN
    // ==========================

    QHBoxLayout* hangDieuKhien =
        new QHBoxLayout();

    QComboBox* chonThuatToan =
        new QComboBox();

    chonThuatToan->addItems({
        "First Fit",
        "Best Fit",
        "Worst Fit"
    });

    // Nút lấy dữ liệu đã được tạo ở phần giám sát phía trên.

    QPushButton* nutKiemTra =
        new QPushButton("Kiểm tra dữ liệu");

    QPushButton* nutBatDau =
        new QPushButton("Bắt đầu mô phỏng");
    nutBatDau->setObjectName("nutBatDau");

    QPushButton* nutBuocTiepTheo =
        new QPushButton("Bước tiếp theo");

    QPushButton* nutChayHet =
        new QPushButton("Chạy tự động");

    QPushButton* nutDatLai =
        new QPushButton("Đặt lại");

    QPushButton* nutSoSanh =
        new QPushButton("So sánh 3 thuật toán");
    nutSoSanh->setObjectName("nutSoSanh");

    hangDieuKhien->addWidget(
        new QLabel("Thuật toán:")
    );

    hangDieuKhien->addWidget(chonThuatToan);
    hangDieuKhien->setSpacing(6);
    chonThuatToan->setMinimumWidth(142);
    nutBatDau->setMinimumHeight(33);

    for (QPushButton* nut : {
        nutKiemTra,
        nutBatDau,
        nutBuocTiepTheo,
        nutChayHet,
        nutDatLai
    }) {
        hangDieuKhien->addWidget(nut);
    }

    ganBieuTuong(nutKiemTra, "check", QColor("#32649b"));
    ganBieuTuong(nutBatDau, "play", QColor("#ffffff"));
    ganBieuTuong(nutBuocTiepTheo, "step", QColor("#3c6593"));
    ganBieuTuong(nutChayHet, "play", QColor("#3c6593"));
    ganBieuTuong(nutDatLai, "refresh", QColor("#3c6593"));
    boCucDieuKhien->addLayout(hangDieuKhien);

    // RAMSIMULATOR_V4: dieu khien trinh dien khong chan giao dien.
    QPushButton* nutTamDung = new QPushButton("Tạm dừng");
    nutTamDung->setMinimumWidth(116);
    QSlider* thanhTocDo = new QSlider(Qt::Horizontal);
    thanhTocDo->setRange(1, 5);
    thanhTocDo->setValue(3);
    thanhTocDo->setTickInterval(1);
    thanhTocDo->setTickPosition(QSlider::TicksBelow);
    thanhTocDo->setMinimumWidth(110);
    thanhTocDo->setMaximumWidth(180);
    QLabel* nhanTocDo = new QLabel("Tốc độ: Vừa");
    nhanTocDo->setMinimumWidth(95);
    QProgressBar* thanhTienDo = new QProgressBar();
    thanhTienDo->setRange(0, 1);
    thanhTienDo->setValue(0);
    thanhTienDo->setTextVisible(true);
    thanhTienDo->setFormat("Chưa bắt đầu mô phỏng");
    thanhTienDo->setMinimumWidth(180);
    thanhTienDo->setStyleSheet(
        "QProgressBar { background: #e5edf8; border: 1px solid #c5d7ec; "
        "border-radius: 5px; text-align: center; min-height: 22px; }"
        "QProgressBar::chunk { background: #2fa97b; border-radius: 4px; }"
    );
    QHBoxLayout* hangChaySinhDong = new QHBoxLayout();
    hangChaySinhDong->setSpacing(6);
    hangChaySinhDong->addWidget(nutTamDung);
    hangChaySinhDong->addWidget(nhanTocDo);
    hangChaySinhDong->addWidget(thanhTocDo);
    hangChaySinhDong->addWidget(thanhTienDo, 1);
    // Quan ly vong doi o cung hang voi toc do / tien do de tiet kiem chieu cao.
    QPushButton* nutGiaiPhong = new QPushButton("Giải phóng tiến trình");
    QPushButton* nutYeuCauMoi = new QPushButton("Thêm yêu cầu cấp phát mới");
    nutGiaiPhong->setObjectName("nutGiaiPhong");
    nutYeuCauMoi->setObjectName("nutYeuCauMoi");
    ganBieuTuong(nutGiaiPhong, "memory", QColor("#0c8762"));
    ganBieuTuong(nutYeuCauMoi, "plus", QColor("#0c8762"));
    hangChaySinhDong->addWidget(nutGiaiPhong);
    hangChaySinhDong->addWidget(nutYeuCauMoi);
    QPushButton* nutSoSanhLichSu = new QPushButton("So sánh theo lịch sử");
    nutSoSanhLichSu->setObjectName("nutSoSanhLichSu");
    ganBieuTuong(nutSoSanh, "chart", QColor("#1760b1"));
    ganBieuTuong(nutSoSanhLichSu, "history", QColor("#1760b1"));
    boCucDieuKhien->addLayout(hangChaySinhDong);

    // GON_GIAO_DIEN_V4
    QLabel* nhanDienBien = new QLabel("");
    nhanDienBien->setWordWrap(true);
    nhanDienBien->setMinimumHeight(26);
    nhanDienBien->setStyleSheet(
        "QLabel { background: #eef5ff; border: 1px solid #c7d9f3; "
        "border-radius: 7px; padding: 5px 8px; color: #204b75; font-weight: 600; }"
    );
    boCucDieuKhien->addWidget(nhanDienBien);
    nhanDienBien->hide();

    // ==========================
    // SO DO RAM 2D
    // ==========================

    boCuc->addWidget(
    taoTieuDeSection("Sơ đồ RAM logic", "memory")
);

    QGroupBox* khungSoDo = new QGroupBox();
    khungSoDo->setObjectName("khungSoDo");

    QVBoxLayout* boCucSoDo =
        new QVBoxLayout(khungSoDo);
    boCucSoDo->setContentsMargins(10, 6, 10, 6);
    boCucSoDo->setSpacing(4);

    QHBoxLayout* hangChuThich = new QHBoxLayout();
    hangChuThich->setSpacing(5);
    for (const auto& muc : std::vector<std::pair<QString, QString>>{
             {"#fff2d5", "Đang xét"},
             {"#e3efff", "Ứng viên"},
             {"#dcf6e9", "Đã cấp phát / chọn"},
             {"#edf3fa", "RAM trống"}
         }) {
        QLabel* chuThich = new QLabel(muc.second);
        chuThich->setAlignment(Qt::AlignCenter);
        chuThich->setStyleSheet(
            QString("background: %1; color: #20415f; border: 1px solid #ccdae8; "
                    "border-radius: 5px; padding: 3px; font-size: 11px;")
                .arg(muc.first)
        );
        hangChuThich->addWidget(chuThich, 1);
    }
    boCucSoDo->addLayout(hangChuThich);

    QGraphicsScene* canh =
        new QGraphicsScene(khungSoDo);

    QGraphicsView* khungVe =
        new QGraphicsView(canh);

    khungVe->setAlignment(
        Qt::AlignLeft | Qt::AlignTop
    );
    khungVe->setRenderHint(QPainter::Antialiasing, true);

    khungVe->setMinimumHeight(70);
    khungVe->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    boCucSoDo->addWidget(khungVe);
    khungSoDo->setMinimumHeight(130);
    khungSoDo->setMaximumHeight(430);
    boCuc->addWidget(khungSoDo, 0);

    // Hai khung ket qua va so sanh: uu tien bang ket qua rong, de doc.
    QHBoxLayout* hangPhanTich = new QHBoxLayout();
    hangPhanTich->setSpacing(7);
    QGroupBox* khungKetQua = new QGroupBox("Kết quả cấp phát");
    khungKetQua->setObjectName("khungKetQua");
    QVBoxLayout* boCucKetQua = new QVBoxLayout(khungKetQua);
    boCucKetQua->setContentsMargins(8, 5, 8, 7);
    boCucKetQua->setSpacing(3);

    QTableWidget* bangKetQua = taoBang({
        "Tiến trình", "Dung lượng (KB)", "Trạng thái", "Vùng RAM", "Ghi chú"
    });
    bangKetQua->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bangKetQua->setMinimumHeight(230);
    bangKetQua->setAlternatingRowColors(true);
    // Hai khung: bang ket qua co 70% chieu ngang; cot tu can theo kich thuoc.
    // Noi dung dai tu xuong dong; khong rut gon thong tin tinh toan.
    bangKetQua->setWordWrap(true);
    bangKetQua->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bangKetQua->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    bangKetQua->verticalHeader()->setMinimumSectionSize(28);
    bangKetQua->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    boCucKetQua->addWidget(bangKetQua, 1);

    QGroupBox* khungSoSanh = new QGroupBox("So sánh 3 thuật toán");
    khungSoSanh->setObjectName("khungSoSanh");
    QVBoxLayout* boCucSoSanh = new QVBoxLayout(khungSoSanh);
    boCucSoSanh->setContentsMargins(8, 5, 8, 7);
    boCucSoSanh->setSpacing(3);
    QTableWidget* bangSoSanhNhanh = taoBang({"Thuật toán", "Đạt", "RAM trống"});
    bangSoSanhNhanh->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bangSoSanhNhanh->setAlternatingRowColors(true);
    bangSoSanhNhanh->setFixedHeight(136);
    for (int dong = 0; dong < 3; ++dong) {
        bangSoSanhNhanh->insertRow(dong);
        const QString ten[] = {"First Fit", "Best Fit", "Worst Fit"};
        for (int cot = 0; cot < 3; ++cot) {
            QTableWidgetItem* o = new QTableWidgetItem(cot == 0 ? ten[dong] : "—");
            o->setTextAlignment(Qt::AlignCenter);
            bangSoSanhNhanh->setItem(dong, cot, o);
        }
    }
    boCucSoSanh->addWidget(bangSoSanhNhanh);
    QHBoxLayout* hangSoSanhTrucQuan = new QHBoxLayout();
    hangSoSanhTrucQuan->setSpacing(6);
    nutSoSanh->setText("So sánh");
    nutSoSanhLichSu->setText("Theo lịch sử");
    nutSoSanh->setToolTip("So sánh 3 thuật toán từ cùng một bộ dữ liệu.");
    nutSoSanhLichSu->setToolTip("So sánh 3 thuật toán theo các sự kiện cấp phát/giải phóng.");
    hangSoSanhTrucQuan->addWidget(nutSoSanh);
    hangSoSanhTrucQuan->addWidget(nutSoSanhLichSu);
    boCucSoSanh->addLayout(hangSoSanhTrucQuan);

    // Hai khung dashboard: ket qua rong nhat, so sanh o ben phai.
    // Chi bo Nhat ky hien thi; lichSuSuKien va So sanh theo lich su giu nguyen.
    hangPhanTich->addWidget(khungKetQua, 7);
    hangPhanTich->addWidget(khungSoSanh, 3);
    khungKetQua->setMinimumHeight(270);
    khungSoSanh->setMinimumHeight(270);
    khungKetQua->setMaximumHeight(290);
    khungSoSanh->setMaximumHeight(290);
    boCuc->addLayout(hangPhanTich);

    // An nhan rong ban dau: khong lap thong bao da co tren cac the va thanh tien do.
    QLabel* nhanNguonDuLieu = new QLabel("");
    nhanNguonDuLieu->setWordWrap(false);
    nhanNguonDuLieu->setStyleSheet("color: #58718e; font-size: 10px;");
    nhanNguonDuLieu->hide();
    nhanNguonDuLieu->setToolTip("Thông tin nguồn hệ điều hành và mô hình RAM logic.");
    QLabel* nhanTongKet = new QLabel("");
    nhanTongKet->setStyleSheet("color: #174d87; font-weight: 600;");
    nhanTongKet->hide();

    // Dieu huong va huong dan chi de hien thi, khong tac dong bo nho mo phong.
    QObject::connect(nutDiToiMoPhong, &QPushButton::clicked, &cuaSo,
        [=]() { vungCuon->ensureWidgetVisible(khungThongTin, 0, 10); });
    QObject::connect(nutDiToiSoDo, &QPushButton::clicked, &cuaSo,
        [=]() { vungCuon->ensureWidgetVisible(khungSoSanh, 0, 15); });
    QObject::connect(nutDiToiKetQua, &QPushButton::clicked, &cuaSo,
        [=]() { vungCuon->ensureWidgetVisible(khungKetQua, 0, 15); });
    QObject::connect(nutThongTin, &QPushButton::clicked, &cuaSo, [&]() {
        QMessageBox::information(&cuaSo, "Thông tin RAMSimulator",
            "RAMSimulator – Chương 9: Main Memory\n\n"
            "Mô phỏng cấp phát RAM logic bằng First Fit, Best Fit và Worst Fit.\n"
            "Có thể đọc dữ liệu hệ điều hành hoặc tự nhập vùng RAM và tiến trình.\n"
            "Hỗ trợ cấp phát, giải phóng, so sánh và xem lịch sử.\n\n"
            "Lưu ý: mô phỏng không cấp phát hay thu hồi RAM vật lý của máy.");
    });

    // Thanh trang thai gon thay cho nut Thoat qua lon cua V3.
    QFrame* thanhTrangThai = new QFrame(&cuaSo);
    thanhTrangThai->setObjectName("thanhTrangThai");
    QHBoxLayout* hangChanTrang = new QHBoxLayout(thanhTrangThai);
    hangChanTrang->setContentsMargins(9, 1, 9, 1);
    QLabel* nhanTrangThai = new QLabel("●  Hệ thống sẵn sàng");
    nhanTrangThai->setStyleSheet("color: #16936d; font-weight: bold;");
    hangChanTrang->addWidget(nhanTrangThai);
    hangChanTrang->addStretch(1);
    // Source, summary and state live on the same slim footer row.
    hangChanTrang->addWidget(nhanNguonDuLieu);
    hangChanTrang->addSpacing(10);
    hangChanTrang->addWidget(nhanTongKet);
    hangChanTrang->addSpacing(8);
    QPushButton* nutThoat = new QPushButton("Thoát");
    nutThoat->setMaximumWidth(86);
    nutThoat->setMinimumHeight(27);
    ganBieuTuong(nutThoat, "exit", QColor("#527094"), 15);
    hangChanTrang->addWidget(nutThoat);
    boCucNgoai->addWidget(thanhTrangThai);

    // ==========================
    // XU LY THEM, XOA DU LIEU
    // ==========================

    QObject::connect(
        nutThemRam,
        &QPushButton::clicked,
        [&]() {
            themDong(bangRam);
        }
    );

    QObject::connect(
        nutXoaRam,
        &QPushButton::clicked,
        [&]() {
            xoaDong(bangRam, &cuaSo);
        }
    );

    QObject::connect(
        nutThemTienTrinh,
        &QPushButton::clicked,
        [&]() {
            themDong(bangTienTrinh);
        }
    );

    QObject::connect(
        nutXoaTienTrinh,
        &QPushButton::clicked,
        [&]() {
            xoaDong(bangTienTrinh, &cuaSo);
        }
    );

    QObject::connect(
        nutThoat,
        &QPushButton::clicked,
        &cuaSo,
        &QWidget::close
    );

    // ==========================
    // TRANG THAI MO PHONG V4
    // ==========================

    DuLieuMoPhong duLieu;
    TrangThaiBoNho boNhoConLai;
    std::vector<PhanBoDaThucHien> cacPhanBo;
    DanhSachDaCapPhat dangSoHuu;
    // GHI_LICH_SU_TRONG_GUI_V1
    std::vector<SuKienRam> lichSuSuKien;

    int viTriTienTrinh = 0;
    int thanhCong = 0;
    int thatBai = 0;
    bool dangMoPhong = false;
    bool dangTuDong = false;
    bool daTungChayTuDong = false;

    // Mot nhip la mot lan xet vung, cong bo vung chon, hoac cap phat.
    enum class PhaTrinhDien { QuetVung, CongBoLuaChon, CapPhat };
    PhaTrinhDien pha = PhaTrinhDien::QuetVung;
    int chiSoVungQuet = 0;
    int maVungDangXet = -1;
    int maVungUngVien = -1;
    int chiSoUngVien = -1;
    int maVungDuocChon = -1;

    QTimer* dongHo = new QTimer(&cuaSo);
    dongHo->setTimerType(Qt::PreciseTimer);

    auto conTienTrinh = [&]() -> bool {
        return dangMoPhong &&
            viTriTienTrinh < static_cast<int>(duLieu.tienTrinh.size());
    };

    auto chuKy = [&]() -> int {
        // Toc do: 1 rat cham -> 5 rat nhanh, tinh bang mili giay.
        return 1550 - 260 * thanhTocDo->value();
    };

    auto capNhatTocDo = [&]() {
        const QString tenTocDo[] = {
            "Rất chậm", "Chậm", "Vừa", "Nhanh", "Rất nhanh"
        };
        nhanTocDo->setText(
            QString("Tốc độ: %1 (%2 ms)")
                .arg(tenTocDo[thanhTocDo->value() - 1])
                .arg(chuKy())
        );
    };

    // Khoa chinh sua dau vao nhung van cho phep cuon/xem bang.
    auto khoaNhapLieu = [&](bool khoa) {
        bangRam->setEditTriggers(
            khoa ? QAbstractItemView::NoEditTriggers
                 : QAbstractItemView::AllEditTriggers
        );
        bangTienTrinh->setEditTriggers(
            khoa ? QAbstractItemView::NoEditTriggers
                 : QAbstractItemView::AllEditTriggers
        );
        chonThuatToan->setEnabled(!khoa);
        for (QPushButton* nut : {
            nutThemRam, nutXoaRam, nutThemTienTrinh, nutXoaTienTrinh,
            nutKiemTra, nutLayDuLieuThuc, nutBatDau
        }) {
            nut->setEnabled(!khoa);
        }
        const bool coViec = khoa && conTienTrinh();
        nutBuocTiepTheo->setEnabled(coViec && !dangTuDong);
        nutChayHet->setEnabled(coViec && !dangTuDong);
        nutTamDung->setEnabled(coViec && (dangTuDong || daTungChayTuDong));
        nutTamDung->setText(dangTuDong ? "Tạm dừng" : "Tiếp tục");
        nutSoSanh->setEnabled(!dangTuDong);
        nutSoSanhLichSu->setEnabled(dangMoPhong && !dangTuDong && !lichSuSuKien.empty());
        nutGiaiPhong->setEnabled(khoa && !dangTuDong && !dangSoHuu.empty());
        nutYeuCauMoi->setEnabled(khoa && !dangTuDong);
    };

    auto dieuChinhChieuCaoSoDo = [&]() {
        int soVung = std::max(1, bangRam->rowCount());
        int chieuCao = std::clamp(63 + soVung * 67, 130, 430);
        khungSoDo->setMinimumHeight(chieuCao);
        khungSoDo->setMaximumHeight(chieuCao);
    };

    auto veTrangThai = [&](int dangXet = -1, int daChon = -1) {
        dieuChinhChieuCaoSoDo();
        veSoDo(canh, duLieu, cacPhanBo, boNhoConLai, dangXet, daChon, maVungUngVien);
    };

    auto capNhatTongKet = [&]() {
        nhanTongKet->setText(
            QString("Thành công: %1 | Thất bại: %2 | RAM trống: %3 KB")
                .arg(thanhCong).arg(thatBai)
                .arg(tongDungLuongTrongKB(boNhoConLai))
        );
        nhanTongKet->show();
        thanhTienDo->setRange(
            0, std::max(1, static_cast<int>(duLieu.tienTrinh.size()))
        );
        thanhTienDo->setValue(viTriTienTrinh);
        thanhTienDo->setFormat("Đã xử lý %v/%m tiến trình");
    };

    // Doc RAM va tien trinh tu he dieu hanh, khong thay doi cach doc V3.
    QObject::connect(nutLayDuLieuThuc, &QPushButton::clicked, &cuaSo, [&]() {
        qint64 tongKB = 0;
        qint64 khaDungKB = 0;
        QString nguon;
        QString loi;
        QVector<TienTrinhHeThong> danhSach;
        if (!docRamHeThong(tongKB, khaDungKB, nguon)) {
            QMessageBox::warning(&cuaSo, "Lỗi", "Không đọc được thông tin RAM.");
            return;
        }
        if (!docTienTrinhHeThong(danhSach, loi)) {
            QMessageBox::warning(&cuaSo, "Lỗi", loi);
            return;
        }
        if (khaDungKB > std::numeric_limits<int>::max()) {
            QMessageBox::warning(
                &cuaSo, "Lỗi", "Dung lượng vượt giới hạn của mô hình C++ hiện tại."
            );
            return;
        }
        bangRam->setRowCount(0);
        bangTienTrinh->setRowCount(0);
        // Dia chi 0 la offset logic, khong phai dia chi RAM vat ly.
        bangRam->insertRow(0);
        bangRam->setItem(0, 0, new QTableWidgetItem("RAM khả dụng (logic)"));
        bangRam->setItem(0, 1, new QTableWidgetItem("0"));
        bangRam->setItem(0, 2, new QTableWidgetItem(QString::number(khaDungKB)));
        for (int i = 0; i < danhSach.size(); ++i) {
            bangTienTrinh->insertRow(i);
            bangTienTrinh->setItem(i, 0, new QTableWidgetItem(danhSach.at(i).ma));
            bangTienTrinh->setItem(i, 1, new QTableWidgetItem(
                QString::number(danhSach.at(i).dungLuongKB)));
        }
        const QString thoiDiem = QDateTime::currentDateTime()
            .toString("HH:mm:ss dd/MM/yyyy");
        giaTriTongRam->setText(QString::number(tongKB / 1024) + " MB");
        giaTriRamKhaDung->setText(QString::number(khaDungKB / 1024) + " MB");
        giaTriTienTrinh->setText(QString::number(danhSach.size()) + " tiến trình");
        giaTriCapNhat->setText(thoiDiem);
        bieuDoRam->capNhat(tongKB / 1024, khaDungKB / 1024);
        nhanNguonDuLieu->setText(
            QString("Nguồn: %1 · RAM logic mô phỏng").arg(nguon)
        );
        nhanNguonDuLieu->show();
        nhanTongKet->hide();
        nhanDienBien->hide();
        dieuChinhChieuCaoSoDo();
        canh->clear();
        thanhTienDo->setRange(0, std::max(1, static_cast<int>(danhSach.size())));
        thanhTienDo->setValue(0);
        thanhTienDo->setFormat("Chưa bắt đầu mô phỏng");
    });

    QObject::connect(nutKiemTra, &QPushButton::clicked, &cuaSo, [&]() {
        DuLieuMoPhong duLieuThu;
        if (docVaKiemTraDuLieu(&cuaSo, bangRam, bangTienTrinh, duLieuThu)) {
            QMessageBox::information(
                &cuaSo, "Kết quả kiểm tra", "Dữ liệu hợp lệ, có thể bắt đầu mô phỏng."
            );
        }
    });

    QObject::connect(nutBatDau, &QPushButton::clicked, &cuaSo, [&]() {
        DuLieuMoPhong duLieuMoi;
        if (!docVaKiemTraDuLieu(&cuaSo, bangRam, bangTienTrinh, duLieuMoi))
            return;
        dongHo->stop();
        duLieu = std::move(duLieuMoi);
        boNhoConLai = saoChepBoNho(duLieu.boNho);
        cacPhanBo.clear();
        dangSoHuu.clear();
        lichSuSuKien.clear();
        viTriTienTrinh = 0;
        thanhCong = 0;
        thatBai = 0;
        pha = PhaTrinhDien::QuetVung;
        chiSoVungQuet = 0;
        maVungDangXet = -1;
        maVungUngVien = -1;
        chiSoUngVien = -1;
        maVungDuocChon = -1;
        dangMoPhong = true;
        dangTuDong = false;
        daTungChayTuDong = false;
        bangKetQua->setRowCount(0);
        veTrangThai();
        capNhatTongKet();
        nhanDienBien->show();
        nhanDienBien->setText(
            QString("Đã chọn %1. Sẵn sàng cấp phát.").arg(chonThuatToan->currentText())
        );
        khoaNhapLieu(true);
    });

    auto capPhatBangThuVien = [&](TrangThaiBoNho& ram,
                                 const YeuCau& yc) -> KetQuaCapPhat {
        if (chonThuatToan->currentIndex() == 0) return capPhatDauTien(ram, yc);
        if (chonThuatToan->currentIndex() == 1) return capPhatVuaNhat(ram, yc);
        return capPhatLonNhat(ram, yc);
    };

    // Mot nhip cua dong ho: quet mot vung -> thong bao chon -> cap phat.
    auto thucHienMotNhip = [&]() {
        if (!conTienTrinh()) {
            dongHo->stop();
            dangTuDong = false;
            khoaNhapLieu(dangMoPhong);
            return;
        }
        const YeuCau& yc = duLieu.tienTrinh[viTriTienTrinh];
        const QString ten = QString::fromStdString(yc.maTienTrinh);
        const int canKB = yc.dungLuongYeuCauKB;
        const QString thuatToan = chonThuatToan->currentText();

        if (pha == PhaTrinhDien::QuetVung) {
            if (chiSoVungQuet >= static_cast<int>(boNhoConLai.size())) {
                pha = PhaTrinhDien::CongBoLuaChon;
            } else {
                const int viTriDangQuet = chiSoVungQuet;
                const VungTrong& vung = boNhoConLai[chiSoVungQuet++];
                const QString tenVung = duLieu.tenVung.at(vung.ma - 1);
                const bool duBoNho = vung.dungLuongTrongKB >= canKB;
                maVungDangXet = vung.ma;
                if (duBoNho) {
                    bool nenThay = (chiSoUngVien == -1);
                    if (chiSoUngVien >= 0) {
                        const VungTrong& u = boNhoConLai[chiSoUngVien];

                        if (chonThuatToan->currentIndex() == 1)
                            nenThay = vung.dungLuongTrongKB < u.dungLuongTrongKB ||
                                (vung.dungLuongTrongKB == u.dungLuongTrongKB &&
                                 vung.diaChiBatDauKB < u.diaChiBatDauKB);

                        if (chonThuatToan->currentIndex() == 2)
                            nenThay = vung.dungLuongTrongKB > u.dungLuongTrongKB ||
                                (vung.dungLuongTrongKB == u.dungLuongTrongKB &&
                                 vung.diaChiBatDauKB < u.diaChiBatDauKB);
                    }

                    if (nenThay) {
                        chiSoUngVien = viTriDangQuet;
                        maVungUngVien = vung.ma;
                    }
                    // First Fit dung o vung dau tien du lon.
                    if (chonThuatToan->currentIndex() == 0)
                        chiSoVungQuet = static_cast<int>(boNhoConLai.size());
                }
                nhanDienBien->show();
                nhanDienBien->setText(
                    QString("%1 | %2 cần %3 KB. Đang xét %4: còn %5 KB — %6.%7")
                        .arg(thuatToan).arg(ten).arg(canKB).arg(tenVung)
                        .arg(vung.dungLuongTrongKB)
                        .arg(duBoNho ? "ĐỦ dung lượng" : "KHÔNG đủ dung lượng")
                        .arg(duBoNho && chonThuatToan->currentIndex() == 0
                             ? " First Fit dừng tìm kiếm tại đây" : "")
                );
                if (chiSoVungQuet >= static_cast<int>(boNhoConLai.size()))
                    pha = PhaTrinhDien::CongBoLuaChon;
                veTrangThai(maVungDangXet);
                khoaNhapLieu(true);
                return;
            }
        }

        if (pha == PhaTrinhDien::CongBoLuaChon) {
            // Chay tren BAN SAO de lay dung quyet dinh cua thuat toan goc.
            TrangThaiBoNho banSao = saoChepBoNho(boNhoConLai);
            KetQuaCapPhat duKien = capPhatBangThuVien(banSao, yc);
            maVungDuocChon = duKien.thanhCong ? duKien.maVung : -1;
            maVungDangXet = -1;
            maVungUngVien = -1;
            chiSoUngVien = -1;
            if (duKien.thanhCong) {
                nhanDienBien->show();
                nhanDienBien->setText(
                    QString("%1: %2 được chọn cho %3 (%4 KB). "
                            "Nhấn bước tiếp hoặc đợi nhịp kế để cấp phát.")
                        .arg(thuatToan)
                        .arg(duLieu.tenVung.at(duKien.maVung - 1))
                        .arg(ten).arg(canKB)
                );
            } else {
                nhanDienBien->show();
                nhanDienBien->setText(
                    QString("%1: Không tìm thấy vùng RAM đủ cho %2 (%3 KB). "
                            "Nhịp tiếp theo sẽ ghi kết quả thất bại.")
                        .arg(thuatToan).arg(ten).arg(canKB)
                );
            }
            veTrangThai(-1, maVungDuocChon);
            pha = PhaTrinhDien::CapPhat;
            khoaNhapLieu(true);
            return;
        }

        // Pha CapPhat: chi luc nay moi cap nhat bo nho that.
        const TrangThaiBoNho truoc = saoChepBoNho(boNhoConLai);
        KetQuaCapPhat ketQua = capPhatBangThuVien(boNhoConLai, yc);
        lichSuSuKien.push_back({LoaiSuKienRam::CapPhat, yc.maTienTrinh, yc.dungLuongYeuCauKB});
        QString tenVung = "—";
        if (ketQua.thanhCong) {
            ++thanhCong;
            // SUA_DIA_CHI_KHOANG_TRONG_V1
            // Xac dinh dung khoang RAM da thay doi.
            for (std::size_t chiSo = 0;
                 chiSo < truoc.size() && chiSo < boNhoConLai.size();
                 ++chiSo) {
                const VungTrong& vung = truoc[chiSo];
                const VungTrong& sau = boNhoConLai[chiSo];
                if (vung.ma != ketQua.maVung) continue;
                if (sau.diaChiBatDauKB - vung.diaChiBatDauKB != canKB ||
                    vung.dungLuongTrongKB - sau.dungLuongTrongKB != canKB)
                    continue;
                tenVung = duLieu.tenVung.at(vung.ma - 1);
                cacPhanBo.push_back({
                    vung.ma, ten, vung.diaChiBatDauKB, canKB
                });
                dangSoHuu.push_back({
                    yc.maTienTrinh, vung.ma, vung.diaChiBatDauKB, canKB
                });
                break;
            }
        } else {
            ++thatBai;
        }
        const int dong = bangKetQua->rowCount();
        bangKetQua->insertRow(dong);
        const QStringList cacCot = {
            ten,
            QString::number(canKB),
            ketQua.thanhCong ? "Thành công" : "Thất bại",
            tenVung,
            ketQua.thanhCong
                ? QString("Còn %1 KB").arg(ketQua.dungLuongConLaiKB)
                : hienThiLyDoTiengViet(ketQua.lyDo)
        };
        for (int i = 0; i < cacCot.size(); ++i) {
            QTableWidgetItem* o = new QTableWidgetItem(cacCot.at(i));
            o->setToolTip(i == 4 && ketQua.thanhCong
                ? QString("Còn %1 KB tại %2")
                    .arg(ketQua.dungLuongConLaiKB).arg(tenVung)
                : cacCot.at(i));
            if (i == 2) {
                o->setForeground(QBrush(ketQua.thanhCong
                    ? QColor("#086f50") : QColor("#aa3347")));
                o->setBackground(QBrush(ketQua.thanhCong
                    ? QColor("#e2f8eb") : QColor("#fff0f0")));
            }
            bangKetQua->setItem(dong, i, o);
        }
        bangKetQua->selectRow(dong);
        bangKetQua->scrollToBottom();
        ++viTriTienTrinh;
        pha = PhaTrinhDien::QuetVung;
        chiSoVungQuet = 0;
        maVungDangXet = -1;
        maVungUngVien = -1;
        chiSoUngVien = -1;
        maVungDuocChon = -1;
        // Cap phat da xong: khong giu vien "vung duoc chon" tren P1-P5.
        // Giai doan chon vung van co vien nhan manh o nhip truoc do.
        veTrangThai();
        capNhatTongKet();
        nhanDienBien->show();
        nhanDienBien->setText(
            QString("%1: %2 — %3%4")
                .arg(ten)
                .arg(ketQua.thanhCong ? "cấp phát thành công" : "cấp phát thất bại")
                .arg(ketQua.thanhCong ? "Vùng " + tenVung :
                     hienThiLyDoTiengViet(ketQua.lyDo))
                .arg(conTienTrinh() ? ". Đang chuẩn bị tiến trình kế tiếp." :
                     ". ĐÃ HOÀN TẤT MÔ PHỎNG.")
        );
        if (!conTienTrinh()) {
            dongHo->stop();
            dangTuDong = false;
        }
        khoaNhapLieu(true);
    };

    QObject::connect(dongHo, &QTimer::timeout, &cuaSo, [&]() {
        thucHienMotNhip();
    });
    QObject::connect(nutBuocTiepTheo, &QPushButton::clicked, &cuaSo, [&]() {
        if (dangTuDong) {
            dongHo->stop();
            dangTuDong = false;
        }
        thucHienMotNhip();
    });
    QObject::connect(nutChayHet, &QPushButton::clicked, &cuaSo, [&]() {
        if (!conTienTrinh()) return;
        dangTuDong = true;
        daTungChayTuDong = true;
        dongHo->start(chuKy());
        khoaNhapLieu(true);
    });
    QObject::connect(nutTamDung, &QPushButton::clicked, &cuaSo, [&]() {
        if (!conTienTrinh() || !daTungChayTuDong) return;
        if (dangTuDong) {
            dongHo->stop();
            dangTuDong = false;
            nhanDienBien->show();
            nhanDienBien->setText("Đã tạm dừng.");
        } else {
            dangTuDong = true;
            dongHo->start(chuKy());
        }
        khoaNhapLieu(true);
    });
    QObject::connect(thanhTocDo, &QSlider::valueChanged, &cuaSo, [&](int) {
        capNhatTocDo();
        if (dangTuDong) dongHo->start(chuKy());
    });


    // Giai phong vung RAM cua mot tien trinh da cap phat.
    QObject::connect(nutGiaiPhong, &QPushButton::clicked, &cuaSo, [&]() {
        if (!dangMoPhong || dangTuDong || dangSoHuu.empty()) return;

        QStringList luaChon;

        for (const PhanBoDaThucHien& muc : cacPhanBo) {
            luaChon << QString("%1 — %2 KB — %3")
                .arg(muc.tenTienTrinh)
                .arg(muc.dungLuongKB)
                .arg(duLieu.tenVung.at(muc.maVung - 1));
        }

        bool dongY = false;

        QString mucChon = QInputDialog::getItem(
            &cuaSo, "Giải phóng bộ nhớ",
            "Chọn tiến trình đã cấp phát:",
            luaChon, 0, false, &dongY
        );

        if (!dongY) return;

        int chiSoChon = luaChon.indexOf(mucChon);

        if (chiSoChon < 0 ||
            chiSoChon >= static_cast<int>(cacPhanBo.size())) {
            return;
        }

        const PhanBoDaThucHien muc = cacPhanBo[chiSoChon];

        std::string loi;

        if (!giaiPhongTienTrinh(
                boNhoConLai, dangSoHuu,
                muc.tenTienTrinh.toStdString(), loi)) {
            QMessageBox::warning(
                &cuaSo, "Không giải phóng được",
                hienThiLyDoTiengViet(loi)
            );
            return;
        }

        lichSuSuKien.push_back({LoaiSuKienRam::GiaiPhong, muc.tenTienTrinh.toStdString(), 0});
        cacPhanBo.erase(cacPhanBo.begin() + chiSoChon);

        // RAM da thay doi: quet lai tu dau o nhip tiep theo.
        pha = PhaTrinhDien::QuetVung;
        chiSoVungQuet = 0;
        chiSoUngVien = -1;
        maVungDangXet = -1;
        maVungUngVien = -1;
        maVungDuocChon = -1;

        for (int dong = 0; dong < bangKetQua->rowCount(); ++dong) {
            if (layChu(bangKetQua, dong, 0) == muc.tenTienTrinh) {
                // Cap nhat mau/tooltip theo trang thai giai phong hien tai.
                QTableWidgetItem* oTrangThai = bangKetQua->item(dong, 2);
                oTrangThai->setText("Đã giải phóng");
                oTrangThai->setForeground(QBrush(QColor("#245d9d")));
                oTrangThai->setBackground(QBrush(QColor("#eaf2ff")));
                QTableWidgetItem* oGhiChu = bangKetQua->item(dong, 4);
                const QString thongBaoThuHoi = QString("Đã thu hồi %1 KB")
                    .arg(muc.dungLuongKB);
                oGhiChu->setText(thongBaoThuHoi);
                oGhiChu->setToolTip(thongBaoThuHoi);
                break;
            }
        }

        veTrangThai();
        capNhatTongKet();

        nhanDienBien->show();
        nhanDienBien->setText(
            QString("Đã giải phóng %1 (%2 KB). RAM trống: %3 KB.")
                .arg(muc.tenTienTrinh)
                .arg(muc.dungLuongKB)
                .arg(tongDungLuongTrongKB(boNhoConLai))
        );

        khoaNhapLieu(true);
    });

    // Them yeu cau moi ma khong can dat lai RAM.
    QObject::connect(nutYeuCauMoi, &QPushButton::clicked, &cuaSo, [&]() {
        if (!dangMoPhong || dangTuDong) return;

        bool dongY = false;

        QString ma = QInputDialog::getText(
            &cuaSo, "Yêu cầu cấp phát mới",
            "Nhập mã tiến trình mới:",
            QLineEdit::Normal, QString(), &dongY
        ).trimmed();

        if (!dongY) return;

        if (ma.isEmpty()) {
            QMessageBox::warning(
                &cuaSo, "Mã không hợp lệ",
                "Mã tiến trình không được để trống."
            );
            return;
        }

        for (const YeuCau& yc : duLieu.tienTrinh) {
            if (QString::fromStdString(yc.maTienTrinh).compare(
                    ma, Qt::CaseInsensitive) == 0) {
                QMessageBox::warning(
                    &cuaSo, "Mã bị trùng",
                    "Hãy sử dụng một mã tiến trình mới."
                );
                return;
            }
        }

        int kb = QInputDialog::getInt(
            &cuaSo, "Dung lượng yêu cầu",
            "Số KB cần cấp phát:",
            100, 1, std::numeric_limits<int>::max(), 1, &dongY
        );

        if (!dongY) return;

        bool daKetThuc = !conTienTrinh();

        duLieu.tienTrinh.push_back({
            ma.toStdString(), kb
        });

        int dong = bangTienTrinh->rowCount();
        bangTienTrinh->insertRow(dong);
        bangTienTrinh->setItem(dong, 0, new QTableWidgetItem(ma));
        bangTienTrinh->setItem(
            dong, 1, new QTableWidgetItem(QString::number(kb))
        );

        if (daKetThuc) {
            pha = PhaTrinhDien::QuetVung;
            chiSoVungQuet = 0;
            chiSoUngVien = -1;
            maVungDangXet = -1;
            maVungUngVien = -1;
            maVungDuocChon = -1;
        }

        capNhatTongKet();

        nhanDienBien->show();
        nhanDienBien->setText(
            QString("Đã thêm %1 (%2 KB). Chờ cấp phát.")
                .arg(ma).arg(kb)
        );

        khoaNhapLieu(true);
    });


    // So sanh ba thuat toan theo lich su su kien da hoan thanh.
    QObject::connect(
        nutSoSanhLichSu,
        &QPushButton::clicked,
        &cuaSo,
        [&]() {
            if (!dangMoPhong || lichSuSuKien.empty() || dangTuDong) {
                QMessageBox::information(
                    &cuaSo, "Chưa có lịch sử",
                    "Hãy xử lý ít nhất một yêu cầu cấp phát "
                    "và tạm dừng mô phỏng nếu đang chạy."
                );
                return;
            }

            QDialog hopThoai(&cuaSo);
            hopThoai.setWindowTitle("So sánh theo lịch sử hoạt động");
            hopThoai.resize(1150, 395);

            QVBoxLayout* boCucLichSu = new QVBoxLayout(&hopThoai);


            QLabel* nhanMoTa = new QLabel(
                QString("%1 sự kiện · Cùng trạng thái RAM ban đầu.")
                    .arg(static_cast<int>(lichSuSuKien.size()))
            );
            nhanMoTa->setWordWrap(true);
            boCucLichSu->addWidget(nhanMoTa);

            QTableWidget* bang = new QTableWidget(3, 11, &hopThoai);

            bang->setHorizontalHeaderLabels({
                "Thuật toán",
                "Cấp thành công",
                "Cấp thất bại",
                "Giải phóng",
                "Bỏ qua giải phóng",
                "Phân mảnh ngoài",
                "Thiếu tổng RAM",
                "Đang chiếm",
                "RAM trống (KB)",
                "Số vùng trống",
                "Vùng lớn nhất (KB)"
            });

            bang->horizontalHeader()->setSectionResizeMode(
                QHeaderView::ResizeToContents
            );

            bang->verticalHeader()->hide();
            bang->setEditTriggers(
                QAbstractItemView::NoEditTriggers
            );
            bang->setSelectionBehavior(
                QAbstractItemView::SelectRows
            );

            const QString tenThuatToan[] = {
                "First Fit", "Best Fit", "Worst Fit"
            };

            for (int loai = 0; loai < 3; ++loai) {
                const BaoCaoLichSu kq = moPhongLichSu(
                    duLieu.boNho, lichSuSuKien, loai
                );

                QStringList cot = {
                    tenThuatToan[loai],
                    QString::number(kq.capPhatThanhCong),
                    QString::number(kq.capPhatThatBai),
                    QString::number(kq.giaiPhongThanhCong),
                    QString::number(kq.giaiPhongBoQua),
                    QString::number(kq.soLanPhanManhNgoai),
                    QString::number(kq.soLanThieuTongRam),
                    QString::number(kq.soTienTrinhDangChiem),
                    QString::number(kq.tongRamTrongKB),
                    QString::number(kq.soVungTrong),
                    QString::number(kq.vungTrongLonNhatKB)
                };

                for (int j = 0; j < cot.size(); ++j) {
                    QTableWidgetItem* o =
                        new QTableWidgetItem(cot.at(j));
                    o->setTextAlignment(Qt::AlignCenter);
                    bang->setItem(loai, j, o);
                }
            }

            boCucLichSu->addWidget(bang);

            QLabel* ghiChu = new QLabel(
                "Chỉ tính sự kiện hoàn thành. Giải phóng tiến trình chưa cấp phát được tính là bỏ qua."
            );
            ghiChu->setWordWrap(true);
            boCucLichSu->addWidget(ghiChu);

            QPushButton* dong = new QPushButton("Đóng");
            boCucLichSu->addWidget(dong);

            QObject::connect(
                dong, &QPushButton::clicked,
                &hopThoai, &QDialog::accept
            );

            hopThoai.exec();
        }
    );

    QObject::connect(nutDatLai, &QPushButton::clicked, &cuaSo, [&]() {
        dongHo->stop();
        dangMoPhong = false;
        dangTuDong = false;
        daTungChayTuDong = false;
        duLieu = {};
        boNhoConLai.clear();
        cacPhanBo.clear();
        dangSoHuu.clear();
        lichSuSuKien.clear();
        viTriTienTrinh = 0;
        thanhCong = 0;
        thatBai = 0;
        pha = PhaTrinhDien::QuetVung;
        chiSoVungQuet = 0;
        maVungDangXet = -1;
        maVungUngVien = -1;
        chiSoUngVien = -1;
        maVungDuocChon = -1;
        bangKetQua->setRowCount(0);
        canh->clear();
        thanhTienDo->setRange(0, std::max(1, bangTienTrinh->rowCount()));
        thanhTienDo->setValue(0);
        thanhTienDo->setFormat("Chưa bắt đầu mô phỏng");
        nhanTongKet->hide();
        nhanDienBien->hide();
        khoaNhapLieu(false);
    });

    // ==========================
    // SO SANH BA THUAT TOAN
    // ==========================


    // BANG SO SANH DANG COT
    QObject::connect(
        nutSoSanh,
        &QPushButton::clicked,
        [&]() {
            DuLieuMoPhong duLieuSoSanh;

            if (dangMoPhong) {
                duLieuSoSanh = duLieu;
            }
            else if (!docVaKiemTraDuLieu(
                &cuaSo,
                bangRam,
                bangTienTrinh,
                duLieuSoSanh
            )) {
                return;
            }

            QDialog hopThoai(&cuaSo);
            hopThoai.setWindowTitle("So sánh 3 thuật toán");
            hopThoai.resize(850, 270);

            QVBoxLayout* boCucHopThoai =
                new QVBoxLayout(&hopThoai);


            QTableWidget* bangSoSanh =
                new QTableWidget(3, 4, &hopThoai);

            bangSoSanh->setHorizontalHeaderLabels({
                "Thuật toán",
                "Thành công",
                "Thất bại",
                "RAM còn (KB)"
            });

            bangSoSanh->horizontalHeader()
                ->setSectionResizeMode(QHeaderView::Stretch);

            bangSoSanh->verticalHeader()->hide();
            bangSoSanh->setAlternatingRowColors(true);
            bangSoSanh->setFixedHeight(162);
            bangSoSanh->setEditTriggers(
                QAbstractItemView::NoEditTriggers
            );

            const QString tenThuatToan[] = {
                "First Fit",
                "Best Fit",
                "Worst Fit"
            };

            for (int loai = 0; loai < 3; loai++) {
                TrangThaiBoNho ram =
                    saoChepBoNho(duLieuSoSanh.boNho);

                int thanhCong = 0;

                for (const YeuCau& yeuCau :
                     duLieuSoSanh.tienTrinh) {

                    KetQuaCapPhat ketQua;

                    if (loai == 0) {
                        ketQua = capPhatDauTien(ram, yeuCau);
                    }
                    else if (loai == 1) {
                        ketQua = capPhatVuaNhat(ram, yeuCau);
                    }
                    else {
                        ketQua = capPhatLonNhat(ram, yeuCau);
                    }

                    if (ketQua.thanhCong) {
                        thanhCong++;
                    }
                }

                int tongTienTrinh = static_cast<int>(
                    duLieuSoSanh.tienTrinh.size()
                );

                QStringList giaTri = {
                    tenThuatToan[loai],
                    QString::number(thanhCong),
                    QString::number(tongTienTrinh - thanhCong),
                    QString::number(tongDungLuongTrongKB(ram))
                };

                for (int cot = 0; cot < 4; cot++) {
                    QTableWidgetItem* o =
                        new QTableWidgetItem(giaTri.at(cot));

                    o->setTextAlignment(Qt::AlignCenter);
                    bangSoSanh->setItem(loai, cot, o);
                }
            }

            boCucHopThoai->addWidget(bangSoSanh);

            QPushButton* nutDong =
                new QPushButton("Đóng");

            boCucHopThoai->addWidget(nutDong);

            QObject::connect(
                nutDong,
                &QPushButton::clicked,
                &hopThoai,
                &QDialog::accept
            );

            hopThoai.exec();
        }
    );

    // Bang so sanh nhanh chi doc du lieu hien co;
    // su kien lich su con nguyen cho so sanh theo lich su.
    auto capNhatBangSoSanhNhanh = [&]() {
        if (duLieu.boNho.empty() || duLieu.tienTrinh.empty()) {
            for (int r = 0; r < 3; ++r) {
                bangSoSanhNhanh->item(r, 1)->setText("—");
                bangSoSanhNhanh->item(r, 2)->setText("—");
            }
            return;
        }
        for (int loai = 0; loai < 3; ++loai) {
            TrangThaiBoNho ramBanSao = saoChepBoNho(duLieu.boNho);
            int dat = 0;
            for (const YeuCau& yc : duLieu.tienTrinh) {
                KetQuaCapPhat ketQua;
                if (loai == 0) ketQua = capPhatDauTien(ramBanSao, yc);
                else if (loai == 1) ketQua = capPhatVuaNhat(ramBanSao, yc);
                else ketQua = capPhatLonNhat(ramBanSao, yc);
                if (ketQua.thanhCong) ++dat;
            }
            bangSoSanhNhanh->item(loai, 1)->setText(
                QString("%1/%2").arg(dat).arg(static_cast<int>(duLieu.tienTrinh.size())));
            bangSoSanhNhanh->item(loai, 2)->setText(
                QString::number(tongDungLuongTrongKB(ramBanSao)) + " KB");
        }
    };

    // Ket noi sau cac handler nghiep vu: chi cap nhat giao dien sau moi thao tac.
    QObject::connect(nutBatDau, &QPushButton::clicked, &cuaSo, [&]() {
        capNhatBangSoSanhNhanh();
        if (dangMoPhong) nhanTrangThai->setText("●  Đang mô phỏng");
    });
    QObject::connect(nutDatLai, &QPushButton::clicked, &cuaSo, [&]() {
        capNhatBangSoSanhNhanh();
        nhanTrangThai->setText("●  Hệ thống sẵn sàng");
    });
    QObject::connect(dongHo, &QTimer::timeout, &cuaSo, [&]() {
        if (dangMoPhong && !conTienTrinh())
            nhanTrangThai->setText("●  Hoàn tất mô phỏng");
    });
    for (QPushButton* nut : {nutBuocTiepTheo, nutGiaiPhong, nutYeuCauMoi}) {
        QObject::connect(nut, &QPushButton::clicked, &cuaSo, [&, nut]() {
                if (nut == nutYeuCauMoi) capNhatBangSoSanhNhanh();
            if (dangMoPhong && !conTienTrinh())
                nhanTrangThai->setText("●  Hoàn tất mô phỏng");
        });
    }

    // Trang thai ban dau cua cac nut.
    capNhatTocDo();
    khoaNhapLieu(false);

    dieuChinhChieuCaoSoDo();

    cuaSo.show();

    return ungDung.exec();
}
