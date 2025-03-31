cmake_minimum_required(VERSION 3.10)

project(minecraft)

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(
    minecraft
    src/main.cpp
    src/window.cpp
    src/renderer.cpp
    src/input.cpp
    src/shader.cpp
    src/mesh.cpp
    src/vertex_layout.cpp
    src/texture.cpp
    src/player.cpp
    src/chunk.cpp
    
    src/glad.c
    src/stb_image.cpp
)

target_link_libraries(minecraft PUBLIC glfw)

target_include_directories(minecraft PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_SOURCE_DIR}/dependencies/stb_image/include
    ${CMAKE_SOURCE_DIR}/dependencies/glm/include
)