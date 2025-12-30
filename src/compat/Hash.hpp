#ifndef HASH_HPP__
#define HASH_HPP__

#include <string>
#include <vector>

#include <openssl/evp.h>

class Hash {
    private:
        EVP_MD_CTX* m_ctx;
    public:
        Hash();
        ~Hash();
        void Update(std::string buffer);
        void Update(std::vector<char> buffer);
        void Update(const char* buffer, size_t size);
        std::string Digest();
};


std::string hash_file(const std::string& path);


#endif // HASH_HPP__
