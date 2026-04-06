#pragma once

#include <chrono>
#include <cstdint>


namespace zen {

namespace core {


class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> m_startTime;
    std::chrono::time_point<std::chrono::system_clock> m_tickTime;

public:
    // Constructor
    Timer();

    // Resets timer 0.0s
    void Reset();

    // Gets elapsed time since the timer was started or last reset
    double GetElapsed(bool _isMilli = false);

    // Gets delta time since the last tick and update tick timestamp
    double Tick(bool _isMilli = false);

    // Get delta time since the last tick
    double GetDelta(bool _isMilli = false);

};


} // namespace core

} // namespace zen
