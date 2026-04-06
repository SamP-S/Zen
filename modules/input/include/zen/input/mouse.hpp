#pragma once

#include <cstdint>
#include <bitset>

struct Mouse {
    int32_t x = 0;
    int32_t y = 0;
    std::bitset<5> buttonStates = 0; // Left, Right, Middle, X1, X2
};
