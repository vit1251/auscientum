
#include <iostream>

#include <sqlite3.h>

#include "Book.hpp"
#include "Chapter.hpp"
#include "BookmarkRepo.hpp"


BookmarkRepo::BookmarkRepo() {
    sqlite3_open("mydata.db", &db);
    sqlite3_exec(db, "PRAGMA synchronous = FULL;", NULL, NULL, 0);
    sqlite3_exec(db, "PRAGMA journal_mode = WAL;", NULL, NULL, 0);
}

BookmarkRepo::~BookmarkRepo() {
    sqlite3_close(db);
}

void BookmarkRepo::SaveBookmark(Book *book, Chapter* chapter) {
    sqlite3_stmt *stmt = nullptr;
    std::lock_guard<std::mutex> lock(m_mutex);

    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, 0);

    if (sqlite3_prepare_v2(db, "UPDATE ab SET ab_position = ? WHERE ab_hash = ? AND ab_chapter_hash = ?", -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    sqlite3_bind_int(stmt, 1, chapter->m_pos);
    sqlite3_bind_text(stmt, 2, book->m_hash.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, chapter->m_hash.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Ошибка обновления: " << sqlite3_errmsg(db) << std::endl;
        goto out;
    }

    sqlite3_exec(db, "COMMIT;", NULL, NULL, 0);

out:

    sqlite3_finalize(stmt);

}
