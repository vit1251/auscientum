#ifndef BOOKMARK_HPP__
#define BOOKMARK_HPP__

class Bookmark {
    protected:
        void create();
    protected:
        std::string dbPath;
    public:
        Bookmark();
        ~Bookmark();
        void Sync();
        void UpdatePosition(std::string book_hash, unsigned book_pos);
        void Restore();
        void Store();

};

#endif // BOOKMARK_HPP__
