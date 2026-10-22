# CV01. PHÂN TÍCH THUẬT TOÁN BEST FIT VÀ QUY TẮC XỬ LÝ KHI NHIỀU VÙNG CÓ CÙNG KÍCH THƯỚC

## 1. Khái niệm thuật toán Best Fit
Best Fit là một trong ba chiến lược phổ biến để lựa chọn vùng nhớ trống trong cơ chế cấp phát bộ nhớ liên tục (Contiguous Memory Allocation), bên cạnh First Fit và Worst Fit.

Theo mục 9.2.2 – Memory Allocation, thuật toán Best Fit lựa chọn vùng nhớ trống có kích thước nhỏ nhất nhưng vẫn đủ lớn để đáp ứng yêu cầu cấp phát của tiến trình.

Để tìm được vùng nhớ phù hợp, thuật toán phải tìm kiếm toàn bộ danh sách vùng trống, trừ trường hợp danh sách được sắp xếp theo kích thước và có thể xác định đúng vùng phù hợp mà không cần duyệt hết. Với quy tắc xử lý trường hợp bằng nhau của nhóm, việc tìm kiếm còn phải bảo đảm ưu tiên địa chỉ bắt đầu nhỏ nhất.

Chiến lược Best Fit tạo ra phần bộ nhớ còn dư nhỏ nhất tại vùng được lựa chọn trong mỗi lần cấp phát.

## 2. Nguyên lý hoạt động
Trong cơ chế phân vùng có kích thước thay đổi (Variable-Partition Scheme), hệ điều hành quản lý những vùng nhớ đang được sử dụng và những vùng còn trống. Các vùng trống có thể có kích thước khác nhau và nằm tại những vị trí khác nhau trong bộ nhớ.

Khi một tiến trình yêu cầu cấp phát RAM, thuật toán Best Fit thực hiện các bước sau:

**Bước 1. Tiếp nhận yêu cầu cấp phát:** Xác định dung lượng bộ nhớ mà tiến trình cần sử dụng.

**Bước 2. Tìm kiếm các vùng nhớ phù hợp:** Kiểm tra danh sách các vùng nhớ trống để xác định những vùng có kích thước lớn hơn hoặc bằng dung lượng yêu cầu.

Nếu danh sách chưa được sắp xếp theo kích thước, thuật toán cần duyệt toàn bộ danh sách để tìm vùng phù hợp nhỏ nhất. Nếu nhiều vùng có cùng kích thước nhỏ nhất phù hợp, áp dụng quy tắc ưu tiên `startKB` nhỏ nhất của nhóm.

**Bước 3. Lựa chọn vùng nhớ:** Trong các vùng đủ điều kiện, lựa chọn vùng có kích thước nhỏ nhất để cấp phát cho tiến trình.

**Bước 4. Thực hiện cấp phát:**

- Nếu kích thước vùng được chọn bằng đúng dung lượng yêu cầu, toàn bộ vùng đó được cấp phát cho tiến trình.
- Nếu kích thước vùng được chọn lớn hơn dung lượng yêu cầu, vùng nhớ được chia thành hai phần. Một phần được cấp phát cho tiến trình, phần còn lại tiếp tục được quản lý như vùng trống.

**Bước 5. Cập nhật trạng thái bộ nhớ:** Sau khi cấp phát thành công, hệ thống cập nhật thông tin về vùng nhớ đã sử dụng và danh sách các vùng trống còn lại. Theo quy ước triển khai của nhóm, tiến trình được cấp phát từ đầu vùng trống đã chọn. Nếu cấp phát `requiredKB` KB từ vùng có địa chỉ bắt đầu `startKB`, thì phần vùng trống còn lại được cập nhật `startKB = startKB + requiredKB` và `freeKB = freeKB - requiredKB`. Khi `freeKB = 0`, vùng đó không còn dung lượng trống để cấp phát. Cách lưu hoặc xóa bản ghi vùng 0 KB thuộc phần quản lý RAM do TV1 thống nhất.

Nếu không tồn tại vùng trống liên tục đủ lớn, yêu cầu không thể được cấp phát ngay. Ở mục 9.2.2, sách nêu hệ điều hành có thể từ chối tiến trình hoặc đưa tiến trình vào hàng đợi để chờ có bộ nhớ phù hợp. Riêng bài *Programming Project – Contiguous Memory Allocation* (trang P-49) yêu cầu chương trình mô phỏng thông báo lỗi và từ chối yêu cầu nếu không thể cấp phát bộ nhớ. Vì vậy, khi áp dụng theo bài tập lập trình này, chương trình của nhóm trả về kết quả cấp phát thất bại và không thay đổi trạng thái RAM.

