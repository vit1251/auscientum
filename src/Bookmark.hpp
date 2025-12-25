#ifndef BOOKMARK_HPP__
#define BOOKMARK_HPP__

class Book;
class Chapter;

class Bookmark {
    protected:
        void CreateScheme();
        void InsertChapter(Book* book, Chapter* chapter);
        void UpdateChapter(Book* book, Chapter* chapter);
        unsigned Exists(Book* book, Chapter* chapter, bool *res);
    protected:
        std::string dbPath;
    public:
        Bookmark();
        ~Bookmark();
        void ReadChapter(Book* book, Chapter* chapter);
        void SaveChapter(Book* book, Chapter* chapter);
};

#endif // BOOKMARK_HPP__
