#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
    static void init();
    static void update();

    static bool get_key_down(int key);
    static bool get_key(int key);
    static bool get_key_up(int key);

private:
    static bool _current_key[GLFW_KEY_LAST];
    static bool _previous_key[GLFW_KEY_LAST];
};