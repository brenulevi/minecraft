#pragma once

#include <GLFW/glfw3.h>
#include <functional>

class Window
{
public:
    Window(int width, int height, const char* title, bool vsync);
    ~Window();

    void treatMessages();
    void present();

    void setCloseCallback(std::function<void()> f);
    void setResizeCallback(std::function<void(int, int)> f);

    inline GLFWwindow* getNative() { return _Ptr; }
    inline float getAspectRatio() { return (float)_Width / (float)_Height; }

private:
    GLFWwindow* _Ptr;
    int _Width;
    int _Height;
    const char* _Title;
    bool _Vsync;

    std::function<void()> _CloseCallback;
    std::function<void(int, int)> _ResizeCallback;
};