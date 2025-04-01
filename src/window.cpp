#include "window.h"

GLFWwindow* Window::_ptr = nullptr;
int Window::_width = 0;
int Window::_height = 0;
const char* Window::_title = nullptr;

void Window::create(int width, int height, const char *title)
{
    _width = width;
    _height = height;
    _title = title;

    _ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(_ptr);

    const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(_ptr, (vid_mode->width - width) / 2.0f, (vid_mode->height - height) / 2.0f);
}

void Window::destroy()
{
    glfwDestroyWindow(_ptr);
}

void Window::update()
{
    glfwSwapBuffers(_ptr);
    glfwPollEvents();
}

void Window::close()
{
    glfwSetWindowShouldClose(_ptr, true);
}

bool Window::is_open()
{
    return !glfwWindowShouldClose(_ptr);
}

GLFWwindow *Window::get_native()
{
    return _ptr;
}

float Window::get_aspect_ratio()
{
    return (float)_width / (float)_height;
}
