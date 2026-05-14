#include "core/window.hpp"

Window::Window(std::string windowName, int windowWidth, int windowHeight, SDL_WindowFlags sdlWindowFlags)
    : m_windowName(windowName), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_sdlWindowFlags(sdlWindowFlags) {}

Window::~Window() {
    SDL_GL_DestroyContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // Add error logger windowFailed()
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(m_windowName.c_str(), m_windowWidth, m_windowHeight, m_sdlWindowFlags | SDL_WINDOW_OPENGL);
    if (!m_window) {
        // Add error logger failedToCreateWindow()
        return false;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        // Add error logger failedToCreateGLContext();
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        // Add erro logger gladFailedToLoadGLFunctions();
        return false;
    }

    glViewport(0, 0, m_windowWidth, m_windowHeight);
    SDL_SetWindowRelativeMouseMode(m_window, true);

    return true;
}

void Window::handleInput(GameState& gameState) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                gameState = GameState::QUIT;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                m_resized = true;
                resizeWindow(event.window.data1, event.window.data2);
                break;
            case SDL_EVENT_KEY_DOWN:
                if (SDL_SCANCODE_ESCAPE == event.key.scancode) {
                    if (gameState == GameState::RUNNING) {
                        gameState = GameState::PAUSED;  
                        SDL_SetWindowRelativeMouseMode(m_window, false);
                    } else if (gameState == GameState::PAUSED) { 
                        gameState = GameState::RUNNING;
                        SDL_SetWindowRelativeMouseMode(m_window, true);
                        m_firstMouse = true;
                    }
                }
                else if (SDL_SCANCODE_0 == event.key.scancode) {
                    // Toggle fullscreen mode
                    Uint32 flags = SDL_GetWindowFlags(m_window);
                    if (flags & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(m_window, 0);
                        // only show cursor if paused
                        if (gameState == GameState::PAUSED)
                            SDL_SetWindowRelativeMouseMode(m_window, false);
                    } else {
                        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
                        if (gameState == GameState::RUNNING)
                            SDL_SetWindowRelativeMouseMode(m_window, true);
                    }
                    m_firstMouse = true;
                }
                break;
        }
    }
}

const bool* Window::getKeyboardState(int *numKeys) {
    return SDL_GetKeyboardState(numKeys);
}

void Window::clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark grey background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::present() {
    SDL_GL_SwapWindow(m_window);
}

bool Window::wasResized() {
    if (m_resized) {
        m_resized = false;
        return true;
    }

    return false;
}

glm::vec2 Window::getMouseDelta() {
    float deltaX, deltaY;
    SDL_GetRelativeMouseState(&deltaX, &deltaY);

    if (m_firstMouse) {
        m_firstMouse = false;
        return glm::vec2(0.0f);
    }

    return glm::vec2(deltaX, deltaY);
}


void Window::resizeWindow(int windowWidth, int windowHeight) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    glViewport(0, 0, windowWidth, windowHeight);
}