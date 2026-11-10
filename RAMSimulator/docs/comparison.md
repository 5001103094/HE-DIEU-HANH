
# SO SÁNH THUẬT TOÁN CẤP PHÁT RAM

## 1. Mục đích

Tài liệu trình bày nguyên tắc hoạt động của ba thuật toán
First Fit, Best Fit và Worst Fit, đồng thời phân tích
kết quả mô phỏng cấp phát RAM cho nhiều tiến trình.

## 2. Nguyên tắc hoạt động

### First Fit
Duyệt danh sách vùng trống và chọn vùng đầu tiên
có đủ dung lượng đáp ứng yêu cầu.

### Best Fit
Chọn vùng có dung lượng nhỏ nhất trong số các vùng
đủ lớn để cấp phát cho tiến trình.

### Worst Fit
Chọn vùng có dung lượng lớn nhất trong số các vùng
đủ lớn để cấp phát cho tiến trình.

Nếu nhiều vùng có cùng dung lượng lớn nhất,
ưu tiên vùng có địa chỉ bắt đầu startKB nhỏ nhất.

## 3. Các chỉ số so sánh

- Số tiến trình cấp phát thành công.
- Số tiến trình cấp phát thất bại.
- Tổng dung lượng RAM còn trống.
- Dung lượng vùng trống lớn nhất.

Ba thuật toán phải sử dụng các bản sao độc lập
của cùng một trạng thái RAM ban đầu.

## 4. Kết quả tính tay TC01

Các vùng trống ban đầu (KB):
300, 600, 350, 200, 750, 125.

Các tiến trình yêu cầu (KB):
115, 500, 358, 200, 375.

| Thuật toán | Thành công | Thất bại | Tổng RAM trống (KB) | Vùng lớn nhất (KB) |
|---|---:|---:|---:|---:|
| First Fit | 5 | 0 | 777 | 200 |
| Best Fit | 5 | 0 | 777 | 350 |
| Worst Fit | 4 | 1 | 1152 | 300 |

## 5. Phân tích kết quả

### First Fit
Cấp phát thành công cả 5 tiến trình.
Thuật toán lựa chọn vùng đủ lớn đầu tiên
theo thứ tự duyệt.

### Best Fit
Cấp phát thành công cả 5 tiến trình.
Thuật toán ưu tiên các vùng có dung lượng
vừa đủ hoặc gần nhất với yêu cầu.

### Worst Fit
Cấp phát thành công 4/5 tiến trình.

Thứ tự chọn vùng:
- P1 (115 KB): H5, còn 635 KB.
- P2 (500 KB): H5, còn 135 KB.
- P3 (358 KB): H2, còn 242 KB.
- P4 (200 KB): H3, còn 150 KB.
- P5 (375 KB): Cấp phát thất bại.

Trước P5, tổng RAM trống là 1152 KB,
nhưng vùng trống lớn nhất chỉ có 300 KB.

Vì tổng RAM trống đủ nhưng không có vùng
liên tục đủ lớn, P5 thất bại do phân mảnh ngoài.

## 6. Kết quả kiểm thử mô-đun TV4

### Thuật toán Worst Fit

Đã biên dịch bằng MSVC với chuẩn C++17.

Kết quả:
- TC01 đến TC06: PASS.
- INVALID: PASS.
- TIE BREAK: PASS.
- INDEPENDENT MEMORY: PASS.

Tổng cộng: 9/9 bài kiểm thử riêng PASS.

### Chức năng so sánh

- CALCULATE STATS: PASS.
- EMPTY RESULTS: PASS.
- NO FREE MEMORY: PASS.

Tổng cộng: 3/3 bài kiểm thử thống kê PASS.

Bảng TC01 đã được kiểm tra bằng số liệu mẫu.
Chưa kiểm thử tích hợp thực tế cả ba thuật toán.

## 7. Nhận xét

Không có thuật toán nào luôn tối ưu trong mọi
trường hợp.

First Fit lựa chọn vùng phù hợp đầu tiên.
Best Fit ưu tiên vùng vừa đủ nhất.
Worst Fit ưu tiên vùng trống lớn nhất.

Trong TC01, First Fit và Best Fit cấp phát được
cả 5 tiến trình, trong khi Worst Fit chỉ cấp phát
được 4 tiến trình.

Kết quả cho thấy việc lựa chọn vùng trống
ảnh hưởng đến khả năng cấp phát cho các
tiến trình tiếp theo và tình trạng phân mảnh ngoài.

## 8. Kết luận

Mô-đun Worst Fit và chức năng thống kê của TV4
đã vượt qua các bài kiểm thử riêng hiện có.

Cần tiếp tục kiểm tra tích hợp với First Fit,
Best Fit và giao diện Console trước khi nghiệm thu
toàn bộ chương trình.
