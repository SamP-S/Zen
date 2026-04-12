#pragma once

#include <cstdint>

namespace zen {
	
namespace platform {

enum class WindowMode : uint8_t {
	Windowed,
	Borderless,
	Fullscreen
};

} // namespace platform

} // namespace zen

