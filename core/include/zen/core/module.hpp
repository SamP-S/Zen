#pragma once

#include <string>

// As enum for implicit int conversion
enum class ModuleType {
    AUDIO,
    EVENT,
    GRAPHICS,
    WINDOW,
    MAX_ENUM
};

class Module {
public:
    // standard methods for safe start/end/rebooting modules
    virtual void Boot() = 0;
    virtual void Shutdown() = 0;
    
    virtual std::string GetModuleName() = 0;
    virtual ModuleType GetModuleType() = 0;
};
