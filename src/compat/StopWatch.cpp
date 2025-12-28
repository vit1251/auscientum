
#include <chrono>

#include "StopWatch.hpp"


StopWatch::StopWatch() {
    m_start = std::chrono::steady_clock::now();
    m_complete = false;
}

StopWatch::~StopWatch() {
}

void StopWatch::start() {
    m_start = std::chrono::steady_clock::now();
}

void StopWatch::stop() {
    m_end = std::chrono::steady_clock::now();
    m_complete = true;
}

/**
 * Длительность в секундах
 *
 */
unsigned StopWatch::getOffset() {
    if (m_complete) {
        std::chrono::duration<double> elapsed = m_end - m_start;
        return elapsed.count();
    } else {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - m_start;
        return elapsed.count();
    }
}
