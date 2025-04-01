#include "Renderer.h"

#include <glad/glad.h>

Renderer::Renderer()
{
    _Shader = new Shader("../Assets/Shaders/Basic.vert", "../Assets/Shaders/Basic.frag");

    glClearColor(0.0f, 0.2f, 0.32f, 1.0f);
}

Renderer::~Renderer()
{
    delete _Shader;
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawArray(VertexArray &va, unsigned int count)
{
    _Shader->bind();
    va.bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
