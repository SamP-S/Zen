#pragma once

#include "platform/window.hpp"

namespace zen {

namespace platform {

class Platform {
public:
    Platform() = default;
    ~Platform() = default;

    Window* CreateWindow();
    void DestroyWindow(Window* _window);

};

} // namespace platform

} // namespace zen
