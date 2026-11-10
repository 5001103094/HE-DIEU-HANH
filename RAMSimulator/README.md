# RAM Simulator – Hướng dẫn sử dụng

## 1. Giới thiệu

Chương trình mô phỏng cấp phát RAM liên tục cho nhiều tiến trình bằng ba thuật toán First Fit, Best Fit và Worst Fit.

Mục đích là quan sát quá trình cấp phát, phát hiện hiện tượng phân mảnh ngoài và so sánh kết quả của ba thuật toán trên cùng dữ liệu ban đầu.

## 2. Môi trường phát triển

- Ngôn ngữ: C++17.
- Môi trường chính: Visual Studio 2022 trên Windows.
- Loại ứng dụng: Console.
- Dự án: `RAMSimulator.sln`.

## 3. Yêu cầu trước khi chạy

Máy tính Windows cần cài đặt Visual Studio 2022 với thành phần **Desktop development with C++** và bộ công cụ MSVC tương ứng.

## 4. Hướng dẫn biên dịch

**Cách 1: Sử dụng Visual Studio 2022**

1. Mở file `RAMSimulator.sln`.
2. Chọn cấu hình `Debug` và nền tảng `x64`.
3. Chọn **Build → Build Solution**.
4. Nếu Build thành công, chọn **Debug → Start Without Debugging** để chạy chương trình.

**Cách 2: Sử dụng build.bat**

1. Mở thư mục `RAMSimulator` trên Windows.
2. Chạy file `build.bat` để biên dịch dự án.
3. Kiểm tra thông báo `BUILD SUCCEEDED` hoặc `BUILD FAILED`.

File `build.bat` chỉ thực hiện biên dịch, không tự khởi chạy chương trình.

## 5. Các chức năng của chương trình

| Lựa chọn | Chức năng |
| --- | --- |
| 1 | Nhập dữ liệu RAM và tiến trình |
| 2 | Chạy thuật toán First Fit |
| 3 | Chạy thuật toán Best Fit |
| 4 | Chạy thuật toán Worst Fit |
| 5 | Chạy cả ba thuật toán |
| 6 | So sánh kết quả cấp phát |
| 0 | Thoát chương trình |

## 6. Quy tắc nhập dữ liệu

- Mỗi vùng RAM có mã vùng, địa chỉ bắt đầu và dung lượng trống tính bằng KB.
- Địa chỉ bắt đầu không được âm.
- Dung lượng RAM và dung lượng yêu cầu của tiến trình phải lớn hơn 0.
- Không chấp nhận mã tiến trình trùng nhau.
- Các vùng RAM trống không được chồng lấn.
- Các vùng được sắp xếp theo địa chỉ bắt đầu tăng dần.

## 7. Nguyên tắc mô phỏng

Mỗi thuật toán được chạy độc lập trên bản sao của cùng trạng thái RAM ban đầu.

Các yêu cầu cấp phát được xử lý theo đúng thứ tự nhập.

Một yêu cầu thất bại do phân mảnh ngoài khi tổng RAM trống vẫn đủ nhưng không tồn tại vùng nhớ liên tục đủ lớn.

## 8. Kiểm thử

Chương trình cần được kiểm thử bằng bộ test case TC01–TC08 trước khi nghiệm thu.

Kết quả biên dịch và kiểm thử cuối cùng phải được xác nhận trên Visual Studio 2022 của nhóm.
