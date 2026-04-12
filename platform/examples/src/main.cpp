#include "zen/platform/platform.hpp"

int main() {
    auto platform = createPlatform(Backend::GLFW); // swap freely

    platform.window->create("My App", 800, 600);
    platform.window->setEventCallback([](const Event& e) {
        if (e.type == EventType::WindowResize)
            glViewport(0, 0, e.resize.width, e.resize.height);
    });

    while (!platform.window->shouldClose()) {
        platform.window->pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        platform.window->swapBuffers();
    }

    platform.window->destroy();
}
