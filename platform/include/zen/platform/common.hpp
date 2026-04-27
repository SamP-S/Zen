#pragma once

#include <cstdint>
#include <string>

namespace zen {

namespace platform {

// ---------------------------------------------------------------------------
// Backend Types
// ---------------------------------------------------------------------------

// enum of supported platform backends
enum class PlatformBackendAPI {
	None = 0,
	SDL2
};

// enum of supported graphics APIs
enum class GraphicsAPI {
	None = 0,
	OpenGL,
	Vulkan
};

// ---------------------------------------------------------------------------
// Window
// ---------------------------------------------------------------------------

// opaque handle type for windows
using WindowHandle = uint32_t;

// sentinel value for invalid window handle
static constexpr WindowHandle kInvalidWindow = 0;

// bitfield flags for window parameters
enum class WindowFlags : uint8_t {
	None 		= 0u,
	Resizable 	= 1u << 0,
	Fullscreen 	= 1u << 1,
	Borderless 	= 1u << 2,
	Hidden 		= 1u << 3,
	Maximized 	= 1u << 4,
	AlwaysTop 	= 1u << 5
};

inline WindowFlags operator|(WindowFlags a, WindowFlags b) noexcept {
    return static_cast<WindowFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline WindowFlags& operator|=(WindowFlags& a, WindowFlags b) noexcept {
    return a = a | b;
}

inline bool operator&(WindowFlags a, WindowFlags b) noexcept {
    return (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;
}

// default window dimensions
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

// sentinel to create window x/y to request OS-centred placement
static constexpr int32_t kWindowCentred = INT32_MIN;

// window description struct for window creation
struct WindowDesc {
	std::string title = "Zen Window";
	int32_t width = DEFAULT_WINDOW_WIDTH;
	int32_t height = DEFAULT_WINDOW_HEIGHT;
	int32_t x = kWindowCentred;
	int32_t y = kWindowCentred;
	WindowFlags flags = WindowFlags::None;
};

// ---------------------------------------------------------------------------
// Geometry
// ---------------------------------------------------------------------------

struct Point {
	int32_t x;
	int32_t y;
};

struct Size {
	union { int32_t w; int32_t width; };
	union { int32_t h; int32_t height; };
};

struct Rect {
	union { int32_t x; };
	union { int32_t y; };
	union { int32_t w; int32_t width; };
	union { int32_t h; int32_t height; };

	int32_t left() const { return x; }
	int32_t right() const { return x + w; }
	int32_t top() const { return y; }
	int32_t bottom() const { return y + h; }
};

} // namespace platform

} // namespace zen
