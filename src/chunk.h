#pragma once

#include <glm/glm.hpp>

#include "mesh.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

enum BlockType
{
    Air = 0,
    Stone = 1
};

struct ChunkVertex
{
    glm::vec3 position;
    glm::vec2 tex_coord;
};

class Chunk
{
public:
    Chunk(const glm::ivec2 position);
    ~Chunk();

    void generate_mesh();

    glm::ivec2& get_position();
    BlockType& get_block_at(int x, int y, int z);
    Mesh& get_mesh();

private:
    bool is_face_visible(int neighbor_x, int neighbor_y, int neighbor_z);
    void add_face_to_mesh(int x, int y, int z, int face_index);

    static VertexLayout get_layout();

private:
    glm::ivec2 _position;
    
    BlockType _blocks[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
    
    Mesh* _mesh;
    std::vector<ChunkVertex> _vertices;
    std::vector<unsigned int> _indices;
};