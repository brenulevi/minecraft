#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "renderer.h"
#include "input.h"

#include "player.h"
#include "chunk.h"
#include "mesh.h"

int main(int argc, char** argv)
{
    std::cout << "Hello World\n" << argv[0] << std::endl;

    glfwInit();

    Window::create(800, 600, "minecraft");
    Renderer::init();
    Input::init();

    Player player;

    VertexLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    Mesh* mesh = new Mesh(layout);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    mesh->add_vertices(vertices, sizeof(vertices));
    mesh->add_indices(indices, sizeof(indices));

    std::vector<Chunk*> chunks;
    for(int x = -2; x <= 2; x++)
    {
        for(int z = -2; z <= 2; z++)
        {
            Chunk* chunk = new Chunk(glm::ivec2(x, z));
            chunks.push_back(chunk);
            chunk->generate_mesh();
        }
    }
    
    float total_time = 0.0f;
    while(Window::is_open())
    {
        float delta_time = glfwGetTime() - total_time;
        total_time += delta_time;

        Input::update();

        if(Input::get_key_down(GLFW_KEY_ESCAPE))
            Window::close();

        player.update(delta_time);
        
        Renderer::clear();
        
        Renderer::set_projection_matrix(player.get_proj_matrix(Window::get_aspect_ratio()));
        Renderer::set_view_matrix(player.get_view_matrix());

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
            Renderer::draw(model, *mesh);
        }

        for(auto chunk : chunks)
        {
            auto& chunk_pos = chunk->get_position();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(chunk_pos.x * CHUNK_SIZE_X, 0.0f, chunk_pos.y * CHUNK_SIZE_Z));
            Renderer::draw(model, chunk->get_mesh());
        }

        Window::update();
    }

    for(auto chunk : chunks)
    {
        delete chunk;
    }

    delete mesh;

    Renderer::shutdown();
    Window::destroy();

    glfwTerminate();
    
    return 0;
}