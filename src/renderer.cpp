#include "renderer.h"

#include <glad/glad.h>

Shader* Renderer::_shader = nullptr;
Texture* Renderer::_texture = nullptr;

void Renderer::init()
{
    gladLoadGL();

    _shader = new Shader("/home/breno/dev/minecraft/assets/shaders/shader.vert", "/home/breno/dev/minecraft/assets/shaders/shader.frag");

    _texture = new Texture;
    _texture->load_image("/home/breno/dev/minecraft/assets/textures/barrel_side.png");

    glEnable(GL_DEPTH_TEST);
}

void Renderer::shutdown()
{
    delete _texture;

    delete _shader;
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const glm::mat4 &model, Mesh &mesh)
{
    _shader->use();

    _texture->bind(0);
    _shader->set_uniform("u_tex", 0);

    _shader->set_uniform("u_model", model);

    mesh.bind();
    glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::set_projection_matrix(const glm::mat4 &proj)
{
    _shader->use();
    _shader->set_uniform("u_proj", proj);
}

void Renderer::set_view_matrix(const glm::mat4 &view)
{
    _shader->use();
    _shader->set_uniform("u_view", view);
}
