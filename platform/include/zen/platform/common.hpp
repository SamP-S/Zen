#pragma once

#include <cstdint>

namespace zen {

namespace platform {

using WindowHandle = uint32_t;

enum class PlatformBackendAPI {
	SDL2,
	GLFW
};

enum class GraphicsAPI {
	None,
	OpenGL,
	Vulkan
};

enum class WindowMode : uint8_t {
	Windowed,
	Borderless,
	Fullscreen
};

} // namespace platform

} // namespace zen
