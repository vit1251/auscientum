
#include <string>
#include <fstream>
#include <vector>

#include "str.hpp"
#include "ZipArchive.hpp"


ZipArchive::ZipArchive() {
    m_archive = nullptr;
}

ZipArchive::~ZipArchive() {
    if (m_archive != nullptr) {
        zip_close(m_archive);
        m_archive = nullptr;
    }
}

void ZipArchive::Open(std::string fileName) {
    if (m_archive != nullptr) {
        zip_close(m_archive);
        m_archive = nullptr;
    }
    m_archive = zip_open(fileName.c_str(), ZIP_RDONLY, nullptr);
}

/**
 * Получаем список записей в архиве
 *
 */
std::vector<ZipArchive::Entry> ZipArchive::GetEntries() {
    std::vector<ZipArchive::Entry> entries;
    int numFiles = zip_get_num_entries(m_archive, 0);
    for (int i = 0; i < numFiles; ++i) {
        struct zip_stat fileInfo;
        zip_stat_init(&fileInfo);
        if (zip_stat_index(m_archive, i, 0, &fileInfo) == 0) {
            ZipArchive::Entry e;
            e.index = fileInfo.index;
            e.name = fileInfo.name;
            entries.push_back(e);
        }
    }
    return entries;
}

/**
 * Извлечение файла
 *
 */
void ZipArchive::Extract(std::string zipFile, std::string outFile) {
    int numFiles = zip_get_num_entries(m_archive, 0);
    for (int i = 0; i < numFiles; ++i) {
        struct zip_stat fileInfo;
        zip_stat_init(&fileInfo);
        if (zip_stat_index(m_archive, i, 0, &fileInfo) == 0) {
            // Шаг 1. Пропускаем директории
            std::string path = fileInfo.name;
            if (str::endsWith(path, "/")) {
                continue;
            }
            // Шаг 2. Распаковываем только указанный файл
            if (zipFile == path) {
                zip_file* file = zip_fopen_index(m_archive, i, 0);
                if (file) {
                    std::ofstream out(outFile, std::ios::binary);
                    std::vector<char> buffer(8192);
                    zip_int64_t size = 0;
                    while ((size = zip_fread(file, buffer.data(), buffer.size())) > 0) {
                        out.write(reinterpret_cast<const char*>(buffer.data()), size);
                    }
                    out.close();
                    zip_fclose(file);
        	}
    	    }
	}
    }
}

void ZipArchive::Close() {
    if (m_archive != nullptr) {
        zip_close(m_archive);
        m_archive = nullptr;
    }
}
