#pragma once

#include "shader.h"
#include "texture.h"
#include "mesh.h"

class Renderer
{
private:
    Renderer() = default;

public:
    static void init();
    static void shutdown();

    static void clear();

    static void draw(const glm::mat4& model, Mesh& mesh);

    static void set_projection_matrix(const glm::mat4& proj);
    static void set_view_matrix(const glm::mat4& view);

private:
    static Shader* _shader;
    static Texture* _texture;
};