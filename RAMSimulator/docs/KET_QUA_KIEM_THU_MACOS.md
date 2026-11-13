<!-- RAMSIMULATOR_V3_GENERATED -->

# Kết quả kiểm thử RAMSimulator trên macOS

- Thời điểm lập báo cáo: 11/11/2026 23:59:33
- Môi trường: macOS, C++17, CMake, Qt6.
- Mã nguồn: repository HE-DIEU-HANH, nhánh main.
- Kết quả: 7/7 bộ kiểm thử PASS.
- Giao diện Qt: biên dịch thành công.
- Dashboard và chức năng đọc dữ liệu macOS đã được kiểm tra trực quan.
- Windows: chưa kiểm thử.
- Linux: chưa kiểm thử.

## Kết quả CTest

```text
1/7 Test #1: kiem_thu_bo_nho ..................   Passed    0.00 sec
2/7 Test #2: kiem_thu_cap_phat_dau_tien .......   Passed    0.00 sec
3/7 Test #3: kiem_thu_cap_phat_vua_nhat .......   Passed    0.00 sec
4/7 Test #4: kiem_thu_cap_phat_lon_nhat .......   Passed    0.00 sec
5/7 Test #5: kiem_thu_dien_bien ...............   Passed    0.00 sec
6/7 Test #6: kiem_thu_so_sanh .................   Passed    0.00 sec
7/7 Test #7: kiem_thu_nhap_du_lieu ............   Passed    0.00 sec
100% tests passed out of 7
Total Test time (real) =   0.02 sec
```

## Phạm vi xác nhận

Bảy bộ kiểm thử kiểm tra phần C++ cốt lõi:
quản lý bộ nhớ, ba thuật toán cấp phát,
diễn biến cấp phát, so sánh và nhập dữ liệu.

Kết quả này không chứng minh chương trình
đã hoạt động trên Windows hoặc Linux.
