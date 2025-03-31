#pragma once

class Texture
{
public:
    Texture();
    ~Texture();

    void load_image(const char* path);

    void set_filtering(int min, int mag);
    void set_wrapping(int s, int t);

    void bind(unsigned int slot);

private:
    unsigned int _id;
    int _width;
    int _height;
    int _channels;
};