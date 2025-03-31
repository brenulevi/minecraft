#include "input.h"

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
        _current_key[i] = glfwGetKey(glfwGetCurrentContext(), i);
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
