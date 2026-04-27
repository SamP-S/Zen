#include "zen/platform/platform.hpp"
#include "internal/sdl2_backend.hpp"

#include <cassert>
#include <spdlog/spdlog.h>

namespace zen {

namespace platform {

// ---------------------------------------------------------------------------
// Internal State
// ---------------------------------------------------------------------------

void Platform::flushInternalState() {
    // reset per-frame key states
    for (auto& [key, state] : m_keys) {
        state.pressed = false;
        state.released = false;
    }
    // reset per-frame mouse button states
    for (auto& btn : m_mouse.buttons) {
        btn.pressed = false;
        btn.released = false;
    }
    // reset per-frame mouse motion/scroll
    m_mouse.dx = 0.0f;
    m_mouse.dy = 0.0f;
    m_mouse.scroll = 0.0f;
}

void Platform::updateInternalState(const Event& _event) {
    switch(_event.type) {
        // --- Quit ---------------------------------------------------------
        case EventType::Quit:
            spdlog::info("[Platform] Quit event received");
            m_quitFlag = true;

        // --- Keyboard -----------------------------------------------------
        case EventType::KeyDown: {
            const KeyCode key = static_cast<KeyCode>(_event.key.keycode);
            KeyState& state = m_keys[key];
            if (!state.down) {  // ignore auto-repeat for pressed
                state.pressed = true;
            }
            state.down = true;
        }
        case EventType::KeyUp: {
            const KeyCode key = static_cast<KeyCode>(_event.key.keycode);
            KeyState& state = m_keys[key];
            state.down = false;
            state.released = true;
            break;
        }

        // --- Mouse Buttons -----------------------------------------------------
        case EventType::MouseButtonDown: {
            const uint8_t btn = _event.mouseButton.button;
            if (btn < static_cast<uint8_t>(MouseButton::COUNT)) {
                KeyState& state = m_mouse.buttons[btn];
                if (!state.down) {  // ignore auto-repeat for pressed
                    state.pressed = true;
                }
                state.down = true;
            }
            break;
        }
        case EventType::MouseButtonUp: {
            const uint8_t btn = _event.mouseButton.button;
            if (btn < static_cast<uint8_t>(MouseButton::COUNT)) {
                KeyState& state = m_mouse.buttons[btn];
                state.down = false;
                state.released = true;
            }
            break;
        }

        // --- Mouse Motion -----------------------------------------------------
        case EventType::MouseMotion:
            m_mouse.x = _event.mouseMotion.x;
            m_mouse.y = _event.mouseMotion.y;
            m_mouse.dx += _event.mouseMotion.dx;
            m_mouse.dy += _event.mouseMotion.dy;
            break;

        // --- Mouse Scroll -----------------------------------------------------
        case EventType::MouseWheel:
            m_mouse.scroll += _event.mouseWheel.delta;
            break;

        // --- Window Input -----------------------------------------------------
        case EventType::WindowFocusLost:
            for (auto& [key, state] : m_keys)
                state = {};
            for (auto& btn : m_mouse.buttons)
                btn = {};
            break;
        case EventType::WindowMouseLeave:
            for (auto& btn : m_mouse.buttons) {
                btn.released    = btn.down; // released any held buttons
                btn.down        = false;
                btn.pressed     = false;
            }
            break;
        
        case EventType::WindowMinimized:
        case EventType::WindowHidden:
            // reset all input state when window is not visible, to prevent "stuck" keys on alt-tab
            for (auto& [key, state] : m_keys)
                state = {};
            for (auto& btn : m_mouse.buttons)
                btn = {};
            m_mouse.dx = 0.0f;
            m_mouse.dy = 0.0f;
            m_mouse.scroll = 0.0f;
            break;
        
        // --- Fallback -----------------------------------------------------
        default:
            break;
    }
}

// ---------------------------------------------------------------------------
// Singleton
// ---------------------------------------------------------------------------

Platform& Platform::get() {
    static Platform instance;
    return instance;
}

// ---------------------------------------------------------------------------
// Lifecycle
// ---------------------------------------------------------------------------

bool Platform::init(PlatformBackendAPI _backendAPI, GraphicsAPI _grahpicsAPI) {
    assert(!m_backend && "Platform already initialized");

    // instanciate the requested backend
    switch (_backendAPI) {
        case PlatformBackendAPI::SDL2:
            m_backend = new sdl2::SDL2Backend();
            break;
        default:
            spdlog::warn("[Platform] Unsupported platform backend API");
            return false;
    }

    // init the backend with the requested graphics API
    if (!m_backend->init(_grahpicsAPI)) {
        spdlog::error("[Platform] Failed to initialize platform backend");
        delete m_backend;
        m_backend = nullptr;
        return false;
    }   

    m_quitFlag = false;
    return true;
}

void Platform::shutdown() {
    if (m_backend) {
        m_backend->shutdown();
        delete m_backend;
        m_backend = nullptr;
    }
    m_quitFlag = false;
}

// ---------------------------------------------------------------------------
// Events
// ---------------------------------------------------------------------------

void Platform::bindEventCallback(EventCallback _callback) {
    assert(m_backend && "Platform not initialized");
    m_eventCallback = std::move(_callback);
}

void Platform::unbindEventCallback() {
    m_eventCallback = nullptr;
}

bool Platform::pollEvents() {
    assert(m_backend && "Platform not initialized");

    flushInternalState();

    Event event;
    while (m_backend->pollEvent(&event)) {
        updateInternalState(event);
        if (m_eventCallback)
            m_eventCallback(event);
    }

    return !m_quitFlag;
}

bool Platform::pollNativeEvent(void* _nativeEvent) {
    assert(m_backend && "Platform not initialized");
    spdlog::error("[Platform] pollNativeEvent is not implemented. This stub always returns false.");
    return m_backend->pollNativeEvent(_nativeEvent);
}

bool Platform::shouldClose() const {
    return m_quitFlag;
}

// ---------------------------------------------------------------------------
// Window
// ---------------------------------------------------------------------------

WindowHandle Platform::createWindow(const WindowDesc& _desc) {
    assert(m_backend && "Platform not initialized");
    return m_backend->createWindow(_desc);
}

void Platform::destroyWindow(WindowHandle _handle) {
    assert(m_backend && "Platform not initialized");
    m_backend->destroyWindow(_handle);
}

void* Platform::getNativeHandle(WindowHandle _handle) {
    assert(m_backend && "Platform not initialized");
    return m_backend->getNativeHandle(_handle); 
}

void* Platform::getContextHandle(WindowHandle _handle) {
    assert(m_backend && "Platform not initialized");
    return m_backend->getContextHandle(_handle); 
}

void Platform::setTitle(WindowHandle _h, const std::string& _title) {
    assert(m_backend && "Platform not initialized");
    m_backend->setTitle(_h, _title);
}

std::string Platform::getTitle(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->getTitle(_h);
}

void Platform::setPosition(WindowHandle _h, Point _pos) {
    assert(m_backend && "Platform not initialized");
    m_backend->setPosition(_h, _pos);
}

Point Platform::getPosition(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->getPosition(_h);
}

void Platform::setSize(WindowHandle _h, Size _size) {
    assert(m_backend && "Platform not initialized");
    m_backend->setSize(_h, _size);
}

Size Platform::getSize(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->getSize(_h);
}

Rect Platform::getRect(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->getRect(_h);
}

void Platform::setMinSize(WindowHandle _h, Size _min) {
    assert(m_backend && "Platform not initialized");
    m_backend->setMinSize(_h, _min);
}

Size Platform::getMinSize(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->getMinSize(_h);
}

void Platform::show(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->show(_h);
}

void Platform::hide(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->hide(_h);
}

bool Platform::isVisible(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->isVisible(_h);
}

void Platform::minimize(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->minimize(_h);
}

void Platform::maximize(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->maximize(_h);
}

void Platform::restore(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->restore(_h);
}

bool Platform::isFullscreen(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->isFullscreen(_h);
}

void Platform::focus(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->focus(_h);
}

bool Platform::isFocused(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->isFocused(_h);
}

void Platform::captureCursor(WindowHandle _h, bool _capture) {
    assert(m_backend && "Platform not initialized");
    m_backend->captureCursor(_h, _capture);
}

bool Platform::hasCursorCapture(WindowHandle _h) const {
    assert(m_backend && "Platform not initialized");
    return m_backend->hasCursorCapture(_h);
}

// ---------------------------------------------------------------------------
// Graphics Context
// ---------------------------------------------------------------------------

void Platform::swapBuffers(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->swapBuffers(_h);
}

// ---------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------

// keyboard
bool Platform::isKeyDown(KeyCode _key) const {
    assert(m_backend && "Platform not initialized");
    auto it = m_keys.find(_key);
    return it != m_keys.end() && it->second.down;
}

bool Platform::isKeyPressed(KeyCode _key) const {
    assert(m_backend && "Platform not initialized");
    auto it = m_keys.find(_key);
    return it != m_keys.end() && it->second.pressed;
}

bool Platform::isKeyReleased(KeyCode _key) const {
    assert(m_backend && "Platform not initialized");
    auto it = m_keys.find(_key);
    return it != m_keys.end() && it->second.released;
}

// mouse buttons
bool Platform::isMouseDown(MouseButton _button) const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.buttons[static_cast<uint8_t>(_button)].down;
}

bool Platform::isMousePressed(MouseButton _button) const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.buttons[static_cast<uint8_t>(_button)].pressed;
}

bool Platform::isMouseReleased(MouseButton _button) const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.buttons[static_cast<uint8_t>(_button)].released;
}

// mouse motion
float Platform::mouseX() const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.x;
}

float Platform::mouseY() const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.y;
}

float Platform::mouseDX() const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.dx;
}

float Platform::mouseDY() const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.dy;
}

float Platform::mouseScroll() const {
    assert(m_backend && "Platform not initialized");
    return m_mouse.scroll;
}

} // namespace platform

} // namespace zen