#pragma once

#include <glm/glm.hpp>

class Player
{
public:
    Player();

    void update(float dt);

    glm::mat4 get_proj_matrix(float aspect_ratio);
    glm::mat4 get_view_matrix();

public:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    float fov;
    float near_plane;
    float far_plane;

    float move_speed;
    float view_speed;

private:
    float _last_mouse_x;
    float _last_mouse_y;
};