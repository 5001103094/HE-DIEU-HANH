# TÀI LIỆU PHÂN TÍCH THUẬT TOÁN FIRST FIT VÀ BÁO CÁO KIỂM TRA CHÉO (CV05)

**Dự án:** RAMSimulator – Mô phỏng cấp phát RAM liên tục (Contiguous Memory Allocation)  
**Thành viên thực hiện:** Thành viên 2 (TV2)  
**Phụ trách:** Thuật toán First Fit (`first_fit.cpp`), Bộ test case dùng chung (`docs/test_cases.md`), Kiểm thử First Fit (`tests/test_first_fit.cpp`), và Kiểm tra chéo Best Fit (TV3).

---

## PHẦN 1. PHÂN TÍCH CHI TIẾT THUẬT TOÁN FIRST FIT

### 1. Khái niệm thuật toán First Fit
First Fit là một trong ba chiến lược kinh điển được sử dụng để giải quyết bài toán lựa chọn phân vùng bộ nhớ trống (Dynamic Storage Allocation Problem) trong cơ chế cấp phát bộ nhớ liên tục (Contiguous Memory Allocation), bên cạnh Best Fit và Worst Fit.

Theo tài liệu chuẩn quốc tế *Operating System Concepts* (Silberschatz, Galvin & Gagne – Mục 9.2.2):
> **First Fit:** Cấp phát vùng nhớ trống **đầu tiên** tìm thấy có kích thước đủ lớn để chứa tiến trình yêu cầu. Quá trình tìm kiếm có thể bắt đầu từ đầu danh sách các vùng trống hoặc bắt đầu từ vị trí vừa kết thúc của lần tìm kiếm trước (Next Fit). Trong dự án này, nhóm thống nhất triển khai theo chuẩn First Fit bắt đầu từ đầu danh sách (địa chỉ thấp nhất đến cao nhất).

Chiến lược này có đặc điểm nổi bật là **dừng tìm kiếm ngay lập tức** khi tìm thấy vùng nhớ thỏa mãn đầu tiên, giúp giảm thiểu tối đa số lần duyệt và thời gian tìm kiếm.

---

### 2. Nguyên lý hoạt động
Trong mô hình phân vùng có kích thước thay đổi (*Variable-Partition Scheme*), hệ điều hành duy trì một danh sách các vùng nhớ RAM còn trống (`Hole`).

Khi nhận được yêu cầu cấp phát từ một tiến trình với kích thước `requiredKB`, thuật toán First Fit tiến hành các bước sau:

1. **Bước 1. Tiếp nhận và kiểm tra yêu cầu:**
   - Xác định mã tiến trình (`pid`) và dung lượng yêu cầu (`requiredKB`).
   - Nếu yêu cầu không hợp lệ (`pid` rỗng hoặc `requiredKB <= 0`), từ chối cấp phát ngay lập tức và trả về nguyên nhân lỗi chuẩn mực.
2. **Bước 2. Duyệt tìm kiếm vùng nhớ:**
   - Duyệt tuần tự danh sách các vùng nhớ trống theo thứ tự địa chỉ từ thấp đến cao (`startKB` tăng dần).
   - Kiểm tra điều kiện: `hole.freeKB >= request.requiredKB`.
3. **Bước 3. Lựa chọn và dừng tìm kiếm:**
   - Ngay khi gặp vùng trống **đầu tiên** thỏa mãn điều kiện trên, thuật toán chọn vùng này và **dừng duyệt ngay lập tức** (sử dụng lệnh `break`).
4. **Bước 4. Thực hiện cấp phát & tách khối:**
   - Tiến trình được cấp phát từ đầu vùng nhớ trống đã chọn.
   - Nếu kích thước vùng lớn hơn yêu cầu: vùng được chia làm 2 phần (phần cấp phát cho tiến trình và phần dư tiếp tục là vùng trống với `startKB = startKB + requiredKB` và `freeKB = freeKB - requiredKB`).
   - Nếu kích thước vừa khít (`freeKB == requiredKB`): toàn bộ vùng được cấp phát, `freeKB` trở về `0`. Theo quy ước triển khai của nhóm, vùng nhớ này vẫn được giữ trong danh sách với `freeKB = 0` và sẽ bị bỏ qua ở các lượt cấp phát sau.
5. **Bước 5. Xử lý khi không tìm thấy khối thỏa mãn:**
   - Nếu duyệt hết danh sách mà không có vùng trống nào đủ lớn, yêu cầu bị từ chối cấp phát.
   - Trạng thái RAM được giữ nguyên toàn vẹn và trả về nguyên nhân cụ thể (không đủ tổng RAM hay do phân mảnh ngoài).

---

