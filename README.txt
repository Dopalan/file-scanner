# 🔍 File Scanner - Malware Hash Checker

Một công cụ C++ đơn giản giúp quét thư mục và kiểm tra các tệp có trùng với danh sách hash độc hại. Dự án này giúp bạn luyện tập lập trình hướng đối tượng, xử lý file hệ thống, và tích hợp tính năng bảo mật cơ bản bằng cách sử dụng SHA-256.

---

## 🚀 Tính năng chính

- Duyệt tất cả các tệp trong thư mục con
- Tính toán hash SHA-256 cho từng tệp
- So sánh hash với danh sách "blacklist" có sẵn
- In thông báo nếu phát hiện file nghi ngờ

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
- Thư viện OpenSSL (để tính toán SHA-256)

