
#include <iostream>
#include <SFML/Audio.hpp>

#include "Book.hpp"
#include "Chapter.hpp"


void LoadDuration(Book *book, Chapter *chapter) {
    sf::Music music;
    if (music.openFromFile(chapter->m_path)) {
        sf::Time duration = music.getDuration();
        unsigned seconds = duration.asSeconds();

        // Выводим в удобном формате
        std::cout << "Длительность: " << seconds << " секунд" << std::endl;
        chapter->m_duration = seconds;
    }
}
