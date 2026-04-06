#pragma once

#include <functional>

#include "core/module.hpp"
#include "platform/event.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace zen {

namespace platform {

class Window {
private:
    Window() = default;
    ~Window() = default;

    // prevent copying
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;   

    // move ok
    Window(Window&&) noexcept = default;
    Window& operator=(Window&&) noexcept = default;

public:
    // native handlers
    void* GetNativeWindowHandler() const;
    void* GetNativeContextHandler() const;
    void SwapFrame();

    // event handling
    void AddEventHandler(std::function<void(Event&)> handler);

    // properties
    void Minimize();
    void Close();
    void SetWindowMinSize(int minWidth, int minHeight);
    void GetWindowMinSize(int& minWidth, int& minHeight);
    void SetWindowSize(int width, int height);
    void GetWindowSize(int& width, int& height);
    void SetCursorCapture(bool capture);
    bool GetCursorCapture();
};

} // namespace platform

} // namespace zen
