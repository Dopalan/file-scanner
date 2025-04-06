#pragma once
#include <vector>
#include <string>

class FileScanner {
public:
    static std::vector<std::string> getAllFiles(const std::string& directoryPath);
};
