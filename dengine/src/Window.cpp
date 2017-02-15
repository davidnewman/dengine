#include "Core.h"

using namespace dengine;

struct Window::Impl {
    SDL_Window* pWindow;

    ~Impl() {
        SDL_DestroyWindow(pWindow);
    }
};

Window::Window(std::string title,
               int x, int y,
               int w, int h,
               SDL_WindowFlags flags) : pImpl{std::make_unique<Impl>()} {

    pImpl->pWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!pImpl->pWindow) throw SdlException();
}

Window::~Window() = default;

std::shared_ptr<Surface> Window::window_surface() const {
    auto sp = SDL_GetWindowSurface(pImpl->pWindow);
    std::shared_ptr<Surface> s = Surface::create(sp); 

    return s; 
}

void Window::update() {
    SDL_UpdateWindowSurface(pImpl->pWindow);
}

unsigned int Window::id() {
    return SDL_GetWindowID(pImpl->pWindow);
}
