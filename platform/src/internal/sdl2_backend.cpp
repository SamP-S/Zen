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

bool SDL2Backend::init(GraphicsAPI _graphicsAPI) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        spdlog::error("[Platform] [SDL2] Failed to initialize SDL: {}", SDL_GetError());
        return false;
    }

    switch(_graphicsAPI) {
        case GraphicsAPI::OpenGL:
            spdlog::info("[Platform] [SDL2] Graphics API set to OpenGL");
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            break;
        case GraphicsAPI::Vulkan:
            spdlog::info("[Platform] [SDL2] Graphics API set to Vulkan");
            spdlog::critical("[Platform] [SDL2] Vulkan support is not fully implemented yet");
            break;
        case GraphicsAPI::None:
            spdlog::info("[Platform] [SDL2] Graphics API set to None");
            break;
        default:
            spdlog::warn("[Platform] [SDL2] Unsupported graphics API, defaulting to None");
            break;
    }
    m_graphicsAPI = _graphicsAPI;
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
// Events
// ---------------------------------------------------------------------------

bool SDL2Backend::pollEvent(Event* _event) {
    SDL_Event sdlEvent;
    if (SDL_PollEvent(&sdlEvent)) {
        *_event = translateSDLEvent(sdlEvent);
        return true;
    }
    return false;
}

bool SDL2Backend::pollNativeEvent(void* _nativeEvent) {
    SDL_Event* sdlEvent = static_cast<SDL_Event*>(_nativeEvent);
    if (SDL_PollEvent(sdlEvent)) {
        return true;
    }
    return false;
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
    if (m_graphicsAPI == GraphicsAPI::OpenGL)   sdlFlags |= SDL_WINDOW_OPENGL;
    if (m_graphicsAPI == GraphicsAPI::Vulkan)   sdlFlags |= SDL_WINDOW_VULKAN;

    SDL_Window* sdlWindow = SDL_CreateWindow(
        _desc.title.c_str(),
        _desc.x,
        _desc.y,
        _desc.width,
        _desc.height,
        sdlFlags
    );

    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to create SDL window: {}", SDL_GetError());
        return kInvalidWindow;
    }

    // create window state
    WindowHandle handle = m_nextHandle++;
    WindowState state = { .sdlWindow = sdlWindow };

    // create OpenGL context if requested
    if (m_graphicsAPI == GraphicsAPI::OpenGL) {
        SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);
        if (!glContext) {
            spdlog::error("[Platform] [SDL2] Failed to create OpenGL context: {}", SDL_GetError());
            SDL_DestroyWindow(sdlWindow);
            return kInvalidWindow;
        }
        // store context in window state
        state.glContext = glContext;
    }
    
    // write state to window map
    m_windows[handle] = state;
    return handle;
}

void SDL2Backend::destroyWindow(WindowHandle _handle) {
    auto it = m_windows.find(_handle);
    if (it == m_windows.end()) {
        spdlog::error("[Platform] [SDL2] Failed to destroy window: invalid handle");
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
        spdlog::error("[Platform] [SDL2] Failed to get context handle: invalid window handle");
        return nullptr;
    }
    return state->glContext;
}

void SDL2Backend::setTitle(WindowHandle _handle, const std::string& _title) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to set window title: invalid window handle");
        return;
    }
    SDL_SetWindowTitle(sdlWindow, _title.c_str());
}

std::string SDL2Backend::getTitle(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to get window title: invalid window handle");
        return "";
    }
    return std::string(SDL_GetWindowTitle(sdlWindow));
}

void SDL2Backend::setPosition(WindowHandle _handle, Point _position) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to set window position: invalid window handle");
        return;
    }
    SDL_SetWindowPosition(sdlWindow, _position.x, _position.y);
}

Point SDL2Backend::getPosition(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to get window position: invalid window handle");
        return {0, 0};
    }
    int x, y;
    SDL_GetWindowPosition(sdlWindow, &x, &y);
    return {x, y};
}

void SDL2Backend::setSize(WindowHandle _handle, Size _size) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to set window size: invalid window handle");
        return;
    }
    SDL_SetWindowSize(sdlWindow, _size.w, _size.h);
}

Size SDL2Backend::getSize(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to get window size: invalid window handle");
        return {0, 0};
    }
    int w, h;
    SDL_GetWindowSize(sdlWindow, &w, &h);
    return {w, h};
}

Rect SDL2Backend::getRect(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to get window rect: invalid window handle");
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
        spdlog::error("[Platform] [SDL2] Failed to set window minimum size: invalid window handle");
        return;
    }
    SDL_SetWindowMinimumSize(sdlWindow, _minSize.w, _minSize.h);
}

Size SDL2Backend::getMinSize(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to get window minimum size: invalid window handle");
        return {0, 0};
    }
    int w, h;
    SDL_GetWindowMinimumSize(sdlWindow, &w, &h);
    return {w, h};
}

void SDL2Backend::show(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to show window: invalid window handle");
        return;
    }
    SDL_ShowWindow(sdlWindow);
}

void SDL2Backend::hide(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to hide window: invalid window handle");
        return;
    }
    SDL_HideWindow(sdlWindow);
}

bool SDL2Backend::isVisible(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to check window visibility: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_SHOWN) != 0;
}

void SDL2Backend::minimize(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to minimize window: invalid window handle");
        return;
    }
    SDL_MinimizeWindow(sdlWindow);
}

void SDL2Backend::maximize(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to maximize window: invalid window handle");
        return;
    }
    SDL_MaximizeWindow(sdlWindow);
}

void SDL2Backend::restore(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to restore window: invalid window handle");
        return;
    }
    SDL_RestoreWindow(sdlWindow);
}

bool SDL2Backend::isFullscreen(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to check if window is fullscreen: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_FULLSCREEN) != 0 || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
}

void SDL2Backend::focus(WindowHandle _handle) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to focus window: invalid window handle");
        return;
    }
    SDL_RaiseWindow(sdlWindow);
}

bool SDL2Backend::isFocused(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to check if window is focused: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

void SDL2Backend::captureCursor(WindowHandle _handle, bool _capture) {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to set cursor capture: invalid window handle");
        return;
    }
    SDL_SetWindowGrab(sdlWindow, _capture ? SDL_TRUE : SDL_FALSE);
}

bool SDL2Backend::hasCursorCapture(WindowHandle _handle) const {
    auto sdlWindow = getSDLWindow(_handle);
    if (!sdlWindow) {
        spdlog::error("[Platform] [SDL2] Failed to check cursor capture: invalid window handle");
        return false;
    }
    Uint32 flags = SDL_GetWindowFlags(sdlWindow);
    return (flags & SDL_WINDOW_MOUSE_GRABBED) != 0;
}

// ---------------------------------------------------------------------------
// Graphics Context
// ---------------------------------------------------------------------------

void SDL2Backend::swapBuffers(WindowHandle _handle) {
    auto state = getState(_handle);
    if (!state) {
        spdlog::error("[Platform] [SDL2] Failed to swap buffers: invalid window handle");
        return;
    }
    if (state->glContext) {
        SDL_GL_SwapWindow(state->sdlWindow);
    } else {
        spdlog::error("[Platform] [SDL2] Failed to swap buffers: window does not have an OpenGL context");
    }
}

} // namespace sdl2

} // namespace platform

} // namespace zen
