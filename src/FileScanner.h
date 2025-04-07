#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>

class FileScanner {
public:
    static std::vector<std::string> getAllFiles(const std::string& directoryPath);
    static bool encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& key);
};
