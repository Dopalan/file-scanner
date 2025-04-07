#include "FileScanner.h"
#include "HashUtil.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>  
#include <chrono>
#include "cxxopts.hpp"

int main(int argc, char* argv[])  {

    cxxopts::Options options("FileScanner", "A simple file scanner to detect files with SHA-256 blacklist");
    
    options.add_options()
        ("d,directory", "Directory to scan", cxxopts::value<std::string>())
        ("b,blacklist", "Path to blacklist file", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") || !result.count("directory") || !result.count("blacklist")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::string directory = result["directory"].as<std::string>();
    std::string blacklistPath = result["blacklist"].as<std::string>(); 

    std::unordered_set<std::string> blacklist;
    std::ifstream blFile(blacklistPath);

    if (!blFile.is_open()) {
        std::cerr << "Failed to open file: " << blacklistPath << std::endl;
        return 1;  
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(blFile, line)) {
        ++lineNumber;
        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }
        if (HashUtil::isValidSHA256(line)) {
            blacklist.insert(line);
        } else {
            std::cerr << "Invalid SHA-256 hash at line " << lineNumber << ": " << line << std::endl;
            return 1;
        }
    }
    if (lineNumber == 0) {
        std::cerr << "Blacklist file is empty." << std::endl;
        return 1;
    }
    blFile.close(); 






    auto files = FileScanner::getAllFiles(directory);

     // Thư mục cách ly
    std::string isolateDir = "isolated_files";
    std::filesystem::create_directory(isolateDir); // Tạo thư mục nếu chưa có

    std::ofstream logFile("logFileScanner.out");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file.\n";
        return 1;
    }
    
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& file : files) {
        std::string hash = HashUtil::computeSHA256(file);

        if (blacklist.count(hash)) {
            // Nếu file bị phát hiện là đáng ngờ, mã hóa và di chuyển vào thư mục cách ly
            std::string isolateFilePath = isolateDir + "/" + std::filesystem::path(file).filename().string() + ".enc";
            if (FileScanner::encryptFile(file, isolateFilePath, "my_secret_key")) {
                std::cout << "[!] Suspicious file found and encrypted: " << file << "\n";
            }
        } else {
            std::cout << "[OK] " << file << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    logFile << "Scan completed in " << duration.count() << " seconds\n";
    logFile.close();
    std::cout<<"Scan completed in " << duration.count() << " seconds\n";
    return 0;
}
