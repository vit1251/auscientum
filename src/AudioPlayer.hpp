#ifndef AUDIOPLAYER_HPP__
#define AUDIOPLAYER_HPP__

namespace sf {
    class Music;
}

class AudioPlayer {
    protected:
        sf::Music *m_music;
    public:
        enum class State {
            Idle,
            Playing,
            Stop,
            Paused
        };
    public:
        AudioPlayer();
        ~AudioPlayer();
    public:
        void play();
        void pause();
        void stop();
        unsigned getDuration();
        State getStatus();
        unsigned getPlayingOffset();
        void setPlayingOffset(unsigned position);
        bool openFromFile(std::string fileName);
};

#endif // AUDIOPLAYER_HPP__
