#pragma once

#include "zen/platform/common.hpp"
#include "zen/platform/event.hpp"
#include "zen/platform/i_backend.hpp"

namespace zen {

namespace platform {

/**
 * All OS interections flow through this interface.
 */ 

class Platform {
private:
    // --- Constr/Destr -----------------------------------------------------
    Platform() = default;
    ~Platform() = default;

    // no copy/move
    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;

    IBackend* m_backend = nullptr;
    WindowHandle m_mainWindow = kInvalidWindow;
    // EventHandler m_eventHandler;
    bool m_quitFlag = false;

public:
    // --- Lifecycle ---------------------------------------------------------
    static Platform& get();     // singleton access
    bool init(PlatformBackendAPI _backendAPI, GraphicsAPI _graphicsAPI);
    void shutdown();

    // --- Events ------------------------------------------------------------
    void setEventCallback(EventCallback _callback);
    
    // bool pollEvent(Event& _event);
    bool pollEvents();
    bool pollNativeEvent(void* _nativeEvent);

    // --- Window ------------------------------------------------------------
    // management
    WindowHandle createWindow(const WindowDesc& _desc);
    void destroyWindow(WindowHandle _handle);

    // native handlers
    void* getNativeHandle(WindowHandle _handle);
    void* getContextHandle(WindowHandle _handle);

    // properties
    void setTitle(WindowHandle _h, const std::string& _title);
    std::string getTitle(WindowHandle _h)    const;

    void setPosition(WindowHandle _h, Point _pos);
    Point getPosition(WindowHandle _h) const;

    void setSize(WindowHandle _h, Size _size);
    Size getSize(WindowHandle _h)     const;
    Rect getRect(WindowHandle _h)     const;

    void setMinSize(WindowHandle _h, Size _min);
    Size getMinSize(WindowHandle _h)  const;

    void show(WindowHandle _h);
    void hide(WindowHandle _h);
    bool isVisible(WindowHandle _h)   const;

    void minimize(WindowHandle _h);
    void maximize(WindowHandle _h);
    void restore(WindowHandle _h);
    bool isFullscreen(WindowHandle _h) const;

    void focus(WindowHandle _h);
    bool isFocused(WindowHandle _h)   const;

    void captureCursor(WindowHandle _h, bool _capture);
    bool hasCursorCapture(WindowHandle _h) const;

    // --- Input -------------------------------------------------------------
    // todo
};

} // namespace platform

} // namespace zen
