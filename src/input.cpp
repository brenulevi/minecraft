#include "input.h"

#include "window.h"

bool Input::_current_key[GLFW_KEY_LAST];
bool Input::_previous_key[GLFW_KEY_LAST];

void Input::init()
{
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _current_key[i] = false;
        _previous_key[i] = false;
    }
}

void Input::update()
{
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _previous_key[i] = _current_key[i];
        _current_key[i] = glfwGetKey(Window::get_native(), i);
    }
}

bool Input::get_key_down(int key)
{
    return _current_key[key] && !_previous_key[key];
}

bool Input::get_key(int key)
{
    return _current_key[key];
}

bool Input::get_key_up(int key)
{
    return !_current_key[key];
}

float Input::get_mouse_x_pos()
{
    double x;
    glfwGetCursorPos(Window::get_native(), &x, nullptr);
    return (float)x;
}

float Input::get_mouse_y_pos()
{
    double y;
    glfwGetCursorPos(Window::get_native(), nullptr, &y);
    return (float)y;
}

void Input::set_cursor_mode(int mode)
{
    glfwSetInputMode(Window::get_native(), GLFW_CURSOR, mode);
}

int Input::get_cursor_mode()
{
    return glfwGetInputMode(Window::get_native(), GLFW_CURSOR);
}
