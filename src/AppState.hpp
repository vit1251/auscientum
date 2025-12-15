#ifndef APPSTATE_HPP__
#define APPSTATE_HPP__

class Book;
class Bookmark;

class AppState {
    public:
        AppState();
    public:
        Bookmark* m_bookmark;
        std::string m_dbPath;
        Book* m_book;
        bool m_reading;
};

#endif // APPSTATE_HPP__
