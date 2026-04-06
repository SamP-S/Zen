#pragma once

#include "zen/core/module.hpp"

namespace zen { 

namespace input {

class Input : public Module {
public:

    // module interface
    void Boot() override;
    void Shutdown() override;
    std::string GetModuleName() override;
    ModuleType GetModuleType() override;

};

} // namespace input

} // namespace zen
