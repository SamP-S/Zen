#pragma once

#include <cstdint>

namespace zen {

namespace platform {

// ---------------------------------------------------------------------------
// Keyboard
// 
// Layout-independent key codes for keyboard input, based on SDL_Keycode values.
// SDL_KeyCode values mirror USB HID usage codes so direct casting should work.
// ---------------------------------------------------------------------------

enum class KeyCode : uint32_t
{
    Unknown         = 0,

    // ── Printable ASCII ─────────────────────────────────────────────────────
    Space           = ' ',
    Apostrophe      = '\'',
    Comma           = ',',
    Minus           = '-',
    Period          = '.',
    Slash           = '/',

    Num0            = '0',
    Num1            = '1',
    Num2            = '2',
    Num3            = '3',
    Num4            = '4',
    Num5            = '5',
    Num6            = '6',
    Num7            = '7',
    Num8            = '8',
    Num9            = '9',

    Semicolon       = ';',
    Equals          = '=',

    A               = 'a',
    B               = 'b',
    C               = 'c',
    D               = 'd',
    E               = 'e',
    F               = 'f',
    G               = 'g',
    H               = 'h',
    I               = 'i',
    J               = 'j',
    K               = 'k',
    L               = 'l',
    M               = 'm',
    N               = 'n',
    O               = 'o',
    P               = 'p',
    Q               = 'q',
    R               = 'r',
    S               = 's',
    T               = 't',
    U               = 'u',
    V               = 'v',
    W               = 'w',
    X               = 'x',
    Y               = 'y',
    Z               = 'z',

    BracketLeft     = '[',
    Backslash       = '\\',
    BracketRight    = ']',
    Grave           = '`',

    // ── Function keys ───────────────────────────────────────────────────────
    // SDL SDLK_* values for non-ASCII keys use bit 30 set (0x40000000 base).
    F1              = 0x4000003A,
    F2              = 0x4000003B,
    F3              = 0x4000003C,
    F4              = 0x4000003D,
    F5              = 0x4000003E,
    F6              = 0x4000003F,
    F7              = 0x40000040,
    F8              = 0x40000041,
    F9              = 0x40000042,
    F10             = 0x40000043,
    F11             = 0x40000044,
    F12             = 0x40000045,
    F13             = 0x40000068,
    F14             = 0x40000069,
    F15             = 0x4000006A,
    F16             = 0x4000006B,
    F17             = 0x4000006C,
    F18             = 0x4000006D,
    F19             = 0x4000006E,
    F20             = 0x4000006F,
    F21             = 0x40000070,
    F22             = 0x40000071,
    F23             = 0x40000072,
    F24             = 0x40000073,

    // ── Navigation & editing ────────────────────────────────────────────────
    Escape          = '\033',
    Enter           = '\r',
    Tab             = '\t',
    Backspace       = '\b',
    Insert          = 0x40000049,
    Delete          = 0x4000004C,
    Home            = 0x4000004A,
    End             = 0x4000004D,
    PageUp          = 0x4000004B,
    PageDown        = 0x4000004E,

    // ── Arrow keys ──────────────────────────────────────────────────────────
    ArrowRight      = 0x4000004F,
    ArrowLeft       = 0x40000050,
    ArrowDown       = 0x40000051,
    ArrowUp         = 0x40000052,

    // ── Modifier keys ───────────────────────────────────────────────────────
    LShift          = 0x400000E1,
    RShift          = 0x400000E5,
    LCtrl           = 0x400000E0,
    RCtrl           = 0x400000E4,
    LAlt            = 0x400000E2,
    RAlt            = 0x400000E3,   // AltGr on EU keyboards
    LSuper          = 0x400000E3,   // Left  Windows / Cmd
    RSuper          = 0x400000E7,   // Right Windows / Cmd
    Menu            = 0x40000076,
    CapsLock        = 0x40000039,
    NumLock         = 0x40000053,
    ScrollLock      = 0x40000047,

    // ── Numpad ──────────────────────────────────────────────────────────────
    KP0             = 0x40000062,
    KP1             = 0x40000059,
    KP2             = 0x4000005A,
    KP3             = 0x4000005B,
    KP4             = 0x4000005C,
    KP5             = 0x4000005D,
    KP6             = 0x4000005E,
    KP7             = 0x4000005F,
    KP8             = 0x40000060,
    KP9             = 0x40000061,
    KPDecimal       = 0x40000063,
    KPDivide        = 0x40000054,
    KPMultiply      = 0x40000055,
    KPMinus         = 0x40000056,
    KPPlus          = 0x40000057,
    KPEnter         = 0x40000058,
    KPEquals        = 0x40000067,

