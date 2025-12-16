
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <zip.h>

#include "Hash.hpp"
#include "Chapter.hpp"
#include "Book.hpp"


static bool endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.size() > str.size()) return false;
    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 * Восстанавливаем книгу из ZIP представления
 *
**/
Book* restoreBook(std::string fileName) {
    Book* book = new Book();
    int err;

    // Шаг 0. Запомним имя архива с файлами
    book->SetArchive(fileName);

    // Шаг 1. Проходимся по файлам архива
    zip* archive = zip_open(fileName.c_str(), ZIP_RDONLY, &err);
    if (archive == nullptr) {
        // Шаг 1. Получаем сообщение об ошибке
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        const char *msg = zip_error_strerror(&error);
        book->SetError(msg); // Будет скопировано
        zip_error_fini(&error);
        return book;
    }

    // Шаг 2. Получаем список файлов
    int numFiles = zip_get_num_entries(archive, 0);
    for (int i = 0; i < numFiles; ++i) {
        struct zip_stat fileInfo;
        zip_stat_init(&fileInfo);
        if (zip_stat_index(archive, i, 0, &fileInfo) == 0) {
            std::string path = fileInfo.name;
            if (endsWith(path, "/")) {
                continue;
            }
            Chapter *chapter = new Chapter();
            chapter->SetPath(path);
            //
            zip_file* file = zip_fopen_index(archive, i, 0);
            if (file) {
                std::vector<char> buffer(8192);
                Hash hash;
                zip_int64_t size = 0;
                while ((size = zip_fread(file, buffer.data(), buffer.size())) > 0) {
                    hash.Update(buffer.data(), size);
                }
                zip_fclose(file);
                std::string chapterHash = hash.Digest();
                chapter->SetHash(chapterHash);
            }
            book->addChapter(chapter);
        }
    }
    zip_close(archive);

    // Шаг 2. Вычисляем уникальный идентификатор книги
    std::vector<std::string> hashs;
    for (auto chapter: book->m_chapters) {
        std::cout << "Глава: " << chapter->m_path << " сумма = " << chapter->m_hash << std::endl;
        hashs.push_back(chapter->m_hash);
    }
    std::sort(hashs.begin(), hashs.end());
    Hash bookDigest;
    for (auto hash: hashs) {
        std::cout << "В алфавитном порядке " << hash << std::endl;
        bookDigest.Update(hash);
    }
    std::string bookHash = bookDigest.Digest();
    std::cout << "Книге присвоен идентификатор " << bookHash << std::endl;
    book->SetHash(bookHash);

    return book;
}
