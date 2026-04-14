#pragma once

#include <functional>
#include <cstdint>

#include "zen/platform/event.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace zen {

namespace platform {

class IWindowBackend {
private:
    IWindowBackend() = default;
    ~IWindowBackend() = default;

    // prevent copying
    IWindowBackend(const IWindowBackend&) = delete;
    IWindowBackend& operator=(const IWindowBackend&) = delete;   

    // move ok
    IWindowBackend(IWindowBackend&&) noexcept = default;
    IWindowBackend& operator=(IWindowBackend&&) noexcept = default;

public:
	// lifecycle
	virtual void init();
	virtual void shutdown();

	// window lifecycle
	virtual WindowHandle create();
	virtual void destroy(WindowHandle _handle);
	virtual void destroyAllWindows();

    // native handlers
    virtual void* getNativeHandle(WindowHandle _handle) const;
    virtual void* getContextHandle(WindowHandle _handle) const;
    
    // event handling
    virtual void pollEvents();

    // looping
    virtual void startFrame();
    virtual void endFrame();

    // properties
    virtual void minimize(WindowHandle _handle);
    virtual void close(WindowHandle _handle);
    virtual void setWindowMinSize(WindowHandle _handle, int _minWidth, int _minHeight);
    virtual void getWindowMinSize(WindowHandle _handle, int& _minWidth, int& _minHeight) const;
    virtual void setWindowSize(WindowHandle _handle, int _width, int _height);
    virtual void getWindowSize(WindowHandle _handle, int& _width, int& _height) const;
    virtual void setCursorCapture(WindowHandle _handle, bool _capture);
    virtual bool getCursorCapture(WindowHandle _handle) const;
};

} // namespace platform

} // namespace zen
