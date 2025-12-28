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
            public:
                std::string name;          // Имя файла
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
