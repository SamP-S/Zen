#pragma once

#include "zen/platform/common.hpp"

namespace zen {

namespace platform {

WindowFlags operator|(WindowFlags a, WindowFlags b) noexcept {
    return static_cast<WindowFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

WindowFlags& operator|=(WindowFlags& a, WindowFlags b) noexcept {
    return a = a | b;
}

bool operator&(WindowFlags a, WindowFlags b) noexcept {
    return (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;
}

} // namespace platform

} // namespace zen