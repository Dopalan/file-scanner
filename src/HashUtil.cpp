#include "HashUtil.h"
#include "picosha2.h"
#include <fstream>
#include <vector>
#include <regex>

bool HashUtil::isValidSHA256(const std::string& hash) {
    static const std::regex sha256Pattern("^[a-fA-F0-9]{64}$");
    return std::regex_match(hash, sha256Pattern);
}
std::string HashUtil::computeSHA256(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return "";

    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(file, hash.begin(), hash.end());

    return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
