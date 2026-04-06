#pragma once

#include "platform/i_window.hpp"

namespace zen {

namespace platform {

class Platform {
public:
    Platform() = default;
    ~Platform() = default;

    IWindow* CreateWindow();
    void DestroyWindow(IWindow* _window);

};

} // namespace platform

} // namespace zen
