#pragma once

#include <cstdint>
#include <functional>
#include "zen/platform/common.hpp"

namespace zen {

namespace platform {

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
	WindowHandle handle;
    union {
        struct { uint32_t width, height; } window;
        struct { uint32_t keycode; } key;
        struct { float x, y; } mouse;
		struct { float delta; } scroll;

    };
};

using EventCallback = std::function<void(const Event&)>;

} // namespace platform
	
} // namespace zen
