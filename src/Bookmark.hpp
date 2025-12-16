#ifndef BOOKMARK_HPP__
#define BOOKMARK_HPP__

class Book;
class Chapter;

class Bookmark {
    protected:
        void updateScheme();
    protected:
        std::string dbPath;
    public:
        Bookmark();
        ~Bookmark();
        void UpdateChapter(Book* book, Chapter* chapter);
        void Sync();
        void UpdatePosition(std::string book_hash, unsigned book_pos);
        void Restore();
        void Store();

};

#endif // BOOKMARK_HPP__
