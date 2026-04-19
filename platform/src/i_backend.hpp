#pragma once

#include <functional>
#include <cstdint>
#include <string>
#include <optional>

#include "zen/platform/event.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace zen {

namespace platform {

/**
 * Abstract interface for platform backends to implement.
 * All OS interections flow through this interface.
 */ 

class IBackend {
public:
    IBackend() = default;
    virtual ~IBackend() = default;

    // prevent copying
    IBackend(const IBackend&) = delete;
    IBackend& operator=(const IBackend&) = delete;   

    // move ok
    IBackend(IBackend&&) noexcept = default;
    IBackend& operator=(IBackend&&) noexcept = default;

	// lifecycle
	virtual bool init() = 0;
	virtual void shutdown() = 0;

    /// --- Window Management
	// window lifecycle
	virtual WindowHandle createWindow(const WindowDesc& _desc) = 0;
	virtual void destroyWindow(WindowHandle _handle) = 0;

    // native handlers
    virtual void* getNativeHandle(WindowHandle _handle) const = 0;
    virtual void* getContextHandle(WindowHandle _handle) const = 0;
    
    // event handling
    virtual void pollEvents(WindowHandle _handle) = 0;

    // properties
    virtual void setWindowTitle(WindowHandle _handle, const std::string& _title) = 0;
    virtual std::string getWindowTitle(WindowHandle _handle) const = 0;
    virtual void setWindowPosition(WindowHandle _handle, Point _position) = 0;
    virtual Point getWindowPosition(WindowHandle _handle) const = 0;
    virtual void showWindow(WindowHandle _handle) = 0;
    virtual void hideWindow(WindowHandle _handle) = 0;
    virtual bool isWindowVisible(WindowHandle _handle) const = 0;
    virtual void minimizeWindow(WindowHandle _handle) = 0;
    virtual void maximizeWindow(WindowHandle _handle) = 0;
    virtual void restoreWindow(WindowHandle _handle) = 0;
    virtual bool isWindowFullscreen(WindowHandle _handle) const = 0;
    virtual void focusWindow(WindowHandle _handle) = 0;
    virtual bool isWindowFocused(WindowHandle _handle) const = 0;
    virtual void setWindowMinSize(WindowHandle _handle, Size _minSize) = 0;
    virtual Size getWindowMinSize(WindowHandle _handle) const = 0;
    virtual void setWindowSize(WindowHandle _handle, Size _size) = 0;
    virtual Size getWindowSize(WindowHandle _handle) const = 0;
    virtual Rect getWindowRect(WindowHandle _handle) const = 0;
    virtual void setCursorCapture(WindowHandle _handle, bool _capture) = 0;
    virtual bool getCursorCapture(WindowHandle _handle) const = 0;
};

} // namespace platform

} // namespace zen
