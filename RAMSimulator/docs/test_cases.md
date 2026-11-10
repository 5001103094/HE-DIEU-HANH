# BỘ TEST CASE DÙNG CHUNG CHO CÁC THUẬT TOÁN CẤP PHÁT RAM
**Dự án:** RAMSimulator – Mô phỏng cấp phát RAM (First Fit / Best Fit / Worst Fit)  
**Tác giả chuẩn bị:** Thành viên 2 (TV2)  
**Phạm vi áp dụng:** Dùng chung cho cả 3 thuật toán: First Fit (TV2), Best Fit (TV3), Worst Fit (TV4) và mô-đun tích hợp (TV5).

---

## 1. MỤC TIÊU & NGUYÊN TẮC THIẾT KẾ
1. **Tính độc lập:** Bộ test case được thiết kế độc lập, không ưu tiên riêng bất kỳ thuật toán nào, bảo đảm phản ánh đúng bản chất lý thuyết hệ điều hành.
2. **Bao phủ đầy đủ các kịch bản:**
   - Trường hợp kinh điển (Silberschatz - Sách giáo trình HĐH) cho 3 kết quả khác nhau.
   - Trường hợp vừa khít hoàn toàn (Exact Fit).
   - Trường hợp không đủ dung lượng tổng.
   - Trường hợp một khối lớn chia nhiều lần.
   - Trường hợp hết chỗ giữa chừng.
   - Trường hợp nhiều khối cùng kích thước (kiểm tra tie-break ưu tiên `startKB` nhỏ hơn).
   - Trường hợp phân mảnh ngoài (External Fragmentation: tổng RAM đủ nhưng không có khối liên tục đủ lớn).
   - Các trường hợp biên: danh sách RAM trống rỗng, dung lượng yêu cầu bằng 0, dung lượng âm, mã tiến trình rỗng.
3. **Tính toán thủ công (Manual Trace):** Tất cả kết quả mong đợi đều được tính toán và kiểm tra thủ công từng bước.

---

## 2. BẢNG TỔNG HỢP CÁC TEST CASE

| Mã TC | Tên kịch bản | Khối nhớ ban đầu (id, startKB, freeKB) | Danh sách yêu cầu (pid, requiredKB) | Mục đích kiểm tra |
|---|---|---|---|---|
| **TC01** | Test case kinh điển | H1(0, 100), H2(100, 500), H3(600, 200), H4(800, 300), H5(1100, 600) | P1(212), P2(417), P3(112), P4(426) | 3 thuật toán cho kết quả khác nhau; FF & WF thất bại P4, BF thành công cả 4 |
| **TC02** | Vừa khít hoàn toàn | H1(0, 100), H2(100, 200), H3(300, 300) | P1(100), P2(200), P3(300) | Kiểm tra cấp phát vừa khít (`freeKB = 0`), FF & BF pass hết, WF phân mảnh gây fail P3 |
| **TC03** | Không đủ tổng dung lượng | H1(0, 100), H2(100, 200) | P1(500) | Yêu cầu lớn hơn tổng dung lượng RAM trống |
| **TC04** | Một khối lớn chia liên tiếp | H1(0, 1000) | P1(100), P2(100), P3(100), P4(100) | Kiểm tra việc tách khối và tịnh tiến địa chỉ `startKB` |
| **TC05** | Hết chỗ giữa chừng | H1(0, 50), H2(50, 50), H3(100, 50) | P1(50), P2(50), P3(50), P4(50) | 3 tiến trình đầu thành công, tiến trình thứ 4 thất bại vì hết RAM |
| **TC06** | Các khối bằng nhau (Tie-break) | H1(0, 100), H2(100, 500), H3(600, 100), H4(700, 500) | P1(90), P2(90), P3(90), P4(90) | Kiểm tra quy tắc ưu tiên `startKB` nhỏ nhất khi các khối thỏa mãn có cùng kích thước |
| **TC07** | Danh sách RAM rỗng | (Không có khối nào) | P1(10) | Xử lý an toàn khi không có vùng nhớ nào |
| **TC08** | Yêu cầu bằng 0 | H1(0, 100) | P1(0) | Yêu cầu không hợp lệ, trả về lỗi chuẩn |
| **TC09** | Phân mảnh ngoài | H1(0, 300), H2(400, 100), H3(600, 200) | P1(150), P2(150), P3(150), P4(150) | Tổng RAM đủ 150 KB (100 + 50) nhưng nằm rời rạc |
| **TC10** | Dữ liệu đầu vào âm / rỗng | H1(0, 100) | P1(-50), ""(50) | Xử lý biên giá trị âm hoặc mã tiến trình rỗng |

