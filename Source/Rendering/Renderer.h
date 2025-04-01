#pragma once

#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();

    void drawArray(VertexArray& va, unsigned int count);

    void resize(int width, int height);

private:
    Shader* _Shader;
};