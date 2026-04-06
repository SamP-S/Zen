# Zen Engine

## Architecture

Zen Engine follows a layered architecture:

### Layer 1: Core (zen::core)
- Memory management
- Containers & data structures
- Math (vectors, matrices, quaternions)
- UUID generation
- Timer & time management
- Logging interface
- Linear algebra interface

### Layer 2: Modules (zen::modules::<module_name>)
- Graphics: Rendering, shaders, textures, meshes
- Audio: Sound playback, mixing, spatial audio
- Input: Keyboard, mouse, gamepad, touch
- Window: Cross-platform window management
- Physics: Collision detection & response
- Networking: Client-server communication

### Layer 3: Engine (zen::engine::<system>)
- Runtime: Game loop systems
- Editor: Content creation tools
- DevTools: Asset pipeline, compilers
- Shared: Engine-only utilities

### Layer 4: Projects
- Sandbox: Testing environment
- Sample Game: Complete example
- User Project Template: Starter template

## Project Structure

```
zen/
│
├── CMakeLists.txt
├── docs/
├── scripts/                  # build scripts, tooling helpers
├── third_party/              # vendored deps (if not using package manager)
│
├── core/                     # Layer 1
│   ├── include/core/
│   ├── src/
│   ├── tests/
│   └── CMakeLists.txt
│
├── modules/                  # Layer 2
│   ├── graphics/
│   │   ├── include/graphics/
│   │   ├── src/
│   │   ├── tests/
│   │   └── CMakeLists.txt
│   │
│   ├── audio/
│   ├── input/
│   ├── window/
│   ├── physics/
│   └── networking/
│
├── engine/                   # Layer 3
│   ├── runtime/              # Headless / game runtime
│   ├── editor/               # Editor application
│   ├── devtools/             # Asset pipeline, compilers
│   ├── shared/               # Engine-only shared logic
│   └── CMakeLists.txt
│
├── projects/                 # Layer 4
│   ├── sandbox/
│   ├── sample_game/
│   └── user_project_template/
│
└── tools/                    # CLI tools not part of runtime
```

## Build Instructions

### Full Build
```bash
./compile.sh          # Standard build (Debug)
./compile.sh clean    # Clean then rebuild
```

### Manual CMake Commands
```bash
cmake -S . -B build   # Configure
cmake --build build   # Build
cmake --build build --target install  # Install
```

### Build Options
Toggle these in CMakeLists.txt or pass to cmake:
- `BUILD_CORE`: Build core library (ON by default)
- `BUILD_MODULES`: Build all modules (ON by default)
- `BUILD_ENGINE`: Build engine targets (OFF by default)
- `BUILD_PROJECTS`: Build sample projects (OFF by default)
- `BUILD_EXAMPLES`: Build example apps (OFF by default)