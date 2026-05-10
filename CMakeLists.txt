cmake_minimum_required(VERSION 3.20)
project(PlanetSimulation VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/engine.cpp
    src/window.cpp
    src/renderer.cpp
    src/mesh.cpp
    src/gameobject.cpp
    src/shader.cpp
    src/scene.cpp
    src/scene_manager.cpp
    src/simulation_scene.cpp
    src/cube.cpp
    src/camera.cpp
)

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    SDL3::SDL3
    glm::glm
)

target_include_directories(${PROJECT_NAME} PRIVATE
    include/
)

if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()