### 3. Ví dụ minh họa từng bước thuật toán First Fit
Xét bộ nhớ RAM gồm các vùng trống ban đầu:
- **H1:** `start = 0 KB`, `free = 100 KB`
- **H2:** `start = 100 KB`, `free = 500 KB`
- **H3:** `start = 600 KB`, `free = 200 KB`
- **H4:** `start = 800 KB`, `free = 300 KB`
- **H5:** `start = 1100 KB`, `free = 600 KB`

Giả sử có 4 yêu cầu cấp phát lần lượt: P1 (212 KB), P2 (417 KB), P3 (112 KB), P4 (426 KB).

| Lượt | Tiến trình | Khối duyệt qua | Khối được chọn | Trạng thái sau cấp phát |
|:---:|:---:|---|:---:|---|
| 1 | **P1 (212 KB)** | - H1(100): không đủ<br>- **H2(500): ĐỦ** | **H2** | H2 còn: `start = 312`, `free = 288 KB`. Dừng duyệt ngay. |
| 2 | **P2 (417 KB)** | - H1(100): không đủ<br>- H2(288): không đủ<br>- H3(200): không đủ<br>- H4(300): không đủ<br>- **H5(600): ĐỦ** | **H5** | H5 còn: `start = 1517`, `free = 183 KB`. Dừng duyệt ngay. |
| 3 | **P3 (112 KB)** | - H1(100): không đủ<br>- **H2(288): ĐỦ** | **H2** | H2 còn: `start = 424`, `free = 176 KB`. Dừng duyệt ngay. |
| 4 | **P4 (426 KB)** | - Duyệt H1(100), H2(176), H3(200), H4(300), H5(183) | *Không có* | **Thất bại.** Không có khối nào đủ 426 KB (Dù tổng RAM trống còn 959 KB). |

---

### 4. Hiện tượng phân mảnh ngoài (External Fragmentation) trong First Fit
Phân mảnh ngoài xảy ra khi tổng không gian nhớ trống đủ để thỏa mãn một yêu cầu cấp phát, nhưng các vùng trống bị chia nhỏ và nằm rải rác, không có một vùng liên tục đơn lẻ nào đủ lớn.

Như minh họa ở lượt 4 phía trên:
- Tổng dung lượng RAM trống còn lại: $100 + 176 + 200 + 300 + 183 = 959\text{ KB} > 426\text{ KB}$.
- Nhưng khối lớn nhất chỉ là $300\text{ KB} < 426\text{ KB}$.
- **Hệ quả:** P4 không thể cấp phát được do phân mảnh ngoài. Hàm First Fit chẩn đoán chuẩn xác lỗi này qua hàm `allocationFailureReason()` của TV1.

---

### 5. So sánh First Fit với Best Fit và Worst Fit

| Tiêu chí | First Fit (TV2) | Best Fit (TV3) | Worst Fit (TV4) |
|---|---|---|---|
| **Chiến lược chọn** | Khối đầu tiên đủ lớn | Khối nhỏ nhất đủ lớn | Khối lớn nhất |
| **Phạm vi duyệt** | Dừng ngay khi tìm thấy ($O(1)$ tốt nhất, $O(N)$ tệ nhất) | Duyệt toàn bộ danh sách ($O(N)$) | Duyệt toàn bộ danh sách ($O(N)$) |
| **Tốc độ thực thi** | **Nhanh nhất** | Chậm hơn | Chậm hơn |
| **Phần dư để lại** | Ngẫu nhiên tùy vị trí | Rất nhỏ (dễ gây phân mảnh nhỏ) | Rất lớn (phần dư còn có thể dùng tiếp) |
| **Khả năng phân mảnh ngoài** | Có | Có | Có |

*Nhận xét từ giáo trình:* Về mặt lý thuyết và thực nghiệm mô phỏng, First Fit và Best Fit nhìn chung đều vượt trội hơn Worst Fit về cả thời gian lẫn tỉ lệ tận dụng không gian nhớ. Giữa First Fit và Best Fit, First Fit thường có tốc độ thực thi nhanh hơn rõ rệt.

---

## PHẦN 2. MÔ TẢ TRIỂN KHAI MÃ NGUỒN `first_fit.cpp`

Hàm `firstFit()` được cài đặt tại `RAMSimulator/first_fit.cpp` với cấu trúc rõ ràng, tuân thủ chặt chẽ chữ ký hàm trong `include/allocators.hpp`:

