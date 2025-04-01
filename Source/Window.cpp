#include "Window.h"

Window::Window(int width, int height, const char *title, bool vsync)
    : _Width(width), _Height(height), _Title(title), _Vsync(vsync)
{
    _Ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(_Ptr);
    glfwSetWindowUserPointer(_Ptr, this);
    
    glfwSwapInterval(vsync);
}

Window::~Window()
{
    glfwDestroyWindow(_Ptr);
}

void Window::treatMessages()
{
    glfwPollEvents();
}

void Window::present()
{
    glfwSwapBuffers(_Ptr);
}

void Window::setCloseCallback(std::function<void()> f)
{
    _CloseCallback = f;

    glfwSetWindowCloseCallback(_Ptr, [](GLFWwindow* window) {
        Window* wnd = (Window*)glfwGetWindowUserPointer(window);
        wnd->_CloseCallback();
    });
}

void Window::setResizeCallback(std::function<void(int, int)> f)
{
    _ResizeCallback = f;

    glfwSetFramebufferSizeCallback(_Ptr, [](GLFWwindow* window, int width, int height) {
        Window* wnd = (Window*)glfwGetWindowUserPointer(window);
        wnd->_Width = width;
        wnd->_Height = height;
        wnd->_ResizeCallback(width, height);
    });
}