## 3. Quy tắc xử lý khi nhiều vùng nhớ có cùng kích thước
Theo nguyên lý Best Fit, vùng nhớ được lựa chọn phải có kích thước nhỏ nhất trong số các vùng đủ đáp ứng yêu cầu cấp phát.

Tuy nhiên, sách không quy định cụ thể cách lựa chọn khi có nhiều vùng nhớ trống cùng kích thước nhỏ nhất và đều đáp ứng yêu cầu.

Để bảo đảm chương trình hoạt động nhất quán, TV1 đã xác nhận quy tắc chung của nhóm như sau:

**Khi có nhiều vùng nhớ trống cùng kích thước nhỏ nhất và đều đáp ứng yêu cầu cấp phát, thuật toán ưu tiên lựa chọn vùng có địa chỉ bắt đầu nhỏ nhất.**

Ví dụ, nếu hai vùng trống H2 và H3 đều có kích thước 20 KB, lần lượt bắt đầu tại vị trí 50 KB và 80 KB, thuật toán lựa chọn H2.

Đây là quy ước triển khai đã được TV1 xác nhận cho chương trình mô phỏng, không phải quy tắc bắt buộc được sách quy định.

## 4. Ví dụ minh họa thuật toán Best Fit
Giả sử phần RAM được mô phỏng có tổng dung lượng 100 KB. Để dễ quan sát, bảng dùng các vị trí tính theo KB từ 0 đến 99; chẳng hạn 0–39 biểu diễn khoảng từ mốc 0 KB đến ngay trước mốc 40 KB (dài 40 KB), không phải 40 địa chỉ byte. Bảng mô tả toàn bộ RAM gồm cả vùng đang sử dụng và vùng trống; riêng danh sách `MemoryState` của thuật toán Best Fit chỉ chứa các vùng trống H1, H2 và H3.

Trạng thái bộ nhớ ban đầu:

| **Vùng nhớ** | **Khoảng vị trí (KB)** | **Kích thước (KB)** | **Trạng thái** |
| ------------ | ----------- | -------------- | -------------- |
| H1           | 0–39        | 40             | Trống          |
| B            | 40–49       | 10             | Đang sử dụng   |
| H2           | 50–69       | 20             | Trống          |
| D            | 70–79       | 10             | Đang sử dụng   |
| H3           | 80–99       | 20             | Trống          |

**Yêu cầu:** Tiến trình P1 cần cấp phát 18 KB bộ nhớ.

### Bước 1. Kiểm tra các vùng nhớ trống
- H1 có kích thước 40, đủ đáp ứng yêu cầu.
- H2 có kích thước 20, đủ đáp ứng yêu cầu.
- H3 có kích thước 20, đủ đáp ứng yêu cầu.

Cả ba vùng đều có khả năng chứa tiến trình P1.

### Bước 2. Lựa chọn vùng nhớ
Theo nguyên lý Best Fit, thuật toán lựa chọn vùng trống có kích thước nhỏ nhất trong số các vùng đủ điều kiện.

H2 và H3 đều có kích thước 20 KB, nhỏ hơn H1 có kích thước 40 KB.

Áp dụng quy tắc đã thống nhất là ưu tiên `startKB` nhỏ nhất khi bằng kích thước, thuật toán lựa chọn H2, bắt đầu tại vị trí 50 KB.

### Bước 3. Thực hiện cấp phát
Theo quy ước đã thống nhất, tiến trình được cấp phát từ đầu vùng trống được chọn.

Tiến trình P1 sử dụng 18 KB bộ nhớ từ vùng H2.

**Dung lượng còn lại:** 20 KB − 18 KB = 2 KB.

Sau khi cấp phát:

- P1 chiếm khoảng từ mốc 50 KB đến trước mốc 68 KB (trên bảng là 50–67).
- Phần trống còn lại nằm từ mốc 68 KB đến trước mốc 70 KB (trên bảng là 68–69).

### Bước 4. Cập nhật trạng thái bộ nhớ
| **Vùng nhớ**   | **Khoảng vị trí (KB)** | **Kích thước (KB)** | **Trạng thái** |
| -------------- | ----------- | -------------- | -------------- |
| H1             | 0–39        | 40             | Trống          |
| B              | 40–49       | 10             | Đang sử dụng   |
| P1             | 50–67       | 18             | Đang sử dụng   |
| Phần dư của H2 | 68–69       | 2              | Trống          |
| D              | 70–79       | 10             | Đang sử dụng   |
| H3             | 80–99       | 20             | Trống          |

