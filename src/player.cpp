#include "player.h"

#include <glm/gtc/matrix_transform.hpp>

#include "input.h"

Player::Player()
    : position(0.0f), rotation(0.0f), fov(60.0f), near_plane(0.1f), far_plane(1000.0f)
{
    move_speed = 5.0f;
    view_speed = 0.1f;
    _last_mouse_x = 0.0f;
    _last_mouse_y = 0.0f;

    Input::set_cursor_mode(GLFW_CURSOR_DISABLED);
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

    float mouse_x = Input::get_mouse_x_pos();
    float mouse_y = Input::get_mouse_y_pos();

    float delta_x = mouse_x - _last_mouse_x;
    float delta_y = _last_mouse_y - mouse_y;

    _last_mouse_x = mouse_x;
    _last_mouse_y = mouse_y;

    rotation.x += delta_y * view_speed;
    rotation.y += delta_x * view_speed;

    if(rotation.x >= 89.0f)
        rotation.x = 89.0f;
    else if(rotation.x <= -89.0f)
        rotation.x = -89.0f;
}

glm::mat4 Player::get_proj_matrix(float aspect_ratio)
{
    return glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
}

glm::mat4 Player::get_view_matrix()
{
    return glm::lookAt(position, position + forward, up);
}
