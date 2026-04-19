#pragma once

#include <cstdint>

enum class KeyMod {
    None    = 0,
    Shift   = 1 << 0,
    Ctrl    = 1 << 1,
    Alt     = 1 << 2,
    Super   = 1 << 3
};
