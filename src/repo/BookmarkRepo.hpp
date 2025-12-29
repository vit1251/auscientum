#ifndef BOOKMARK_REPO_HPP__
#define BOOKMARK_REPO_HPP__

#include <mutex>

struct sqlite3;

class Book;
class Chapter;

class BookmarkRepo {
    protected:
        std::mutex m_mutex;
        sqlite3 *db;
    public:
        BookmarkRepo();
        ~BookmarkRepo();
    public:
        void SaveBookmark(Book *book, Chapter* chapter);
};

#endif // BOOKMARK_REPO_HPP__
