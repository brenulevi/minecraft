#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
    Window() = default;

public:
    static void create(int width, int height, const char* title);
    static void destroy();

    static void update();

    static bool is_open();

    static float get_aspect_ratio();

private:
    static GLFWwindow* _ptr;
    static int _width;
    static int _height;
    static const char* _title;
};