#include "Sprite.h"

using namespace dengine;

void Sprite::advance(double time) {
    if (_frames == 1)
        return;

    _frameElapsed += time;

    if (_frameElapsed >= _frameDuration) {
        // advance to the next frame
        _frame.x += _frame.w;

        if (_frame.x > _max_x) {
            _frame.x = 0;
        }

        _frameElapsed = 0.0;
    }
}

const SDL_Rect* Sprite::frame() const {
    return &_frame;
}

std::shared_ptr<Renderer::Texture> Sprite::sheet() const {
    return _sheet;
}
