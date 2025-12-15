
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <filesystem>

#include "Bookmark.hpp"
#include "Config.hpp"
#include "fsx.hpp"


Bookmark::Bookmark() {
    dbPath = GetDbPath();
    std::cout << "debug: Директория с базой данных " << dbPath << std::endl;
    if (!fsx::is_regular_file(dbPath)) {
        create();
    }
}

Bookmark::~Bookmark() {
}

/**
 * Создаем базу данных
 *
 */
void Bookmark::create() {
    sqlite3 *db;

    // Шаг 1. Открываем
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        const char *err_msg = sqlite3_errmsg(db);
        std::cerr << "Ошибка открытия БД: " << err_msg << std::endl;
        // TODO - узнать sqlite3_free(err_msg);
        return;
    }

    // Шаг 2. Создаем структуру
    std::string query = "CREATE TABLE IF NOT EXISTS book ("
                "  book_hash TEXT NOT NULL PRIMARY KEY,"
                "  book_pos INTEGER DEFAULT 0,"
                ");";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, query.c_str(), 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return;
    }

    // Шаг 3. Закрываем
    sqlite3_close(db);
}

/**
 * Обновление позиции прослушивания книги
 *
 */
void Bookmark::UpdatePosition(std::string book_hash, unsigned book_pos) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sql = "UPDATE book SET book_pos = ? WHERE book_hash = ?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    sqlite3_bind_int(stmt, 1, book_pos);
    sqlite3_bind_text(stmt, 2, book_hash.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Ошибка обновления: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

out:

    sqlite3_close(db);

}

/**
 * Синхронизация закладок/позиций в аудиокниге
 *
 */
void Bookmark::Restore() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char* query = "SELECT book_hash, book_pos FROM book;";

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* book_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int book_pos = sqlite3_column_int(stmt, 1);

        std::cout << "hash = " << book_hash << " pos = " << book_pos << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

void Bookmark::Store() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
 
}

void Bookmark::Sync() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
 
}

