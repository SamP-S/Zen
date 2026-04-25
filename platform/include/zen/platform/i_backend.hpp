#pragma once

#include <functional>
#include <cstdint>
#include <string>
#include <optional>

#include "zen/platform/event.hpp"

namespace zen {

namespace platform {

/**
 * Abstract interface for platform backends to implement.
 * All OS library calls flow through this interface.
 */ 

class IBackend {
public:
    // --- Constr/Destr -----------------------------------------------------
    IBackend() = default;
    virtual ~IBackend() = default;

    // prevent copying
    IBackend(const IBackend&) = delete;
    IBackend& operator=(const IBackend&) = delete;   

    // move ok
    IBackend(IBackend&&) noexcept = default;
    IBackend& operator=(IBackend&&) noexcept = default;

	// --- Lifecycle ---------------------------------------------------------
	virtual bool init() = 0;
	virtual void shutdown() = 0;

    // --- Events ------------------------------------------------------------
    virtual bool pollEvent(Event& _event) = 0;  // user polls for events, pre-processed by backend (translate native events to Event & cache state i.e key states, mouse position, etc)
    virtual bool pollNativeEvent(void* _nativeEvent) = 0; // native events, unprocessed for UI libraries (ImGui) that need access to native events, backend should still update internal state for these events (key states, mouse position, etc)

    // --- Events ------------------------------------------------------------
	// management
	virtual WindowHandle createWindow(const WindowDesc& _desc) = 0;
	virtual void destroyWindow(WindowHandle _handle) = 0;

    // native handlers
    virtual void* getNativeHandle(WindowHandle _handle) const = 0;
    virtual void* getContextHandle(WindowHandle _handle) const = 0;
    
    // properties
    virtual void setTitle(WindowHandle _handle, const std::string& _title) = 0;
    virtual std::string getTitle(WindowHandle _handle) const = 0;
    
    virtual void setPosition(WindowHandle _handle, Point _position) = 0;
    virtual Point getPosition(WindowHandle _handle) const = 0;

    virtual void setSize(WindowHandle _handle, Size _size) = 0;
    virtual Size getSize(WindowHandle _handle) const = 0;
    virtual Rect getRect(WindowHandle _handle) const = 0;

    virtual void setMinSize(WindowHandle _handle, Size _minSize) = 0;
    virtual Size getMinSize(WindowHandle _handle) const = 0;

    virtual void show(WindowHandle _handle) = 0;
    virtual void hide(WindowHandle _handle) = 0;
    virtual bool isVisible(WindowHandle _handle) const = 0;

    virtual void minimize(WindowHandle _handle) = 0;
    virtual void maximize(WindowHandle _handle) = 0;
    virtual void restore(WindowHandle _handle) = 0;
    virtual bool isFullscreen(WindowHandle _handle) const = 0;

    virtual void focus(WindowHandle _handle) = 0;
    virtual bool isFocused(WindowHandle _handle) const = 0;

    virtual void captureCursor(WindowHandle _handle, bool _capture) = 0;
    virtual bool hasCursorCapture(WindowHandle _handle) const = 0;
};

} // namespace platform

} // namespace zen
