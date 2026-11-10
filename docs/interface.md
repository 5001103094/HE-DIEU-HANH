
# Mô tả cấu trúc dữ liệu và các hàm chung - TV1

## 1. Cấu trúc dữ liệu

Các cấu trúc được khai báo trong include/models.hpp.

- Hole: Lưu mã vùng RAM (id), địa chỉ bắt đầu (startKB) và dung lượng trống (freeKB).
- Request: Lưu mã tiến trình (pid) và dung lượng RAM yêu cầu (requiredKB).
- AllocationResult: Lưu mã tiến trình, trạng thái thành công, mã vùng được chọn, dung lượng còn lại và nguyên nhân thất bại.
- MemoryState: Danh sách các vùng RAM trống, được biểu diễn bằng vector<Hole>.

## 2. Khai báo thuật toán

File include/allocators.hpp khai báo ba hàm:

- firstFit: Chọn vùng RAM đầu tiên đủ lớn.
- bestFit: Chọn vùng RAM nhỏ nhất nhưng đủ lớn.
- worstFit: Chọn vùng RAM lớn nhất trong các vùng đủ lớn.

Ba thuật toán do TV2, TV3 và TV4 phụ trách cài đặt.

## 3. Các hàm quản lý bộ nhớ

Các hàm được khai báo trong include/memory.hpp và cài đặt trong src/memory.cpp.

- totalFreeKB: Tính tổng dung lượng RAM còn trống.
- largestHoleKB: Tìm dung lượng vùng RAM trống lớn nhất.
- copyMemory: Tạo bản sao độc lập của trạng thái RAM.
- allocationFailureReason: Xác định nguyên nhân cấp phát thất bại, gồm yêu cầu không hợp lệ, thiếu tổng RAM hoặc phân mảnh ngoài.
- allocateFromHole: Cấp phát RAM từ vùng được chọn, cập nhật địa chỉ bắt đầu và dung lượng trống còn lại.

Hàm allocateFromHole nhận chỉ số vùng RAM, không phải mã vùng RAM. Khi cấp phát thất bại, hàm không thay đổi trạng thái bộ nhớ.

## 4. Nguyên tắc sử dụng chung

Ba thuật toán First Fit, Best Fit và Worst Fit phải sử dụng các bản sao độc lập từ dữ liệu RAM ban đầu.

Các thuật toán sử dụng cấu trúc dữ liệu và hàm chung do TV1 cung cấp để tránh trùng lặp xử lý cấp phát.

## 5. Kiểm thử

File tests/test_memory.cpp kiểm tra các hàm quản lý bộ nhớ bằng assert.

Các trường hợp kiểm thử gồm tính tổng RAM, tìm vùng lớn nhất, sao chép dữ liệu, cập nhật sau cấp phát, phát hiện phân mảnh ngoài và xử lý yêu cầu không hợp lệ.