**Kết quả:** P1 được cấp phát thành công, bắt đầu tại vị trí 50 KB và sử dụng 18 KB. Phần trống của H2 còn 2 KB, có `startKB` thay đổi từ 50 thành 68 và `freeKB` thay đổi từ 20 thành 2. Nếu mô hình giữ nguyên mã `id=2` cho phần dư thì bản ghi `Hole` tương ứng chuyển từ `{2, 50, 20}` thành `{2, 68, 2}` theo thứ tự `{id, startKB, freeKB}`. Việc quản lý mã vùng thuộc mô-đun quản lý RAM. Tổng dung lượng trống sau cấp phát là 40 + 2 + 20 = 62 KB.

## 5. Các trường hợp cần xử lý khi mô phỏng
Dựa trên nguyên lý cấp phát bộ nhớ liên tục và thuật toán Best Fit, chương trình cần xử lý các trường hợp sau:

| **Trường hợp**                                | **Cách xử lý**                                                            |
| --------------------------------------------- | ------------------------------------------------------------------------- |
| Có một vùng trống nhỏ nhất đủ đáp ứng yêu cầu | Lựa chọn vùng đó để cấp phát                                              |
| Vùng được chọn lớn hơn dung lượng yêu cầu     | Chia vùng nhớ và giữ lại phần dư                                          |
| Vùng được chọn bằng dung lượng yêu cầu        | Cấp phát toàn bộ vùng, không tạo phần dư                                  |
| Nhiều vùng cùng kích thước nhỏ nhất phù hợp   | Ưu tiên `startKB` nhỏ nhất theo quy tắc đã thống nhất                     |
| Không có vùng trống liên tục đủ lớn           | Trả kết quả thất bại, thông báo lỗi và không thay đổi RAM theo yêu cầu của bài lập trình |
| Một tiến trình giải phóng bộ nhớ              | Đưa vùng được giải phóng trở lại danh sách vùng trống                     |
| Vùng vừa giải phóng liền kề vùng trống khác   | Gộp các vùng trống liền kề thành một vùng lớn hơn                         |

Trường hợp yêu cầu dung lượng không dương là dữ liệu đầu vào không hợp lệ trong chương trình mô phỏng. Nếu vùng trống còn `freeKB = 0`, vùng đó không thể đáp ứng một yêu cầu cấp phát dương; việc giữ hay loại bỏ bản ghi vùng này cần tuân theo thiết kế của TV1. Kiểm tra mã tiến trình bị trùng, giải phóng và gộp vùng trống là các quy tắc quản lý RAM cần phối hợp với mô-đun TV1, không phải quy tắc riêng của bước lựa chọn Best Fit.

## 6. Mối liên hệ giữa Best Fit và phân mảnh ngoài
Theo mục 9.2.3 – Fragmentation, cả First Fit và Best Fit đều có thể gặp hiện tượng phân mảnh ngoài (External Fragmentation).

Phân mảnh ngoài xảy ra khi tổng dung lượng bộ nhớ còn trống đủ để đáp ứng một yêu cầu cấp phát, nhưng các vùng trống không liên tục, khiến không có vùng riêng lẻ nào đủ lớn để chứa tiến trình.

### Ví dụ minh họa
Tiếp tục sử dụng trạng thái bộ nhớ sau khi cấp phát P1 tại mục 4.

Các vùng trống còn lại:

- H1: 40 KB.
- Phần dư của H2: 2 KB.
- H3: 20 KB.

**Tổng dung lượng trống:** 40 + 2 + 20 = 62 KB.

Giả sử tiến trình P2 yêu cầu cấp phát 45 KB bộ nhớ.

Ta có:

- Tổng dung lượng trống là 62 KB, lớn hơn 45 KB.
- Vùng trống liên tục lớn nhất có kích thước 40 KB, nhỏ hơn 45 KB.

Như vậy, không tồn tại vùng trống liên tục nào đủ đáp ứng yêu cầu của P2.

**Kết quả:** P2 không thể được cấp phát ngay vì hiện tượng phân mảnh ngoài. Trong chương trình mô phỏng dựa theo bài tập lập trình của sách, yêu cầu này được thông báo là cấp phát thất bại do phân mảnh ngoài; RAM không bị thay đổi.

