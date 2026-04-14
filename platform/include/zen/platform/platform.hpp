#pragma once

#include "zen/platform/common.hpp"

namespace zen {

namespace platform {

class Platform {
public:
    Platform(PlatformBackendAPI _backendAPI);
    ~Platform() = default;

};

} // namespace platform

} // namespace zen
