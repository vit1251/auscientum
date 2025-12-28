
class BookStore {
    protected:
    public:
        BookStore();
        ~BookStore();
    public:
        std::list<Book *> Read(std::string path);
};
