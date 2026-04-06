#pragma once

#include <functional>

#include "core/module.hpp"
#include "platform/event.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace zen {

namespace platform {

class IWindow {
private:
    IWindow() = default;
    ~IWindow() = default;

    // prevent copying
    IWindow(const IWindow&) = delete;
    IWindow& operator=(const IWindow&) = delete;   

    // move ok
    IWindow(IWindow&&) noexcept = default;
    IWindow& operator=(IWindow&&) noexcept = default;

public:
    // native handlers
    void* GetNativeWindowHandler() const;
    void* GetNativeContextHandler() const;
    
    // event handling
    void AddEventHandler(std::function<void(Event&)> _handler);

    // looping
    void StartFrame();
    void EndFrame();

    // properties
    void Minimize();
    void Close();
    void SetWindowMinSize(int _minWidth, int _minHeight);
    void GetWindowMinSize(int& _minWidth, int& _minHeight);
    void SetWindowSize(int _width, int _height);
    void GetWindowSize(int& _width, int& _height);
    void SetCursorCapture(bool _capture);
    bool GetCursorCapture();
};

} // namespace platform

} // namespace zen
