
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

#include <openssl/evp.h>

#include "Hash.hpp"

Hash::Hash() {
    m_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(m_ctx, EVP_sha512(), NULL);
}

Hash::~Hash() {
    EVP_MD_CTX_free(m_ctx);
}

void Hash::Update(std::string buffer) {
    EVP_DigestUpdate(m_ctx, buffer.data(), buffer.size());
}

void Hash::Update(std::vector<char> buffer) {
    EVP_DigestUpdate(m_ctx, buffer.data(), buffer.size());
}

void Hash::Update(const char* buffer, size_t size) {
    EVP_DigestUpdate(m_ctx, buffer, size);
}

std::string Hash::Digest() {
    unsigned char hash[64];
    unsigned int len;
    EVP_DigestFinal_ex(m_ctx, hash, &len);
    size_t length = sizeof(hash) / sizeof(hash[0]);
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < length; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}

/**
 * Функция для вычисления SHA512 хеша файла
 *
**/
std::string hash_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    std::vector<char> buffer(4096);
    Hash messageDigest;

    for (;;) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes_read = file.gcount();
        if (bytes_read == 0) {
            break;
        }
        messageDigest.Update(buffer.data(), bytes_read);
    }
    return messageDigest.Digest();
}
