#pragma once

#include "Window.h"
#include "Rendering/Renderer.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

    inline Window &getWindow() { return *_Window; }
    inline Renderer &getRenderer() { return *_Renderer; }

private:
    void close();
    void resize(int width, int height);

private:
    Window *_Window;
    Renderer *_Renderer;

    bool _IsRunning;

    static Game *s_Instance;
};