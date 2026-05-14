cmake_minimum_required(VERSION 3.20)
project(PlanetSimulation VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/core/engine.cpp
    src/core/window.cpp
    src/rendering/renderer.cpp
    src/rendering/shader.cpp
    src/rendering/mesh.cpp
    src/rendering/texture.cpp
    src/rendering/skybox.cpp
    src/rendering/camera.cpp
    src/scenes/scene.cpp
    src/scenes/simulation_scene.cpp
    src/scenes/binary_star_scene.cpp
    src/scenes/figure_eight_scene.cpp
    src/objects/gameobject.cpp
    src/objects/planet.cpp
    src/physics/physics.cpp
    src/managers/mesh_manager.cpp
    src/managers/texture_manager.cpp
    src/managers/scene_manager.cpp
    src/utils/obj_loader.cpp
    src/utils/error_logger.cpp
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