#ifndef STOPWATCH_HPP__
#define STOPWATCH_HPP__

#include <chrono>

class StopWatch {
    protected:
        std::chrono::time_point<std::chrono::steady_clock> m_start;
        std::chrono::time_point<std::chrono::steady_clock> m_end;
        bool m_complete;
    public:
        StopWatch();
        ~StopWatch();
    public:
        void start();
        void stop();
        unsigned getOffset();
};

#endif // STOPWATCH_HPP__
