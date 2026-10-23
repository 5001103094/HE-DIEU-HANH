# BÁO CÁO KIỂM THỬ – TV5

## 1. Mục đích

Kiểm tra khả năng biên dịch và hoạt động của các module trong chương trình mô phỏng cấp phát RAM bằng ba thuật toán First Fit, Best Fit và Worst Fit.

Ghi nhận kết quả kiểm thử riêng, làm cơ sở cho quá trình kiểm thử tích hợp toàn hệ thống.

## 2. Môi trường kiểm thử

- Ngôn ngữ: C++17.
- Hệ điều hành kiểm thử: macOS.
- Công cụ lập trình: Visual Studio Code.
- Trình biên dịch: Apple Clang 21.0.0.
- Nhánh kiểm thử: `test/tv5-integration`.
- Môi trường triển khai chính của nhóm: Visual Studio 2022 trên Windows.

## 3. Kết quả kiểm thử

| Thành phần | Số bài kiểm thử | Kết quả |
|---|---:|---|
| Memory – TV1 | 7 | 7/7 PASS |
| First Fit – TV2 | 10 | 10/10 PASS |
| Best Fit – TV3 | 6 | 6/6 PASS |
| Trace – TV3 | 2 | 2/2 PASS |
| **Tổng cộng** | **25** | **25/25 PASS** |

Các bài kiểm thử được biên dịch và chạy bằng Clang với chuẩn C++17 trên macOS.

Kết quả không ghi nhận lỗi biên dịch, liên kết hoặc lỗi kiểm thử trong các lần chạy được báo cáo.

## 4. Kiểm tra tích hợp

### 4.1. Các nội dung đã kiểm tra

- Kiểm tra cú pháp C++17 của First Fit và Best Fit.
- Kiểm thử riêng các thuật toán First Fit và Best Fit với module quản lý RAM.
- Kiểm thử riêng chức năng Trace.
- Kiểm thử module quản lý RAM.
- Kiểm tra cấu hình chuẩn C++17 trong tệp `.vcxproj`.
- Kiểm tra các tệp mã nguồn đã được khai báo trong `.vcxproj` và `.vcxproj.filters`.

### 4.2. Các nội dung chưa hoàn thành

- Chưa kiểm thử Worst Fit của TV4.
- Chưa chạy đầy đủ bộ nghiệm thu tích hợp TC01–TC08 của nhóm.
- Chưa xác nhận chương trình tích hợp Build thành công bằng MSVC trên Visual Studio 2022.
- Chưa nghiệm thu toàn bộ menu và chức năng so sánh trên bản tích hợp hoàn chỉnh.

## 5. Đánh giá và kết luận

Các module Memory, First Fit, Best Fit và Trace đã vượt qua tổng cộng 25/25 bài kiểm thử riêng trên macOS bằng C++17.

Kết quả cho thấy những thành phần đã kiểm tra hoạt động đúng với các trường hợp kiểm thử tương ứng.

Tuy nhiên, chương trình chưa đủ điều kiện kết luận nghiệm thu tích hợp toàn hệ thống do còn thiếu bước kiểm thử Worst Fit và xác nhận Build trên Visual Studio 2022.

## 6. Công việc tiếp theo

- Tiếp nhận mã nguồn Worst Fit từ TV4.
- Phối hợp TV1 hoàn thiện cấu hình dự án Visual Studio 2022.
- Biên dịch và chạy chương trình tích hợp đầy đủ.
- Thực hiện bộ nghiệm thu TC01–TC08.
- Bổ sung kết quả vào báo cáo trước khi nghiệm thu cuối cùng.

**Trạng thái CV05: Đang thực hiện – Đã hoàn thành kiểm thử riêng 25/25 bài.**