    // ── Media & system ──────────────────────────────────────────────────────
    PrintScreen     = 0x40000046,
    Pause           = 0x40000048,

    MediaPlay       = 0x400000B0,
    MediaStop       = 0x400000B1,
    MediaNext       = 0x400000B5,
    MediaPrev       = 0x400000B6,
    VolumeMute      = 0x400000B4,
    VolumeUp        = 0x40000080,
    VolumeDown      = 0x40000081,
};

// ---------------------------------------------------------------------------
// KeyMod
// 
// Modifier key bitmask for keyboard input, based on SDL_Keymod values.
// ---------------------------------------------------------------------------

enum class KeyMod : uint16_t {
    None        = 0x0000,

    LShift      = 0x0001,
    RShift      = 0x0002,
    Shift       = LShift | RShift,

    LCtrl       = 0x0040,
    RCtrl       = 0x0080,
    Ctrl        = LCtrl  | RCtrl,

    LAlt        = 0x0100,
    RAlt        = 0x0200,
    Alt         = LAlt   | RAlt,

    LSuper      = 0x0400,
    RSuper      = 0x0800,
    Super       = LSuper | RSuper,

    CapsLock    = 0x2000,
    NumLock     = 0x1000,
    ScrollLock  = 0x4000,
    
    // convenience combinations
    CtrlShift   = Ctrl | Shift,
    CtrlAlt     = Ctrl | Alt,
    AltShift    = Alt | Shift,
};

inline KeyMod  operator|(KeyMod  a, KeyMod b) {
    return static_cast<KeyMod>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}
inline KeyMod  operator&(KeyMod  a, KeyMod b) {
    return static_cast<KeyMod>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}
inline KeyMod& operator|=(KeyMod& a, KeyMod b) {
    a = a | b;
    return a;
}
inline bool hasMod(KeyMod a, KeyMod b) {
    return (a & b) != KeyMod::None;
}

struct KeyState {
    bool down       = false;
    bool pressed    = false;
    bool released   = false;
};

// ---------------------------------------------------------------------------
// Mouse
// ---------------------------------------------------------------------------

enum class MouseButton : uint8_t
{
    Unknown = 0,
    M1      = 1,    // LEFT
    M2      = 2,    // MIDDLE
    M3      = 3,    // RIGHT
    M4      = 4,    // THUMB-BACK
    M5      = 5,    // THUMB-FWD
    COUNT   = 6,
};

struct MouseState {
    float x = 0.0f, y = 0.0f;
    float dx = 0.0f, dy = 0.0f; // delta since last frame
    float scroll = 0.0f;        // delta scroll since last frame
    KeyState buttons[static_cast<uint8_t>(MouseButton::COUNT)];
};

// ---------------------------------------------------------------------------
// Utility
// 
// ASCII codes for debugging
// ---------------------------------------------------------------------------

constexpr const char* toString(KeyCode _key) {
    switch (_key) {
        case KeyCode::Space:        return "Space";
        case KeyCode::Apostrophe:   return "Apostrophe";
        case KeyCode::Comma:        return "Comma";
        case KeyCode::Minus:        return "Minus";
        case KeyCode::Period:       return "Period";
        case KeyCode::Slash:        return "Slash";
        case KeyCode::Num0:         return "0";
        case KeyCode::Num1:         return "1";
        case KeyCode::Num2:         return "2";
        case KeyCode::Num3:         return "3";
        case KeyCode::Num4:         return "4";
        case KeyCode::Num5:         return "5";
        case KeyCode::Num6:         return "6";
        case KeyCode::Num7:         return "7";
        case KeyCode::Num8:         return "8";
        case KeyCode::Num9:         return "9";
        case KeyCode::A:            return "A";
        case KeyCode::B:            return "B";
        case KeyCode::C:            return "C";
        case KeyCode::D:            return "D";
        case KeyCode::E:            return "E";
        case KeyCode::F:            return "F";
        case KeyCode::G:            return "G";
        case KeyCode::H:            return "H";
        case KeyCode::I:            return "I";
        case KeyCode::J:            return "J";
        case KeyCode::K:            return "K";
        case KeyCode::L:            return "L";
        case KeyCode::M:            return "M";
        case KeyCode::N:            return "N";
        case KeyCode::O:            return "O";
        case KeyCode::P:            return "P";
        case KeyCode::Q:            return "Q";
        case KeyCode::R:            return "R";
        case KeyCode::S:            return "S";
        case KeyCode::T:            return "T";
        case KeyCode::U:            return "U";
        case KeyCode::V:            return "V";
        case KeyCode::W:            return "W";
        case KeyCode::X:            return "X";
        case KeyCode::Y:            return "Y";
        case KeyCode::Z:            return "Z";
        case KeyCode::Escape:       return "Escape";
        case KeyCode::Enter:        return "Enter";
        case KeyCode::Tab:          return "Tab";
        case KeyCode::Backspace:    return "Backspace";
        case KeyCode::Insert:       return "Insert";
        case KeyCode::Delete:       return "Delete";
        case KeyCode::Home:         return "Home";
        case KeyCode::End:          return "End";
        case KeyCode::PageUp:       return "PageUp";
        case KeyCode::PageDown:     return "PageDown";
        case KeyCode::ArrowRight:   return "ArrowRight";
        case KeyCode::ArrowLeft:    return "ArrowLeft";
        case KeyCode::ArrowDown:    return "ArrowDown";
        case KeyCode::ArrowUp:      return "ArrowUp";
        case KeyCode::F1:           return "F1";
        case KeyCode::F2:           return "F2";
        case KeyCode::F3:           return "F3";
        case KeyCode::F4:           return "F4";
        case KeyCode::F5:           return "F5";
        case KeyCode::F6:           return "F6";
        case KeyCode::F7:           return "F7";
        case KeyCode::F8:           return "F8";
        case KeyCode::F9:           return "F9";
        case KeyCode::F10:          return "F10";
        case KeyCode::F11:          return "F11";
        case KeyCode::F12:          return "F12";
        case KeyCode::LShift:       return "LShift";
        case KeyCode::RShift:       return "RShift";
        case KeyCode::LCtrl:        return "LCtrl";
        case KeyCode::RCtrl:        return "RCtrl";
        case KeyCode::LAlt:         return "LAlt";
        case KeyCode::RAlt:         return "RAlt";
        case KeyCode::CapsLock:     return "CapsLock";
        case KeyCode::NumLock:      return "NumLock";
        case KeyCode::ScrollLock:   return "ScrollLock";
        case KeyCode::PrintScreen:  return "PrintScreen";
        case KeyCode::Pause:        return "Pause";
        case KeyCode::KP0:          return "KP0";
        case KeyCode::KP1:          return "KP1";
        case KeyCode::KP2:          return "KP2";
        case KeyCode::KP3:          return "KP3";
        case KeyCode::KP4:          return "KP4";
        case KeyCode::KP5:          return "KP5";
        case KeyCode::KP6:          return "KP6";
        case KeyCode::KP7:          return "KP7";
        case KeyCode::KP8:          return "KP8";
        case KeyCode::KP9:          return "KP9";
        case KeyCode::KPEnter:      return "KPEnter";
        case KeyCode::KPPlus:       return "KP+";
        case KeyCode::KPMinus:      return "KP-";
        case KeyCode::KPMultiply:   return "KP*";
        case KeyCode::KPDivide:     return "KP/";
        case KeyCode::KPDecimal:    return "KP.";
        case KeyCode::MediaPlay:    return "MediaPlay";
        case KeyCode::MediaStop:    return "MediaStop";
        case KeyCode::MediaNext:    return "MediaNext";
        case KeyCode::MediaPrev:    return "MediaPrev";
        case KeyCode::VolumeMute:   return "VolumeMute";
        case KeyCode::VolumeUp:     return "VolumeUp";
        case KeyCode::VolumeDown:   return "VolumeDown";
        default:                    return "KeyUnknown";
    }
}

constexpr const char* toString(MouseButton _btn) noexcept
{
    switch (_btn) {
        case MouseButton::M1:   return "MouseLeft";
        case MouseButton::M2:   return "MouseMiddle";
        case MouseButton::M3:   return "MouseRight";
        case MouseButton::M4:   return "Mouse4";
        case MouseButton::M5:   return "Mouse5";
        default:                return "MouseUnknown";
    }
}

} // namespace platform
    
} // namespace zen