```cpp
AllocationResult firstFit(
    MemoryState& memory,
    const Request& request
) {
    AllocationResult result;
    result.pid = request.pid;

    // Buoc 1: Kiem tra tinh hop le cua yeu cau cap phat
    if (request.pid.empty() || request.requiredKB <= 0) {
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // Buoc 2: Khoi tao vi tri vung nho tim duoc
    std::size_t foundIndex = memory.size();

    // Buoc 3: Duyet tuan tu tu dau danh sach (dia chi thap den cao)
    for (std::size_t i = 0; i < memory.size(); ++i) {
        if (memory[i].freeKB >= request.requiredKB) {
            foundIndex = i;
            break; // First Fit: chon vung dau tien va dung tim kiem ngay
        }
    }

    // Buoc 4: Neu khong tim thay vung phu hop
    if (foundIndex == memory.size()) {
        result.reason = allocationFailureReason(memory, request);
        return result;
    }

    // Buoc 5: Thuc hien cap phat bang cach goi ham dung chung cua TV1
    return allocateFromHole(memory, foundIndex, request);
}
```

### Các ưu điểm kỹ thuật:
1. **Tái sử dụng triệt để tài nguyên nhóm:** Sử dụng hàm `allocateFromHole()` của TV1 để tự động cập nhật `startKB`, trừ `freeKB` và trả về `AllocationResult` hợp lệ.
2. **Chẩn đoán nguyên nhân lỗi nhất quán:** Sử dụng hàm `allocationFailureReason()` của TV1 để trả về chuỗi thông báo lỗi chuẩn xác giữa trường hợp không đủ tổng RAM và phân mảnh ngoài.
3. **An toàn tối đa:** Không sử dụng con trỏ thô, duyệt mảng an toàn qua `std::size_t`, không bao giờ xảy ra lỗi truy cập ngoài mảng hay crash chương trình.

---

## PHẦN 3. BÁO CÁO KIỂM TRA CHÉO (CROSS-CHECK) CODE BEST FIT CỦA TV3

Là một phần trong nhiệm vụ CV05, TV2 đã tiến hành rà soát mã nguồn (code review) và kiểm thử độc lập đối với mô-đun của TV3 (`best_fit.cpp`, `trace.cpp`, `test_best_fit.cpp`).

### 1. Đánh giá mã nguồn `RAMSimulator/best_fit.cpp`
- **Chữ ký hàm:** `AllocationResult bestFit(MemoryState& memory, const Request& request)` hoàn toàn khớp với khai báo trong `include/allocators.hpp`.
- **Logic thuật toán:**
  - Thuật toán duyệt qua toàn bộ danh sách `memory` và tìm khối thỏa mãn có `freeKB` nhỏ nhất.
  - **Quy tắc Tie-break:** TV3 đã cài đặt chuẩn xác điều kiện:
    ```cpp
    if (bestIndex == memory.size() ||
        hole.freeKB < memory[bestIndex].freeKB ||
        (hole.freeKB == memory[bestIndex].freeKB &&
            hole.startKB < memory[bestIndex].startKB)) {
        bestIndex = i;
    }
    ```
    Điều này bảo đảm khi hai khối có cùng kích thước nhỏ nhất thỏa mãn, thuật toán luôn ưu tiên chọn khối có `startKB` nhỏ hơn theo đúng quy ước chung của nhóm.
- **Tích hợp:** TV3 cũng tái sử dụng đúng đắn `allocateFromHole()` và `allocationFailureReason()` của TV1.
- **Xử lý biên:** Kiểm tra đầu vào âm/rỗng ngay từ đầu hàm rất an toàn.

### 2. Đánh giá mô-đun `RAMSimulator/trace.cpp`
- Hàm `printBestFitTrace()` hiển thị đầy đủ, trực quan:
  - Trạng thái các khối RAM trước cấp phát kèm đánh dấu `DU` hoặc `KHONG DU`.
  - Kết quả lựa chọn (vùng chọn, khoảng địa chỉ đã cấp `[start, start + size)`, dung lượng còn lại).
  - Trạng thái RAM sau cấp phát.
- Hàm thuần túy hiển thị ra luồng `std::ostream&`, hoàn toàn không làm sai lệch hay thay đổi trạng thái RAM.

### 3. Kết quả kiểm thử chéo Best Fit trên bộ test case chung
TV2 đã đưa mã nguồn `bestFit()` của TV3 vào chạy kiểm thử với bộ test case chung (bao gồm cả trường hợp kinh điển TC01, vừa khít TC02, tie-break TC06, phân mảnh ngoài TC09):
- **Kết quả:** Code của TV3 hoạt động hoàn hảo, cho kết quả khớp 100% với tính toán manual trace trong tài liệu `docs/test_cases.md`.
- **Độ ổn định:** Không phát sinh bất kỳ lỗi rò rỉ bộ nhớ, crash, hay lỗi biên dịch nào (`0 Warning(s), 0 Error(s)`).

### 4. Kết luận kiểm tra chéo
Mô-đun Best Fit của TV3 đạt chất lượng xuất sắc, tuân thủ nghiêm ngặt các quy ước kiến trúc của nhóm, hoàn toàn sẵn sàng để TV5 ghép nối vào chương trình chính.

