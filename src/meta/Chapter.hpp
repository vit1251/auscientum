#ifndef CHAPTER_HPP
#define CHAPTER_HPP

#include <string>
#include <stdint.h>

class Chapter {
    public:
        uint16_t m_number;              // Номер главы
        std::string m_zip_path;         // Путь в архиве
        std::string m_path;             // Путь к файлу
        std::string m_name;             // Имя файла
        std::string m_hash;             // Хэш файла
        unsigned m_pos;                 // Позиция аудио 
    public:
        Chapter();
        void SetHash(std::string hash);
        void SetZipPath(std::string zipPath);
        void SetPath(std::string path);
        void SetName(std::string name);
        void SetNumber(unsigned number);
};

#endif // CHAPTER_HPP
