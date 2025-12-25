#ifndef APPSTATE_HPP__
#define APPSTATE_HPP__

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

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
        sf::Music m_music;
};

#endif // APPSTATE_HPP__
