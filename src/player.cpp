#include "player.h"

#include <glm/gtc/matrix_transform.hpp>

#include "input.h"

Player::Player()
    : position(0.0f), rotation(0.0f), fov(60.0f), near_plane(0.1f), far_plane(1000.0f)
{
    move_speed = 5.0f;
}

void Player::update(float dt)
{
    forward.x = cos(glm::radians(rotation.y - 90.0f)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y - 90.0f)) * cos(glm::radians(rotation.x));
    forward = glm::normalize(forward);

    right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, forward));

    glm::vec3 move_dir(0.0f);

    if (Input::get_key(GLFW_KEY_W))
        move_dir += forward;
    if (Input::get_key(GLFW_KEY_S))
        move_dir -= forward;
    if (Input::get_key(GLFW_KEY_A))
        move_dir -= right;
    if (Input::get_key(GLFW_KEY_D))
        move_dir += right;
    if(Input::get_key(GLFW_KEY_SPACE))
        move_dir += glm::vec3(0.0f, 1.0f, 0.0f);
    if(Input::get_key(GLFW_KEY_LEFT_SHIFT))
        move_dir -= glm::vec3(0.0f, 1.0f, 0.0f);

    if(glm::length(move_dir) != 0.0f)
        move_dir = glm::normalize(move_dir);

    position += move_dir * dt * move_speed;
}

glm::mat4 Player::get_proj_matrix(float aspect_ratio)
{
    return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
}

glm::mat4 Player::get_view_matrix()
{
    return glm::lookAt(position, position + forward, up);
}
