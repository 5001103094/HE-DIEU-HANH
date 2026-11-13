<!-- RAMSIMULATOR_V3_GENERATED -->

# Hướng dẫn chạy RAMSimulator đa nền tảng

## 1. Giới thiệu

RAMSimulator là chương trình mô phỏng cấp phát bộ nhớ RAM bằng C++17,
gồm ba thuật toán:

- First Fit: cấp phát vào vùng trống phù hợp đầu tiên.
- Best Fit: cấp phát vào vùng trống phù hợp nhỏ nhất.
- Worst Fit: cấp phát vào vùng trống phù hợp lớn nhất.

Chương trình có giao diện Qt6, sơ đồ cấp phát RAM logic,
bảng kết quả, chức năng so sánh và bộ kiểm thử tự động.

## 2. Lưu ý về dữ liệu thực tế

Chức năng đọc dữ liệu hệ thống sử dụng thông tin do hệ điều hành
cung cấp tại thời điểm lấy mẫu.

- macOS: đọc thông tin RAM và tiến trình đang chạy.
- Windows: mã nguồn có phần xử lý dành cho Windows,
  nhưng chưa được kiểm thử thực tế.

RAM khả dụng là giá trị ước tính, không phải lượng RAM
được hệ điều hành bảo đảm dành riêng cho chương trình.

First Fit, Best Fit và Worst Fit chỉ thực hiện cấp phát
trên mô hình RAM logic. Chúng không thay đổi cách hệ điều hành
cấp phát RAM vật lý.

Khi dữ liệu đầu vào chỉ có một vùng trống, ba thuật toán
có thể cho kết quả giống nhau. Để so sánh sự khác biệt,
cần sử dụng bộ dữ liệu gồm nhiều vùng trống.

## 3. Chạy trên macOS

Yêu cầu: CMake, Qt6 và trình biên dịch C++17.

Cài đặt công cụ nếu chưa có:

```bash
brew install cmake qtbase
```

Tại thư mục gốc dự án:

```bash
cmake -S RAMSimulator \
  -B RAMSimulator/ket_qua_bien_dich \
  -DCMAKE_PREFIX_PATH="$(brew --prefix qtbase)"

cmake --build RAMSimulator/ket_qua_bien_dich --parallel 4

ctest --test-dir RAMSimulator/ket_qua_bien_dich \
  --output-on-failure
```

Mở giao diện:

```bash
./RAMSimulator/ket_qua_bien_dich/mo_phong_bo_nho_giao_dien
```

## 4. Chạy trên Windows - sẽ kiểm thử sau

Yêu cầu dự kiến:

- Visual Studio 2022 với công cụ C++.
- CMake.
- Qt6 bản tương thích với MSVC.

Mở Developer PowerShell hoặc Developer Command Prompt
tại thư mục gốc dự án.

Thay đường dẫn Qt bằng phiên bản đã cài trên máy:

```bat
cmake -S RAMSimulator -B RAMSimulator/ket_qua_bien_dich -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/6.x.y/msvc2022_64"

cmake --build RAMSimulator/ket_qua_bien_dich --config Release

ctest --test-dir RAMSimulator/ket_qua_bien_dich -C Release --output-on-failure
```

Đường dẫn `6.x.y` chỉ là ví dụ, phải thay bằng phiên bản Qt thực tế.

File chạy dự kiến:

```text
RAMSimulator/ket_qua_bien_dich/Release/mo_phong_bo_nho_giao_dien.exe
```

Chưa khẳng định bản Windows PASS khi chưa biên dịch,
chạy và kiểm thử trên Windows.

## 5. Chạy trên Linux

Cần trình biên dịch C++17, CMake và Qt6 Widgets.

Tại thư mục gốc dự án:

```bash
cmake -S RAMSimulator -B RAMSimulator/ket_qua_bien_dich
cmake --build RAMSimulator/ket_qua_bien_dich
ctest --test-dir RAMSimulator/ket_qua_bien_dich --output-on-failure
```

Việc chạy trên Linux cũng cần được xác nhận bằng kiểm thử thực tế.

## 6. Phân biệt mã nguồn mới và cũ

Phiên bản C++17 và Qt6 sử dụng `CMakeLists.txt` trong RAMSimulator.

Repository vẫn giữ một số file `.sln`, `.vcxproj` và nguồn C++
cũ để bảo toàn công việc đã có của nhóm.

Các file Visual Studio cũ có thể không tự động chứa
những thành phần mới của Dashboard Qt.

Không xóa những file cũ trước khi nhóm thống nhất
phương án chuyển đổi hoàn toàn.

## 7. Nguyên tắc bàn giao

- Giữ mã nguồn C++17 và CMake.
- Giữ thư mục `giao_dien`, `include`, `src`, `tests`.
- Không đưa thư mục kết quả biên dịch lên GitHub.
- Không đưa file sao lưu cá nhân lên GitHub.
- Không xóa lịch sử Git của nhóm.
- Kiểm thử trên Windows trước khi công bố hỗ trợ Windows hoàn chỉnh.
