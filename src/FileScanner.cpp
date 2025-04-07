#include "FileScanner.h"

//quét và lấy đường dẫn tất cả các file trong thư mục
//trả về danh sách đường dẫn file
std::vector<std::string> FileScanner::getAllFiles(const std::string& directoryPath) {
    std::vector<std::string> filePaths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            filePaths.push_back(entry.path().string());
        }
    }
    return filePaths;

    
}

bool  FileScanner::encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& key) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &encryptKey);

    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for encryption: " << inputFilePath << std::endl;
        return false;
    }

    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file for encrypted data: " << outputFilePath << std::endl;
        return false;
    }

    unsigned char buffer[16];  // AES block size is 16 bytes
    unsigned char encryptedBuffer[16];

    while (inFile.read(reinterpret_cast<char*>(buffer), sizeof(buffer))) {
        AES_encrypt(buffer, encryptedBuffer, &encryptKey);
        outFile.write(reinterpret_cast<char*>(encryptedBuffer), sizeof(encryptedBuffer));
    }

    inFile.close();
    outFile.close();
    return true;
}
