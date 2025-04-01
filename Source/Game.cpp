#include "Game.h"

#include <iostream>
#include <glad/glad.h>

#include "Rendering/VertexArray.h"

Game* Game::s_Instance = nullptr;

Game::Game()
{
    if(s_Instance)
    {
        std::cout << "Game instance already running!!" << std::endl;
        return;
    }

    s_Instance = this;

    glfwInit();

    _Window = new Window(800, 600, "minecraft", false);
    _Window->setCloseCallback(std::bind(&Game::close, this));
    _Window->setResizeCallback(std::bind(&Game::resize, this, std::placeholders::_1, std::placeholders::_2));

    gladLoadGL();

    _Renderer = new Renderer;
}

Game::~Game()
{
    delete _Renderer;
    delete _Window;

    glfwTerminate();
}

void Game::run()
{
    VertexLayout layout;
    layout.add<float>(3);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexArray va;
    va.addVertexBuffer(layout, vb);

    while (_IsRunning)
    {
        _Window->treatMessages();

        _Renderer->clear();

        _Renderer->drawArray(va, 3);

        _Window->present();
    }
}

void Game::close()
{
    _IsRunning = false;
}

void Game::resize(int width, int height)
{
    _Renderer->resize(width, height);
}
