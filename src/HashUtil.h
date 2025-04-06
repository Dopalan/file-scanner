#pragma once
#include <string>

class HashUtil {
public:
    static std::string computeSHA256(const std::string& filePath);
    static bool isValidSHA256(const std::string& hash) ;
};