---

## 3. CHI TIẾT TÍNH TOÁN BẰNG TAY (MANUAL TRACE)

### TC01: Test case kinh điển
- **Bộ nhớ ban đầu:** H1: 100 KB, H2: 500 KB, H3: 200 KB, H4: 300 KB, H5: 600 KB.
- **Yêu cầu:** P1(212), P2(417), P3(112), P4(426).

#### Kết quả First Fit:
| Yêu cầu | Khối được chọn | Trạng thái sau cấp phát | Ghi chú |
|---|---|---|---|
| P1(212) | H2 (500 KB) | H2 còn 288 KB (start=312) | Khối đầu tiên đủ lớn |
| P2(417) | H5 (600 KB) | H5 còn 183 KB (start=1517) | Duyệt qua H1, H2, H3, H4 không đủ; chọn H5 |
| P3(112) | H2 (288 KB) | H2 còn 176 KB (start=424) | H1 ko đủ; H2(288) đủ -> chọn H2 |
| P4(426) | *Không có* | Thất bại (Phân mảnh ngoài) | Các khối còn lại: 100, 176, 200, 300, 183 (ko khối nào >= 426) |

#### Kết quả Best Fit:
| Yêu cầu | Khối được chọn | Trạng thái sau cấp phát | Ghi chú |
|---|---|---|---|
| P1(212) | H4 (300 KB) | H4 còn 88 KB | Khối nhỏ nhất đủ lớn trong các khối 500, 300, 600 |
| P2(417) | H2 (500 KB) | H2 còn 83 KB | Khối nhỏ nhất đủ lớn trong 500, 600 |
| P3(112) | H3 (200 KB) | H3 còn 88 KB | Khối nhỏ nhất đủ lớn trong 200, 600 |
| P4(426) | H5 (600 KB) | H5 còn 174 KB | Khối duy nhất đủ lớn |
*(Tất cả 4 tiến trình đều cấp phát thành công).*

#### Kết quả Worst Fit:
| Yêu cầu | Khối được chọn | Trạng thái sau cấp phát | Ghi chú |
|---|---|---|---|
| P1(212) | H5 (600 KB) | H5 còn 388 KB | Khối lớn nhất |
| P2(417) | H2 (500 KB) | H2 còn 83 KB | Khối lớn nhất còn lại đủ lớn (H5 còn 388 ko đủ) |
| P3(112) | H5 (388 KB) | H5 còn 276 KB | Khối lớn nhất trong các khối đủ |
| P4(426) | *Không có* | Thất bại (Phân mảnh ngoài) | Khối lớn nhất hiện tại chỉ còn 300 KB (H4) |

---

### TC02: Vừa khít hoàn toàn (Exact Fit)
- **Bộ nhớ ban đầu:** H1(0, 100), H2(100, 200), H3(300, 300).
- **Yêu cầu:** P1(100), P2(200), P3(300).
- **First Fit:** P1 chọn H1 (còn 0), P2 chọn H2 (còn 0), P3 chọn H3 (còn 0). Thành công cả 3.
- **Best Fit:** P1 chọn H1 (còn 0), P2 chọn H2 (còn 0), P3 chọn H3 (còn 0). Thành công cả 3.
- **Worst Fit:** 
  - P1(100) chọn khối lớn nhất H3(300) -> H3 còn 200 KB.
  - P2(200) chọn khối lớn nhất: H2(200) và H3(200), tie-break startKB nhỏ hơn -> chọn H2(200) -> H2 còn 0 KB.
  - P3(300) -> Không khối nào đủ >= 300 KB -> **Thất bại!**

---

### TC03: Không đủ tổng dung lượng RAM
- **Bộ nhớ ban đầu:** H1(0, 100), H2(100, 200). Tổng dung lượng = 300 KB.
- **Yêu cầu:** P1(500).
- **Kết quả (cả 3 thuật toán):** Thất bại, `reason = "Khong du tong dung luong RAM trong."`, trạng thái RAM giữ nguyên.

---

### TC04: Một khối lớn chia liên tiếp
- **Bộ nhớ ban đầu:** H1(0, 1000).
- **Yêu cầu:** P1(100), P2(100), P3(100), P4(100).
- **Kết quả (cả 3 thuật toán):**
  - P1 chọn H1: start chuyển thành 100, free còn 900.
  - P2 chọn H1: start chuyển thành 200, free còn 800.
  - P3 chọn H1: start chuyển thành 300, free còn 700.
  - P4 chọn H1: start chuyển thành 400, free còn 600.
  - Thành công cả 4 tiến trình.

