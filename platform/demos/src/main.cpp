#include "zen/platform/platform.hpp"

using namespace zen::platform;

int main() {
    // init platform
    auto& platform = Platform::get();
    platform.init(PlatformBackendAPI::SDL2, GraphicsAPI::OpenGL);

    WindowHandle h = platform.createWindow({ "My App", 800, 600 });

    while (!platform.shouldClose()) {
        platform.pollEvents();

        // render here...

        platform.swapBuffers(h);
    }

    platform.destroyWindow(h);
    platform.shutdown();
}
