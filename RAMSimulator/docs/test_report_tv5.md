# BÁO CÁO KIỂM THỬ – TV5

## 1. Mục đích

Kiểm tra khả năng biên dịch và hoạt động của các module trong chương trình mô phỏng cấp phát RAM bằng ba thuật toán First Fit, Best Fit và Worst Fit.

Đánh giá chức năng nhập dữ liệu, kiểm tra tính hợp lệ, thực hiện cấp phát RAM, thống kê kết quả và so sánh ba thuật toán.

Ghi nhận kết quả kiểm thử riêng và kiểm thử tích hợp, làm cơ sở cho quá trình nghiệm thu toàn hệ thống.

## 2. Môi trường kiểm thử

- Ngôn ngữ: C++17.
- Hệ điều hành kiểm thử: macOS.
- Công cụ lập trình: Visual Studio Code.
- Trình biên dịch: Apple Clang 21.0.0.
- Nhánh kiểm thử tích hợp: `test/tv5-integration`.
- Nhánh phát triển TV5: `feature/tv5-console-integration`.
- Môi trường triển khai chính của nhóm: Visual Studio 2022 trên Windows.

## 3. Kết quả kiểm thử riêng

| Thành phần | Số bài kiểm thử | Kết quả |
|---|---:|---|
| Memory – TV1 | 7 | 7/7 PASS |
| First Fit – TV2 | 10 | 10/10 PASS |
| Best Fit – TV3 | 6 | 6/6 PASS |
| Trace – TV3 | 2 | 2/2 PASS |
| Worst Fit – TV4 | 9 | 9/9 PASS |
| **Tổng cộng** | **34** | **34/34 PASS** |

Các bài kiểm thử được biên dịch và chạy bằng Clang với chuẩn C++17 trên macOS.

Toàn bộ 34 bài kiểm thử riêng đều đạt yêu cầu. Không ghi nhận lỗi biên dịch, liên kết hoặc trường hợp kiểm thử thất bại trong các lần chạy được báo cáo.

Kết quả này xác nhận các module đã vượt qua những trường hợp kiểm thử riêng tương ứng, chưa thay thế cho nghiệm thu toàn hệ thống.

## 4. Kiểm tra tích hợp

### 4.1. Biên dịch chương trình tích hợp

Đã biên dịch và khởi chạy thành công chương trình Console trên macOS bằng chuẩn C++17.

Các thành phần được liên kết gồm:

- Module quản lý RAM.
- Module nhập và kiểm tra dữ liệu.
- Thuật toán First Fit.
- Thuật toán Best Fit.
- Thuật toán Worst Fit.
- Module Trace.
- Chương trình điều khiển Menu Console.

Kết quả: **PASS**.

Chương trình hiển thị đầy đủ menu từ lựa chọn 0 đến 6 và cho phép thực hiện các chức năng cấp phát RAM, thống kê và so sánh thuật toán.

### 4.2. Kiểm thử cấp phát RAM thành công

Dữ liệu kiểm thử:

| Vùng RAM | Địa chỉ bắt đầu (KB) | Dung lượng (KB) |
|---|---:|---:|
| H1 | 0 | 100 |
| H2 | 200 | 250 |
| H3 | 500 | 400 |

Tiến trình P1 yêu cầu cấp phát 250 KB.

Kết quả thực tế:

| Thuật toán | Vùng được chọn | Thành công | Thất bại | RAM trống còn lại (KB) |
|---|---|---:|---:|---:|
| First Fit | H2 | 1 | 0 | 500 |
| Best Fit | H2 | 1 | 0 | 500 |
| Worst Fit | H3 | 1 | 0 | 500 |

Chương trình lựa chọn đúng vùng RAM theo nguyên tắc của từng thuật toán.

Đồng thời, chức năng so sánh hiển thị chính xác số lần cấp phát thành công, thất bại, tổng RAM trống và vùng trống lớn nhất.

Kết quả: **PASS**.

### 4.3. Kiểm thử hiện tượng phân mảnh ngoài

Dữ liệu kiểm thử:

| Vùng RAM | Địa chỉ bắt đầu (KB) | Dung lượng (KB) |
|---|---:|---:|
| H1 | 0 | 100 |
| H2 | 200 | 150 |
| H3 | 500 | 200 |

Tiến trình P1 yêu cầu cấp phát 250 KB.

Tổng RAM trống là 450 KB nhưng vùng trống liên tục lớn nhất chỉ có 200 KB.

Kết quả thực tế:

| Thuật toán | Thành công | Thất bại | Tổng RAM trống (KB) | Vùng lớn nhất (KB) |
|---|---:|---:|---:|---:|
| First Fit | 0 | 1 | 450 | 200 |
| Best Fit | 0 | 1 | 450 | 200 |
| Worst Fit | 0 | 1 | 450 | 200 |

