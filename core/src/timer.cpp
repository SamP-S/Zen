#include "zen/core/timer.hpp"


namespace zen {

namespace core {


Timer::Timer() {
    Reset();
}

void Timer::Reset() {
    m_startTime = std::chrono::system_clock::now();
    m_tickTime = m_startTime;
}

double Timer::GetElapsed(bool _isMilli) {
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count();
    return _isMilli ? dt : dt / 1000;
}

double Timer::Tick(bool _isMilli) {
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_tickTime).count();
    m_tickTime = currentTime;
    return _isMilli ? dt : dt / 1000;
}

double Timer::GetDelta(bool _isMilli) {
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_tickTime).count();
    return _isMilli ? dt : dt / 1000;
}

} // namespace core

} // namespace zen
