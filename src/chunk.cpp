#include "chunk.h"

Chunk::Chunk(const glm::vec3 position)
    : _position(position)
{
    VertexLayout layout = get_layout();
    _mesh = new Mesh(layout);
}

Chunk::~Chunk()
{
    if (_mesh)
        delete _mesh;
}

void Chunk::generate_blocks()
{
    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                _blocks[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Z] = Stone; // air
            }
        }
    }
}

void Chunk::generate_mesh()
{
    _vertices.clear();
    _indices.clear();

    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                if (_blocks[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Z] == Air)
                    continue;

                bool visible_faces[6];
                visible_faces[0] = is_face_visible(x, y + 1, z); // top
                visible_faces[1] = is_face_visible(x, y - 1, z); // bottom
                visible_faces[2] = is_face_visible(x - 1, y, z); // left
                visible_faces[3] = is_face_visible(x + 1, y, z); // right
                visible_faces[4] = is_face_visible(x, y, z - 1); // front
                visible_faces[5] = is_face_visible(x, y, z + 1); // back

                for (int i = 0; i < 6; i++)
                {
                    if (visible_faces[i])
                        add_face_to_mesh(x, y, z, i);
                }
            }
        }
    }

    _mesh->add_vertices(_vertices.data(), _vertices.size() * sizeof(ChunkVertex));
    _mesh->add_indices(_indices.data(), _indices.size() * sizeof(unsigned int));
}

glm::vec3 &Chunk::get_position()
{
    return _position;
}

BlockType &Chunk::get_block_at(int x, int y, int z)
{
    return _blocks[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y];
}

Mesh &Chunk::get_mesh()
{
    return *_mesh;
}

bool Chunk::is_face_visible(int neighbor_x, int neighbor_y, int neighbor_z)
{
    if (neighbor_x < 0 || neighbor_x >= CHUNK_SIZE_X || neighbor_y < 0 || neighbor_y >= CHUNK_SIZE_Y || neighbor_z < 0 || neighbor_z >= CHUNK_SIZE_Z)
        return true;

    return _blocks[neighbor_x + neighbor_y * CHUNK_SIZE_X + neighbor_z * CHUNK_SIZE_X * CHUNK_SIZE_Y] == Air;
}

void Chunk::add_face_to_mesh(int x, int y, int z, int face_index)
{
    if (face_index == 0) // top
    {
        _vertices.push_back({{x, y + 1, z}, {0.0f, 0.0f}});
        _vertices.push_back({{x, y + 1, z + 1}, {0.0f, 1.0f}});
        _vertices.push_back({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
        _vertices.push_back({{x + 1, y + 1, z}, {1.0f, 0.0f}});
    }
    else if (face_index == 1) // bottom
    {
        _vertices.push_back({{x, y, z}, {0.0f, 0.0f}});
        _vertices.push_back({{x, y, z + 1}, {0.0f, 1.0f}});
        _vertices.push_back({{x + 1, y, z + 1}, {1.0f, 1.0f}});
        _vertices.push_back({{x + 1, y, z}, {1.0f, 0.0f}});
    }
    else if (face_index == 2) // left
    {
        _vertices.push_back({{x, y, z}, {0.0f, 0.0f}});
        _vertices.push_back({{x, y, z + 1}, {1.0f, 0.0f}});
        _vertices.push_back({{x, y + 1, z + 1}, {1.0f, 1.0f}});
        _vertices.push_back({{x, y + 1, z}, {0.0f, 1.0f}});
    }
    else if (face_index == 3) // right
    {
        _vertices.push_back({{x + 1, y, z}, {0.0f, 0.0f}});
        _vertices.push_back({{x + 1, y, z + 1}, {1.0f, 0.0f}});
        _vertices.push_back({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
        _vertices.push_back({{x + 1, y + 1, z}, {0.0f, 1.0f}});
    }
    else if (face_index == 4) // front
    {
        _vertices.push_back({{x, y, z}, {0.0f, 0.0f}});
        _vertices.push_back({{x, y + 1, z}, {0.0f, 1.0f}});
        _vertices.push_back({{x + 1, y + 1, z}, {1.0f, 1.0f}});
        _vertices.push_back({{x + 1, y, z}, {1.0f, 0.0f}});
    }
    else if (face_index == 5) // back
    {
        _vertices.push_back({{x, y, z + 1}, {0.0f, 0.0f}});
        _vertices.push_back({{x, y + 1, z + 1}, {0.0f, 1.0f}});
        _vertices.push_back({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
        _vertices.push_back({{x + 1, y, z + 1}, {1.0f, 0.0f}});
    }

    unsigned int vertices_count = _vertices.size();
    _indices.push_back(vertices_count - 4);
    _indices.push_back(vertices_count - 3);
    _indices.push_back(vertices_count - 2);

    _indices.push_back(vertices_count - 4);
    _indices.push_back(vertices_count - 2);
    _indices.push_back(vertices_count - 1);
}

VertexLayout Chunk::get_layout()
{
    VertexLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    return layout;
}
