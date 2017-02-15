#include "Renderer.h"

using namespace dengine;

struct Renderer::Impl {
    SDL_Renderer* pRenderer;
    ~Impl() {
        SDL_DestroyRenderer(pRenderer);
    }
};

// Texture
Renderer::Texture::Texture(SDL_Texture* t) {
    pTexture = t;
}

Renderer::Texture::~Texture() {
    SDL_DestroyTexture(pTexture);
}

SDL_Texture* Renderer::Texture::resource() {
    return pTexture;
}

// Public
Renderer::Renderer(unsigned int window_id,
                   int index,
                   unsigned int flags) : pImpl{std::make_unique<Impl>()} {
    auto window = SDL_GetWindowFromID(window_id);
    pImpl->pRenderer = SDL_CreateRenderer(window, index, flags);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(pImpl->pRenderer);
}

void Renderer::render() {
    SDL_RenderPresent(pImpl->pRenderer);
}

void Renderer::clear() {
    SDL_RenderClear(pImpl->pRenderer);
}

void Renderer::copy(std::shared_ptr<Renderer::Texture> texture,
                    const SDL_Rect* src,
                    const SDL_Rect* dst) {
    SDL_RenderCopy(pImpl->pRenderer, texture->resource(), src, dst);
}

void Renderer::copy(std::shared_ptr<Renderer::Texture> texture,
                    const SDL_Rect* src,
                    const SDL_Rect* dst,
                    const double angle,
                    const SDL_Point* center,
                    const SDL_RendererFlip flip) {
    SDL_RenderCopyEx(pImpl->pRenderer, texture->resource(), src, dst, angle, center, flip);
}

std::shared_ptr<Renderer::Texture> Renderer::texture(const std::string path) {
    auto s = Surface::create(path);
    auto t = Renderer::Texture::create(
        SDL_CreateTextureFromSurface(pImpl->pRenderer, s->resource())
    );

    return t;
}

void Renderer::draw_color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
    SDL_SetRenderDrawColor(pImpl->pRenderer, red, green, blue, alpha);
}

void Renderer::draw_line(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(pImpl->pRenderer, x1, y1, x2, y2);
}

void Renderer::draw_lines(const std::vector<SDL_Point> points) {
    SDL_RenderDrawLines(pImpl->pRenderer, points.data(), points.size());
}

void Renderer::draw_rect(const SDL_Rect* rect) {
    SDL_RenderDrawRect(pImpl->pRenderer, rect);
}

void Renderer::draw_rects(const std::vector<SDL_Rect> rects) {
    SDL_RenderDrawRects(pImpl->pRenderer, rects.data(), rects.size());
}

void Renderer::draw_fillrect(const SDL_Rect* rect) {
    SDL_RenderFillRect(pImpl->pRenderer, rect);
}

void Renderer::draw_fillrects(const std::vector<SDL_Rect> rects) {
    SDL_RenderFillRects(pImpl->pRenderer, rects.data(), rects.size());
}
