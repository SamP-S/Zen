#pragma once

class IInput {
public:
    IInput() = default;
    ~IInput() = default;

    // prevent copying
    IInput(const IInput&) = delete;
    IInput& operator=(const IInput&) = delete;   

    // move ok
    IInput(IInput&&) noexcept = default;
    IInput& operator=(IInput&&) noexcept = default;

    virtual bool IsKeyDown(int _keycode) const = 0;
    virtual bool IsMouseButtonDown(int _button) const = 0;
    virtual void GetMousePosition(float& _x, float& _y) const = 0;
};
