
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "Bookmark.hpp"
#include "Config.hpp"
#include "fsx.hpp"
#include "Book.hpp"
#include "Chapter.hpp"


Bookmark::Bookmark() {
    dbPath = GetDbPath();
    CreateScheme();
}

Bookmark::~Bookmark() {
}

/**
 * Создаем базу данных
 *
 */
void Bookmark::CreateScheme() {
    sqlite3 *db = nullptr;
    std::string query;
    char *err_msg = nullptr;
    int rc;

    // Шаг 1. Открываем
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        const char *err_msg = sqlite3_errmsg(db);
        std::cerr << "Ошибка открытия БД: " << err_msg << std::endl;
        goto out;
    }

    // Шаг 2. Создаем таблицу аудиокниги (ab)
    query = "CREATE TABLE IF NOT EXISTS ab ("
                "  ab_hash TEXT NOT NULL,"
                "  ab_chapter_hash TEXT NOT NULL,"
                "  ab_position INTEGER NOT NULL DEFAULT 0,"
                "  PRIMARY KEY (ab_hash, ab_chapter_hash)"
                ");";
    rc = sqlite3_exec(db, query.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        goto out;
    }

out:

    // Шаг 3. Закрываем
    sqlite3_close(db);

}

/**
 * Загружает позицию главы и в случае отсутствия позиции создает новую запись
 *
 */
void Bookmark::InsertChapter(Book *book, Chapter* chapter) {
    sqlite3 *db = nullptr;
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    int rc = 0;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    query = "INSERT INTO ab (ab_hash, ab_chapter_hash, ab_position) VALUES (?,?,?);";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    sqlite3_bind_text(stmt, 1, book->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, chapter->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, 0);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Ошибка обновления: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

out:

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

/**
 * Обновление позиции прослушивания книги
 *
 */
void Bookmark::UpdateChapter(Book *book, Chapter* chapter) {
    sqlite3 *db = nullptr;
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    int rc = 0;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    query = "UPDATE ab SET ab_position = ? WHERE ab_hash = ? AND ab_chapter_hash = ?";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    sqlite3_bind_int(stmt, 1, chapter->m_pos);
    sqlite3_bind_text(stmt, 2, book->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, chapter->m_hash.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Ошибка обновления: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

out:

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

/**
 * Синхронизация закладок/позиций в аудиокниге
 *
 */
unsigned Bookmark::Exists(Book *book, Chapter* chapter, bool *res) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char* query = "SELECT ab_hash, ab_chapter_hash, ab_position FROM ab WHERE ab_hash = ? AND ab_chapter_hash = ?";
    unsigned rowCount = 0;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, book->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, chapter->m_hash.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* book_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* chapter_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int book_pos = sqlite3_column_int(stmt, 2);
        std::cout << "hash = " << book_hash << " pos = " << book_pos << std::endl;
        rowCount += 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    *res = rowCount > 0;

    return 0;
}

/**
 * Синхронизация закладок/позиций в аудиокниге
 *
 */
void Bookmark::ReadChapter(Book *book, Chapter* chapter) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char* query = "SELECT ab_hash, ab_chapter_hash, ab_position FROM ab WHERE ab_hash = ? AND ab_chapter_hash = ?";
    unsigned rowCount = 0;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, book->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, chapter->m_hash.c_str(), -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* book_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* chapter_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int position = sqlite3_column_int(stmt, 2);
        std::cout << "hash = " << book_hash << " pos = " << position << std::endl;
        if (chapter->m_hash == chapter_hash) {
            std::cout << "Найдена закладка: " << position << " сек. для главы " << chapter->m_hash << std::endl;
            chapter->m_pos = position;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Bookmark::SaveChapter(Book *book, Chapter* chapter) {
    bool exists;
    int err = Exists(book, chapter, &exists);
    if (err != 0) {
        return;
    }
    std::cout << "Книга " << book->m_hash << " " << (exists ? "уже существует" : "не существует") << std::endl;
    if (exists) {
        UpdateChapter(book, chapter);
    } else {
        InsertChapter(book, chapter);
    }
}

