#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "gamestates.hpp"

class Window {
public:
    Window(std::string windowName, int windowWidth, int windowHeight, SDL_WindowFlags sdlWindowFlags);
    ~Window();
    bool init();

    void handleInput(GameState& gameState);
    void clear();
    void present();
    
    int getWidth() const { return m_windowWidth; }
    int getHeight() const { return m_windowHeight; }
    SDL_Window* getWindow() const { return m_window; }

    bool wasResized();

private:
    std::string m_windowName;
    int m_windowWidth;
    int m_windowHeight;
    bool m_resized;
    SDL_WindowFlags m_sdlWindowFlags;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    void resizeWindow(int windowWidth, int windowHeight);
};