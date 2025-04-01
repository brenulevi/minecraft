#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    unsigned int vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);

    _Id = glCreateProgram();
    glAttachShader(_Id, vertexShader);
    glAttachShader(_Id, fragmentShader);
    glLinkProgram(_Id);

    checkLinkStatus();

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_Id);
}

void Shader::bind()
{
    glUseProgram(_Id);
}

unsigned int Shader::createShader(const char *path, GLenum type)
{
    unsigned int shader = glCreateShader(type);

    std::ifstream file(path);
    
    if(file.is_open())
    {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        std::string str = ss.str();
        const char* source = str.c_str();

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
    }
    else
    {
        std::cout << "Invalid shader file:" << path << std::endl;
    }

    checkCompileStatus(shader);

    return shader;
}

int Shader::getUniformLocation(const std::string &name)
{
    if(_UniformsLocation.find(name) == _UniformsLocation.end())
    {
        _UniformsLocation[name] = glGetUniformLocation(_Id, name.c_str());
    }

    return _UniformsLocation[name];
}

void Shader::checkCompileStatus(unsigned int shader)
{
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

void Shader::checkLinkStatus()
{
    int result;
    glGetProgramiv(_Id, GL_LINK_STATUS, &result);
    if (!result)
    {
        char infoLog[512];
        glGetProgramInfoLog(_Id, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}
