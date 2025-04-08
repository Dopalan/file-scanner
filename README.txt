# 🔍 File Scanner - Malware Hash Checker

Một công cụ C++ đơn giản giúp quét thư mục và kiểm tra các tệp có trùng với danh sách hash độc hại, sau đó mã hóa và chuyển đến thư mục riêng

---

## 🚀 Tính năng chính

- Duyệt tất cả các tệp trong thư mục con
- Tính toán hash SHA-256 cho từng tệp
- So sánh hash với danh sách "blacklist" có sẵn
- In thông báo nếu phát hiện file nghi ngờ
- Mã hóa và chuyển file đến thư mục

---

## 📁 Cấu trúc thư mục

file-scanner/
│
├── src/
│   ├── main.cpp
│   ├── FileScanner.h / FileScanner.cpp
│   ├── HashUtil.h / HashUtil.cpp
│
├── test/
│   └── sample_files/
│
├── blacklist.txt  
├── README.md     



---

## 📦 Yêu cầu

- C++17 trở lên
- Thư viện OpenSSL

