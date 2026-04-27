#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <cassert>

#include "zen/platform/common.hpp"
#include "zen/platform/event.hpp"
#include "zen/platform/i_backend.hpp"
#include "zen/platform/input.hpp"

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

    IBackend* m_backend = nullptr;              // backend implementation
    EventCallback m_eventCallback = nullptr;    // user callback for event driven
    bool m_quitFlag = false;                    // quit flag set when quit flag received
    std::unordered_map<KeyCode, KeyState> m_keys = {};  // indexed by KeyCode, layout-independent key states
    MouseState m_mouse = {};                    // mouse state

    void flushInternalState();                      // reset per-frame input state
    void updateInternalState(const Event& _event);  // cache input state

public:
    // --- Lifecycle ---------------------------------------------------------
    static Platform& get();     // singleton access
    bool init(PlatformBackendAPI _backendAPI, GraphicsAPI _graphicsAPI);
    void shutdown();

    // --- Events ------------------------------------------------------------

    // callbacks
    void bindEventCallback(EventCallback _callback);
    void unbindEventCallback();
    
    // polling
    // bool pollEvent(Event& _event);
    bool pollEvents();
    bool pollNativeEvent(void* _nativeEvent);   // bypasses event processing, for UI libraries (ImGui)

    // quit flag
    bool shouldClose() const;

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

    // --- Graphics Context --------------------------------------------------
    
    // swap framebuffers
    void swapBuffers(WindowHandle _h);

    // --- Input -------------------------------------------------------------

    // keyboard
    bool isKeyDown(KeyCode _key) const;     // held down
    bool isKeyPressed(KeyCode _key) const;  // pressed this frame
    bool isKeyReleased(KeyCode _key) const; // released this frame

    // mouse buttons
    bool isMouseDown(MouseButton _button) const;     // held down
    bool isMousePressed(MouseButton _button) const;  // pressed this frame
    bool isMouseReleased(MouseButton _button) const; // released this frame

    // mouse motion
    float mouseX() const;
    float mouseY() const;
    float mouseDX() const;
    float mouseDY() const;
    float mouseScroll() const;
};

} // namespace platform

} // namespace zen
