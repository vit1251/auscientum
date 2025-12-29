#ifndef ZIPARCHIVE_HPP__
#define ZIPARCHIVE_HPP__

#include <vector>

#include <zip.h>


class ZipArchive {
    protected:
        zip* m_archive;
    public:
        /* Запись в ZIP архиве */
        class Entry {
            friend class ZipArchive;
            protected:
                unsigned index;            // Идентификатор в архиве
                uint32_t crc;              // Контрольная сумма
            public:
                std::string name;          // Имя файла
                uint64_t size;             // Размер файла (до сжатия)
                uint64_t comp_size;        // Размер файла (сжатый)
                time_t mtime;              // Дата модификации
        };
    public:
        ZipArchive();
        ~ZipArchive();
    public:
        void Open(std::string path);
        std::vector<Entry> GetEntries();
        void Extract(std::string zipFile, std::string outFile);
        void Close();
};

#endif // ZIPARCHIVE_HPP__
