#include "FileScanner.h"
#include "HashUtil.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>  

int main() {

    std::string directory;
    std::string blacklistPath;

    std::cout << "Enter  directory path: ";
    std::getline(std::cin, directory);  

    std::cout << "Enter  blacklist file path:";
    std::getline(std::cin, blacklistPath); 

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
    std::ofstream logFile("logFileScanner.out");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file.\n";
        return 1;
    }
    for (const auto& file : files) {
        std::string hash = HashUtil::computeSHA256(file);
        if (blacklist.count(hash)) {
            logFile << "[!] Suspicious file: " << file << "\n";;
        } else {
            logFile << "[OK] " << file << "\n";

        }
    }
    logFile.close();

    return 0;
}
