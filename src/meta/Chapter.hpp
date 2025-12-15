#ifndef CHAPTER_HPP
#define CHAPTER_HPP

#include <string>
#include <stdint.h>

class Chapter {
    public:
        uint16_t m_number;
        std::string m_path;
        std::string m_name;
        std::string m_hash;
    public:
        Chapter();
        void SetHash(std::string hash);
        void SetPath(std::string path);
        void SetName(std::string name);
};

#endif // CHAPTER_HPP
