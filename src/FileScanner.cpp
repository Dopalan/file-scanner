#include "FileScanner.h"
#include <filesystem>

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
