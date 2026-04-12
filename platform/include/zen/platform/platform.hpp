#pragma once

#include "zen/platform/i_window.hpp"

namespace zen {

namespace platform {

/// Platform 

class Platform {
public:
    Platform() = default;
    ~Platform() = default;

    IWindow* CreateWindow();
    void DestroyWindow(IWindow* _window);

};

} // namespace platform

} // namespace zen
