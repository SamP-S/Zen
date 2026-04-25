#include "internal/sdl2_backend.hpp"

#include <cstdint>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

namespace zen {

namespace platform {

namespace sdl2 {

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

SDL2Backend::WindowState* SDL2Backend::getState(WindowHandle _handle) {
    auto it = m_windows.find(_handle);
    if (it != m_windows.end()) {
        return &it->second;
    }
    return nullptr;
}

const SDL2Backend::WindowState* SDL2Backend::getState(WindowHandle _handle) const {
    auto it = m_windows.find(_handle);
    if (it != m_windows.end()) {
        return &it->second;
    }
    return nullptr;
}

SDL_Window* SDL2Backend::getSDLWindow(WindowHandle _handle) const {
    auto state = getState(_handle);
    return state ? state->sdlWindow : nullptr;
}

// ---------------------------------------------------------------------------
// Lifecycle
// ---------------------------------------------------------------------------

SDL2Backend::~SDL2Backend() {
    shutdown();
}

bool SDL2Backend::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        spdlog::error("[SDL2] Failed to initialize SDL: {}", SDL_GetError());
        return false;
    }
    return true;
}

void SDL2Backend::shutdown() {
    for (auto& [handle, state] : m_windows) {
        if (state.glContext)
            SDL_GL_DeleteContext(state.glContext);
        if (state.sdlWindow)
            SDL_DestroyWindow(state.sdlWindow);
    }
    m_windows.clear();
    SDL_Quit();
}

// ---------------------------------------------------------------------------
// Windows
// ---------------------------------------------------------------------------

WindowHandle SDL2Backend::createWindow(const WindowDesc& _desc) {
    // create SDL window
    uint32_t sdlFlags = SDL_WINDOW_SHOWN;

    if (_desc.flags & WindowFlags::Resizable)   sdlFlags |= SDL_WINDOW_RESIZABLE;
    if (_desc.flags & WindowFlags::Fullscreen)  sdlFlags |= SDL_WINDOW_FULLSCREEN;
    if (_desc.flags & WindowFlags::Borderless)  sdlFlags |= SDL_WINDOW_BORDERLESS;
    if (_desc.flags & WindowFlags::Hidden)      sdlFlags |= SDL_WINDOW_HIDDEN;
    if (_desc.flags & WindowFlags::Maximized)   sdlFlags |= SDL_WINDOW_MAXIMIZED;
    if (_desc.flags & WindowFlags::AlwaysTop)   sdlFlags |= SDL_WINDOW_ALWAYS_ON_TOP;

    SDL_Window* sdlWindow = SDL_CreateWindow(
        _desc.title.c_str(),
        _desc.x,
        _desc.y,
        _desc.width,
        _desc.height,
        sdlFlags
    );

    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to create SDL window: {}", SDL_GetError());
        return kInvalidWindow;
    }

    // create window state
    WindowHandle handle = m_nextHandle++;
    m_windows[handle] = WindowState{ .sdlWindow = sdlWindow };
    return handle;
}

void SDL2Backend::destroyWindow(WindowHandle _handle) {
    auto it = m_windows.find(_handle);
    if (it == m_windows.end()) {
        spdlog::error("[SDL2] Failed to destroy window: invalid handle");
        return;
    }

    auto& state = it->second;
    if (state.glContext)
        SDL_GL_DeleteContext(state.glContext);
    if (state.sdlWindow)
        SDL_DestroyWindow(state.sdlWindow);
    m_windows.erase(it);
}

void* SDL2Backend::getNativeHandle(WindowHandle _handle) const {getSDLWindow(_handle);
    return static_cast<void*>(getSDLWindow(_handle));
}

void* SDL2Backend::getContextHandle(WindowHandle _handle) const {
    auto state = getState(_handle);
    if (!state) {
        spdlog::error("[SDL2] Failed to get context handle: invalid window handle");
        return nullptr;
    }
    return state->glContext;
}

void SDL2Backend::setTitle(WindowHandle _handle, const std::string& _title) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to set window title: invalid window handle");
        return;
    }
    SDL_SetWindowTitle(sdlWindow, _title.c_str());
}

std::string SDL2Backend::getTitle(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to get window title: invalid window handle");
        return "";
    }
    return std::string(SDL_GetWindowTitle(sdlWindow));
}

void SDL2Backend::setPosition(WindowHandle _handle, Point _position) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to set window position: invalid window handle");
        return;
    }
    SDL_SetWindowPosition(sdlWindow, _position.x, _position.y);
}

Point SDL2Backend::getPosition(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to get window position: invalid window handle");
        return {0, 0};
    }
    int x, y;
    SDL_GetWindowPosition(sdlWindow, &x, &y);
    return {x, y};
}

void SDL2Backend::setSize(WindowHandle _handle, Size _size) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to set window size: invalid window handle");
        return;
    }
    SDL_SetWindowSize(sdlWindow, _size.w, _size.h);
}

Size SDL2Backend::getSize(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to get window size: invalid window handle");
        return {0, 0};
    }
    int w, h;
    SDL_GetWindowSize(sdlWindow, &w, &h);
    return {w, h};
}

Rect SDL2Backend::getRect(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to get window rect: invalid window handle");
        return {0, 0, 0, 0};
    }
    int x, y, w, h;
    SDL_GetWindowPosition(sdlWindow, &x, &y);
    SDL_GetWindowSize(sdlWindow, &w, &h);
    return {x, y, w, h};
}

void SDL2Backend::setMinSize(WindowHandle _handle, Size _minSize) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to set window minimum size: invalid window handle");
        return;
    }
    SDL_SetWindowMinimumSize(sdlWindow, _minSize.w, _minSize.h);
}

Size SDL2Backend::getMinSize(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to get window minimum size: invalid window handle");
        return {0, 0};
    }
    int w, h;
    SDL_GetWindowMinimumSize(sdlWindow, &w, &h);
    return {w, h};
}

void SDL2Backend::show(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to show window: invalid window handle");
        return;
    }
    SDL_ShowWindow(sdlWindow);
}

void SDL2Backend::hide(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to hide window: invalid window handle");
        return;
    }
    SDL_HideWindow(sdlWindow);
}

bool SDL2Backend::isVisible(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to check window visibility: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_SHOWN) != 0;
}

void SDL2Backend::minimize(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to minimize window: invalid window handle");
        return;
    }
    SDL_MinimizeWindow(sdlWindow);
}

void SDL2Backend::maximize(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to maximize window: invalid window handle");
        return;
    }
    SDL_MaximizeWindow(sdlWindow);
}

void SDL2Backend::restore(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to restore window: invalid window handle");
        return;
    }
    SDL_RestoreWindow(sdlWindow);
}

bool SDL2Backend::isFullscreen(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to check if window is fullscreen: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_FULLSCREEN) != 0 || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
}

void SDL2Backend::focus(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to focus window: invalid window handle");
        return;
    }
    SDL_RaiseWindow(sdlWindow);
}

bool SDL2Backend::isFocused(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to check if window is focused: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

void SDL2Backend::captureCursor(WindowHandle _handle, bool _capture) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to set cursor capture: invalid window handle");
        return;
    }
    SDL_SetWindowGrab(sdlWindow, _capture ? SDL_TRUE : SDL_FALSE);
}

bool SDL2Backend::hasCursorCapture(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[SDL2] Failed to check cursor capture: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_MOUSE_GRABBED) != 0;
}

} // namespace sdl2

} // namespace platform

} // namespace zen
