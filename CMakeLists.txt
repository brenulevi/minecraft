cmake_minimum_required(VERSION 3.10)

project(minecraft)

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(
    minecraft
    
    Source/Main.cpp
    Source/Game.cpp
    Source/Window.cpp
    
    Source/Rendering/Renderer.cpp
    Source/Rendering/Shader.cpp
    Source/Rendering/VertexBuffer.cpp
    Source/Rendering/VertexLayout.cpp
    Source/Rendering/VertexArray.cpp
    
    Source/glad.c
    Source/stb_image.cpp
)

target_link_libraries(minecraft PUBLIC glfw)

target_include_directories(minecraft PUBLIC
    ${CMAKE_SOURCE_DIR}/Source/
    ${CMAKE_SOURCE_DIR}/Dependencies/glad/include
    ${CMAKE_SOURCE_DIR}/Dependencies/stb_image/include
    ${CMAKE_SOURCE_DIR}/Dependencies/glm/include
)