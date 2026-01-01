
#include <iostream>
#include <SFML/Audio.hpp>

#include "Book.hpp"
#include "Chapter.hpp"

#include "Duration.hpp"

DurationError LoadDuration(Book *book, Chapter *chapter) {
    sf::Music music;
    if (!music.openFromFile(chapter->m_path)) {
        return DurationError::IOError;
    }
    sf::Time duration = music.getDuration();
    unsigned seconds = duration.asSeconds();
    std::cout << "Длительность: " << seconds << " секунд" << std::endl;
    chapter->m_duration = seconds;
    return DurationError::Ok;
}
