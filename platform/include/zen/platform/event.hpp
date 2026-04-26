#pragma once

#include <cstdint>
#include <functional>
#include "zen/platform/common.hpp"

namespace zen {

namespace platform {

enum class EventType {
    Common,
    Quit,
    WindowShown,
    WindowHidden,
    WindowMoved,
    WindowResized,
    WindowMinimized,
    WindowMaximized,
    WindowRestored,
    WindowDestroyed,
    WindowExposed,
    WindowOccluded,
    WindowMouseEnter,
    WindowMouseLeave,
    WindowFocusGained,
    WindowFocusLost,
    KeyUp,
    KeyDown,
    MouseMotion,
    MouseButtonDown,
    MouseButtonUp,
    MouseScroll,
    Unsupported,
};

struct CommonEvent {
    uint32_t data1, data2, data3, data4;
};

struct QuitEvent {};

struct WindowEvent {
    uint32_t    windowID;
    uint32_t    data1;      // event dependent data (width/x)
    uint32_t    data2;      // event dependent data (height/y)
};

struct KeyEvent {
    uint32_t    windowID;
    uint32_t    keycode;
    uint8_t     state;      // 0 = released, 1 = pressed
    uint8_t     repeat;     // 0 = not a repeat, 1 = repeat
};

struct MouseMotionEvent {
    uint32_t    windowID;
    uint32_t    state;      // bitfield of buttons currently pressed
    float       x, y;       // mouse position relative to window
    float       dx, dy;     // relative motion since last event
};

struct MouseButtonEvent {
    uint32_t    windowID;
    uint8_t     button;
    uint8_t     state;      // 0 = released, 1 = pressed
    float       x, y;       // mouse position relative to window
};

struct MouseScrollEvent {
    uint32_t    windowID;
    int32_t     delta;      // scroll amount, positive = scroll up, negative = scroll down
};

struct Event {
    EventType   type;
    union {
        CommonEvent         common;
        QuitEvent           quit;
        WindowEvent         window;
        KeyEvent            key;
        MouseMotionEvent    mouseMotion;
        MouseButtonEvent    mouseButton;
        MouseScrollEvent    mouseScroll;
    };
};

using EventCallback = std::function<void(const Event&)>;

} // namespace platform
	
} // namespace zen
