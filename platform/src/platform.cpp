#include "zen/platform/platform.hpp"
#include "internal/sdl2_backend.hpp"

#include <cassert>
#include <spdlog/spdlog.h>

namespace zen {

namespace platform {

// ---------------------------------------------------------------------------
// Internal State
// ---------------------------------------------------------------------------

void Platform::updateInternalState(const Event& _event) {
    switch(_event.type) {
        case EventType::Quit:
            spdlog::info("[Platform] Quit event received");
            m_quitFlag = true;
        default:
            spdlog::warn("[Platform] Unhandled event type: {}", static_cast<int>(_event.type));
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

void Platform::setEventCallback(EventCallback _callback) {
    assert(m_backend && "Platform not initialized");
    m_eventCallback = std::move(_callback);
}

bool Platform::pollEvents() {
    assert(m_backend && "Platform not initialized");
    if (m_quitFlag) return false;

    Event event;
    while (m_backend->pollEvent(&event)) {
        updateInternalState(event);
        if (m_eventCallback) m_eventCallback(event);
    }
    return true;
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
// Window
// ---------------------------------------------------------------------------
void Platform::swapBuffers(WindowHandle _h) {
    assert(m_backend && "Platform not initialized");
    m_backend->swapBuffers(_h);
}

} // namespace platform

} // namespace zen