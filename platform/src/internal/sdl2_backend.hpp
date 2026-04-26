#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "zen/platform/i_backend.hpp"

namespace zen {

namespace platform {

namespace sdl2 {

class SDL2Backend final : public IBackend {
private:
    // internal state
    struct WindowState {
        SDL_Window* sdlWindow = nullptr;
        SDL_GLContext glContext = nullptr; // null if not openGL context
    };
    WindowState* getState(WindowHandle _handle);
    const WindowState* getState(WindowHandle _handle) const;
    SDL_Window* getSDLWindow(WindowHandle _handle) const;
    Event translateSDLEvent(const SDL_Event& sdlEvent) const;

    std::unordered_map<WindowHandle, WindowState> m_windows;
    WindowHandle m_nextHandle = 1;  // 0 rserved for invalid
    GraphicsAPI m_graphicsAPI = GraphicsAPI::None;

public:
    // --- Constr/Destr -----------------------------------------------------
    SDL2Backend() = default;
    ~SDL2Backend() override;

    // --- Lifecycle ---------------------------------------------------------
    bool init(GraphicsAPI _graphicsAPI) override;
    void shutdown() override;

    // --- Events ------------------------------------------------------------
    bool pollEvent(Event* _event) override;
    bool pollNativeEvent(void* _nativeEvent) override;

    // --- Window ------------------------------------------------------------
    // management
    WindowHandle createWindow(const WindowDesc& _desc) override;
    void destroyWindow(WindowHandle _handle) override;

    // native handlers
    void* getNativeHandle(WindowHandle _handle) const override;
    void* getContextHandle(WindowHandle _handle) const override;

    // properties
    void setTitle(WindowHandle _handle, const std::string& _title) override;
    std::string getTitle(WindowHandle _handle) const override;

    void setPosition(WindowHandle _handle, Point _position) override;
    Point getPosition(WindowHandle _handle) const override;

    void setSize(WindowHandle _handle, Size _size) override;
    Size getSize(WindowHandle _handle) const override;
    Rect getRect(WindowHandle _handle) const override;

    void setMinSize(WindowHandle _handle, Size _minSize) override;
    Size getMinSize(WindowHandle _handle) const override;

    void show(WindowHandle _handle) override;
    void hide(WindowHandle _handle) override;
    bool isVisible(WindowHandle _handle) const override;

    void minimize(WindowHandle _handle) override;
    void maximize(WindowHandle _handle) override;
    void restore(WindowHandle _handle) override;
    bool isFullscreen(WindowHandle _handle) const override;

    void focus(WindowHandle _handle) override;
    bool isFocused(WindowHandle _handle) const override;

    void captureCursor(WindowHandle _handle, bool _capture) override;
    bool hasCursorCapture(WindowHandle _handle) const override;

    // --- Grapphics Context ---------------------------------------------------
    void swapBuffers(WindowHandle _handle) override;
};

} // namespace sdl2

} // namespace platform

} // namespace zen