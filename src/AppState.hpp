#ifndef APPSTATE_HPP__
#define APPSTATE_HPP__

#include "AudioPlayer.hpp"

class Book;
class Bookmark;

class AppState {
    public:
        AppState();
        ~AppState();
    public:
        Bookmark* m_bookmark;
        std::string m_dbPath;
        Book* m_book;
        bool m_reading;
        AudioPlayer m_music;
};

#endif // APPSTATE_HPP__
