#pragma once

#include <functional>

enum class EventType {
    WindowClose,
    WindowResize,
    KeyDown,
    KeyUp,
    MouseButtonDown,
    MouseButtonUp,
    MouseMove,
    MouseWheel,
};

struct Event {
    EventType type;
    union {
        struct { int width, height; }   resize;
        struct { int keycode; }         key;
        struct { float x, y; }        mouse;
    };
};

using EventCallback = std::function<void(const Event&)>;
