
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "AudioPlayer.hpp"

AudioPlayer::AudioPlayer() {
    m_music = new sf::Music();
}

AudioPlayer::~AudioPlayer() {
    delete m_music;
}

void AudioPlayer::play() {
    m_music->play();
}

void AudioPlayer::pause() {
    m_music->pause();
}

void AudioPlayer::stop() {
    m_music->stop();
}

unsigned AudioPlayer::getDuration() {
    return m_music->getDuration().asSeconds();
}

AudioPlayer::State AudioPlayer::getStatus() {
    return AudioPlayer::State::Idle;
}

unsigned AudioPlayer::getPlayingOffset() {
    return m_music->getPlayingOffset().asSeconds();
}

void AudioPlayer::setPlayingOffset(unsigned position) {
    m_music->setPlayingOffset(sf::seconds(position));
}

bool AudioPlayer::openFromFile(std::string fileName) {
    return m_music->openFromFile(fileName);
}
