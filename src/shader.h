#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    void use();

    void set_uniform(const std::string& name, int value);
    void set_uniform(const std::string& name, const glm::mat4& value);

private:
    unsigned int create_shader(const char* path, int type);
    int get_uniform_location(const std::string& name);

private:
    unsigned int _id;
    std::map<std::string, int> _uniforms;
};