Cả ba thuật toán đều từ chối cấp phát và hiển thị nguyên nhân không có vùng RAM liên tục đủ lớn.

Bảng so sánh thống kê chính xác các kết quả thất bại.

Kết quả: **PASS**.

### 4.4. Kiểm thử nhiều tiến trình – TC01

Dữ liệu gồm 6 vùng RAM trống có dung lượng lần lượt:

300 KB, 600 KB, 350 KB, 200 KB, 750 KB và 125 KB.

Năm yêu cầu cấp phát có dung lượng lần lượt:

115 KB, 500 KB, 358 KB, 200 KB và 375 KB.

Kết quả thực tế:

| Thuật toán | Thành công | Thất bại | RAM trống còn lại (KB) |
|---|---:|---:|---:|
| First Fit | 5 | 0 | 777 |
| Best Fit | 5 | 0 | 777 |
| Worst Fit | 4 | 1 | 1152 |

Kết quả cấp phát và thống kê phù hợp với dự kiến của bộ dữ liệu TC01.

Trong lần chạy này có mã tiến trình được nhập chưa đúng quy ước. Vì vậy, cần chạy lại TC01 với mã P1–P5 hợp lệ trên bản tích hợp có cập nhật kiểm tra PID trước khi xác nhận nghiệm thu đầy đủ TC01.

Trạng thái: **Đạt kết quả thuật toán dự kiến, chờ xác nhận nghiệm thu đầy đủ**.

### 4.5. Kiểm thử ràng buộc mã tiến trình

Đã bổ sung kiểm tra định dạng mã tiến trình trong file `src/input.cpp`.

Quy tắc: Mã tiến trình phải bắt đầu bằng chữ P viết hoa, theo sau là số nguyên dương không có số 0 đứng đầu.

Các trường hợp đã kiểm tra:

- Chấp nhận mã hợp lệ như P1 và P2.
- Từ chối mã không đúng định dạng như PP và P0.
- Không chấp nhận hai tiến trình có mã trùng nhau.
- Yêu cầu người dùng nhập lại khi mã không hợp lệ.

Kết quả kiểm thử chức năng nhập PID trên nhánh `feature/tv5-console-integration`: **PASS**.

Bản sửa đã được Commit và Push lên GitHub, cập nhật trong Pull Request #6 với Commit `52ae4a7`.

Cần kiểm tra lại chức năng này trên bản tích hợp cuối cùng sau khi hợp nhất các thay đổi.

### 4.6. Các nội dung chưa hoàn thành

- Chưa hoàn tất nghiệm thu đầy đủ bộ TC01–TC08 trên bản tích hợp cuối cùng.
- Chưa xác nhận Build thành công bằng MSVC trong Visual Studio 2022 trên Windows.
- Chưa hoàn tất xác nhận tích hợp các thay đổi mới nhất từ tất cả thành viên trên cùng một phiên bản chính thức.

## 5. Đánh giá và kết luận

Các module Memory, First Fit, Best Fit, Worst Fit và Trace đã vượt qua tổng cộng **34/34 bài kiểm thử riêng** trên macOS bằng C++17.

Chương trình tích hợp đã biên dịch và chạy thành công trên macOS. Các trường hợp kiểm thử cấp phát thành công, cấp phát thất bại do phân mảnh ngoài và thống kê so sánh ba thuật toán đều cho kết quả chính xác.

Trường hợp TC01 cho kết quả thuật toán phù hợp với dự kiến. Chức năng kiểm tra định dạng mã tiến trình đã được bổ sung và kiểm thử trên nhánh phát triển của TV5.

Tuy nhiên, kết quả hiện tại chưa đủ để kết luận nghiệm thu toàn hệ thống. Nhóm cần tiếp tục kiểm thử trên bản tích hợp cuối cùng và xác nhận khả năng Build bằng Visual Studio 2022 trên Windows.

## 6. Công việc tiếp theo

- Hoàn thiện kiểm thử tích hợp với mã nguồn mới nhất của các thành viên.
- Chạy lại TC01 và tiếp tục nghiệm thu đầy đủ TC01–TC08.
- Kiểm tra chức năng nhập PID trên bản tích hợp cuối cùng.
- Phối hợp TV1 cập nhật cấu hình `.vcxproj` và `.vcxproj.filters` khi cần thiết.
- Xác nhận Build và chạy chương trình trên Visual Studio 2022.
- Tổng hợp kết quả nghiệm thu cuối cùng và bàn giao cho nhóm.

**Trạng thái CV05: Đang thực hiện – Đã hoàn thành 34/34 bài kiểm thử riêng và các trường hợp kiểm thử tích hợp được ghi nhận. Chờ nghiệm thu cuối cùng trên Windows.**