---

### TC05: Hết chỗ giữa chừng
- **Bộ nhớ ban đầu:** H1(0, 50), H2(50, 50), H3(100, 50). Tổng = 150 KB.
- **Yêu cầu:** P1(50), P2(50), P3(50), P4(50).
- **Kết quả (cả 3 thuật toán):**
  - P1, P2, P3 lần lượt chiếm trọn H1, H2, H3 (mỗi khối còn 0 KB).
  - P4 yêu cầu 50 KB -> Thất bại do hết RAM (`"Khong du tong dung luong RAM trong."`).

---

### TC06: Các khối bằng nhau & Quy tắc Tie-break
- **Bộ nhớ ban đầu:** H1(0, 100), H2(100, 500), H3(600, 100), H4(700, 500).
- **Yêu cầu:** P1(90), P2(90), P3(90), P4(90).
- **First Fit:**
  - P1(90) chọn H1 (đầu tiên) -> H1 còn 10 KB.
  - P2(90) duyệt gặp H2(500) đủ -> chọn H2 -> H2 còn 410 KB.
  - P3(90) duyệt gặp H2(410) đủ -> chọn H2 -> H2 còn 320 KB.
  - P4(90) duyệt gặp H2(320) đủ -> chọn H2 -> H2 còn 230 KB.
- **Best Fit:**
  - P1(90) chọn H1 (nhỏ nhất đủ, tie-break H1 vs H3 ưu tiên startKB=0) -> H1 còn 10 KB.
  - P2(90) chọn H3 (nhỏ nhất đủ là 100 KB) -> H3 còn 10 KB.
  - P3(90) chọn H2 (nhỏ nhất đủ giữa H2(500) và H4(500), ưu tiên startKB=100) -> H2 còn 410 KB.
  - P4(90) chọn H2 (nhỏ nhất đủ: H2(410) < H4(500)) -> H2 còn 320 KB.
- **Worst Fit:**
  - P1(90) chọn H2 (lớn nhất giữa H2(500) và H4(500), tie-break startKB=100) -> H2 còn 410 KB.
  - P2(90) chọn H4 (lớn nhất là 500 KB) -> H4 còn 410 KB.
  - P3(90) chọn H2 (lớn nhất giữa H2(410) và H4(410), tie-break startKB=100) -> H2 còn 320 KB.
  - P4(90) chọn H4 (lớn nhất là 410 KB) -> H4 còn 320 KB.

---

### TC07: Danh sách RAM rỗng
- **Bộ nhớ ban đầu:** `{}`.
- **Yêu cầu:** P1(10).
- **Kết quả:** Thất bại, `"Khong du tong dung luong RAM trong."`, không crash.

---

### TC08: Yêu cầu bằng 0
- **Bộ nhớ ban đầu:** H1(0, 100).
- **Yêu cầu:** P1(0).
- **Kết quả:** Thất bại, `"Yeu cau cap phat khong hop le."`, trạng thái RAM giữ nguyên.

---

### TC09: Phân mảnh ngoài (External Fragmentation)
- **Bộ nhớ ban đầu:** H1(0, 300), H2(400, 100), H3(600, 200). Tổng dung lượng = 600 KB.
- **Yêu cầu:** P1(150), P2(150), P3(150), P4(150).
- **First Fit:**
  - P1(150) chọn H1(300) -> H1 còn 150 KB.
  - P2(150) chọn H1(150) -> H1 còn 0 KB.
  - P3(150) chọn H3(200) -> H3 còn 50 KB.
  - RAM còn lại: H1(0), H2(100), H3(50). Tổng RAM trống = 150 KB.
  - P4(150) cần 150 KB -> **Thất bại** do không có khối đơn lẻ nào đủ 150 KB.
  - Lý do: `"Phan manh ngoai: khong co vung RAM lien tuc du lon."`.

---

### TC10: Trường hợp biên (Dung lượng âm hoặc mã tiến trình rỗng)
- **Bộ nhớ ban đầu:** H1(0, 100).
- **Yêu cầu:** P1(-50) và ""(50).
- **Kết quả:** Đều thất bại với lý do `"Yeu cau cap phat khong hop le."`, trạng thái RAM không đổi.