Ví dụ cho thấy Best Fit không loại bỏ được hiện tượng phân mảnh ngoài, dù thuật toán lựa chọn vùng trống có phần dung lượng còn dư nhỏ nhất trong mỗi lần cấp phát.

## 7. Đặc điểm của thuật toán Best Fit
### 7.1. Lựa chọn vùng nhớ
Best Fit lựa chọn vùng trống nhỏ nhất đủ đáp ứng yêu cầu, tạo ra phần bộ nhớ còn dư nhỏ nhất tại vùng được cấp phát trong lần cấp phát đó.

### 7.2. Quá trình tìm kiếm
Thuật toán cần tìm kiếm toàn bộ danh sách các vùng trống nếu danh sách chưa được sắp xếp theo kích thước.

Nếu chỉ xét nguyên lý Best Fit, danh sách sắp xếp theo kích thước tăng dần cho phép tìm vùng đủ lớn đầu tiên. Tuy nhiên, vì nhóm còn quy định ưu tiên `startKB` nhỏ nhất khi các vùng bằng kích thước, chỉ dừng ở vùng đầu tiên là đúng khi các vùng được sắp xếp theo **`freeKB` tăng dần, rồi `startKB` tăng dần**. Nếu chỉ sắp xếp theo `freeKB`, chương trình vẫn cần kiểm tra các vùng có cùng kích thước nhỏ nhất phù hợp để chọn `startKB` nhỏ nhất.

### 7.3. Hiện tượng phân mảnh ngoài
Best Fit vẫn có thể gặp phân mảnh ngoài. Khi các tiến trình được cấp phát và giải phóng bộ nhớ, không gian trống có thể bị chia thành nhiều vùng nhỏ, nằm rời rạc.

Điều này có thể khiến một yêu cầu cấp phát không được đáp ứng ngay, mặc dù tổng dung lượng bộ nhớ trống vẫn đủ.

### 7.4. So sánh với First Fit và Worst Fit
Theo các kết quả mô phỏng được đề cập trong sách:

- First Fit và Best Fit nhìn chung có kết quả tốt hơn Worst Fit về thời gian và mức sử dụng bộ nhớ.
- Không có kết luận rõ ràng rằng First Fit hay Best Fit luôn tốt hơn nhau về mức sử dụng bộ nhớ.
- First Fit nhìn chung nhanh hơn Best Fit.

Do đó, không thể khẳng định Best Fit luôn là thuật toán cấp phát bộ nhớ hiệu quả nhất trong mọi trường hợp.

## 8. Kết luận
Best Fit là thuật toán cấp phát bộ nhớ liên tục, lựa chọn vùng nhớ trống có kích thước nhỏ nhất nhưng vẫn đủ đáp ứng yêu cầu của tiến trình. Khi vùng được chọn lớn hơn dung lượng yêu cầu, phần bộ nhớ còn dư tiếp tục được quản lý để phục vụ các lần cấp phát tiếp theo.

Thuật toán cần tìm kiếm toàn bộ danh sách vùng trống nếu danh sách chưa được sắp xếp theo kích thước. Mặc dù tạo ra phần dung lượng dư nhỏ nhất tại vùng được lựa chọn trong mỗi lần cấp phát, Best Fit vẫn có thể gặp hiện tượng phân mảnh ngoài.

Để phục vụ việc lập trình và kiểm thử, nhóm đã thống nhất khi có nhiều vùng trống cùng kích thước nhỏ nhất phù hợp thì ưu tiên vùng có `startKB` nhỏ nhất. Tiến trình được cấp phát từ đầu vùng đã chọn; `startKB` và `freeKB` của phần trống còn lại được cập nhật tương ứng. Khi tìm kiếm trên danh sách đã sắp xếp, cũng phải bảo đảm quy tắc ưu tiên này. Đây là quy ước triển khai của nhóm, không phải quy định riêng của sách.

Nội dung phân tích là cơ sở để triển khai hàm cấp phát Best Fit, xây dựng chức năng ghi lại quá trình cấp phát và thực hiện kiểm thử trong các công việc tiếp theo.

## Tài liệu tham khảo
- Abraham Silberschatz, Peter B. Galvin, Greg Gagne, *Operating System Concepts*, 10th edition, Chapter 9 – Main Memory, mục 9.2.2 (trang 358–359), mục 9.2.3 (trang 359–360), và *Programming Projects – Contiguous Memory Allocation* (trang P-48 đến P-50).
- Quy ước triển khai được TV1 thông báo ngày 22/10/2026 về `Hole`, ưu tiên `startKB` và cập nhật vùng trống sau cấp phát.
