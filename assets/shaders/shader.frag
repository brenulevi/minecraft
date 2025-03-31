#version 330 core

in vec2 v_tex_coord;

uniform sampler2D u_tex;

out vec4 a_color;

void main()
{
    a_color = texture(u_tex, v_tex_coord);
}