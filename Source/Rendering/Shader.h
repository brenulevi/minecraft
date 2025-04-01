#pragma once

#include <map>
#include <string>
#include <glad/glad.h>

class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void bind();

    inline void setUniform(const std::string &name, int value) { glUniform1i(getUniformLocation(name), value); }

private:
    unsigned int createShader(const char *path, GLenum type);
    int getUniformLocation(const std::string &name);

    void checkCompileStatus(unsigned int shader);
    void checkLinkStatus();

private:
    unsigned int _Id;
    std::map<std::string, int> _UniformsLocation;
};