#include "Core.h"

using namespace dengine;

struct Surface::Impl {
    SDL_Surface* pSurface;
    ~Impl() {
        SDL_FreeSurface(pSurface);
    }
};

// public
Surface::~Surface() = default;

void Surface::fill_rect(const SDL_Rect* rect, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    SDL_FillRect(pImpl->pSurface, rect, SDL_MapRGBA(pImpl->pSurface->format, r, g, b, a));
}

void Surface::blit(const SDL_Rect* srcRect, std::shared_ptr<Surface> dst, SDL_Rect* dstRect) {
    SDL_BlitSurface(pImpl->pSurface, srcRect, dst->pImpl->pSurface, dstRect); 
}

// private
Surface::Surface(SDL_Surface* sp) : pImpl{std::make_unique<Surface::Impl>()} {
    pImpl->pSurface = sp;
}

Surface::Surface(std::string file) : pImpl{std::make_unique<Surface::Impl>()} {
    pImpl->pSurface = IMG_Load(file.c_str());
}

SDL_Surface* Surface::resource() {
    return pImpl->pSurface;
}
