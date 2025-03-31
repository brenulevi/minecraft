#include "shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
    unsigned int vertex_shader = create_shader(vertex_path, GL_VERTEX_SHADER);
    unsigned int fragment_shader = create_shader(fragment_path, GL_FRAGMENT_SHADER);

    _id = glCreateProgram();
    glAttachShader(_id, vertex_shader);
    glAttachShader(_id, fragment_shader);
    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        char buf[512];
        glGetProgramInfoLog(_id, 512, nullptr, buf);
        std::cout << buf << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::use()
{
    glUseProgram(_id);
}

void Shader::set_uniform(const std::string &name, int value)
{
    glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform(const std::string &name, const glm::mat4 &value)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

unsigned int Shader::create_shader(const char *path, int type)
{
    unsigned int shader = glCreateShader(type);

    std::ifstream shader_file(path);

    if(shader_file.is_open())
    {
        std::stringstream ss;
        ss << shader_file.rdbuf();
        std::string str = ss.str();
        const char* source = str.c_str();
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
    }
    else
    {
        std::cout << "invalid shader path: " << path << std::endl;
    }

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char buf[512];
        glGetShaderInfoLog(shader, 512, nullptr, buf);
        std::cout << buf << std::endl;
    }

    return shader;
}

int Shader::get_uniform_location(const std::string &name)
{
    if(_uniforms.find(name) == _uniforms.end())
    {
        _uniforms[name] = glGetUniformLocation(_id, name.c_str());
    }

    return _uniforms[name];
}
