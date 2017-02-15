#ifndef _DENGINE_SPRITE_INCL
#define _DENGINE_SPRITE_INCL

#include "Core.h"

namespace dengine {
    class Sprite {
        public:
            /**
             * \brief Sprite animation.
             *
             * \param t std::shared_ptr<Renderer::Texture> frame sheet.
             * \param w int width of each frame in pixels.
             * \param h int height of each frame in pixels.
             * \param d double duration of each frame.
             */
            Sprite(std::shared_ptr<Renderer::Texture> t, int frames, int w, int h, double d) :
                _sheet(t),  _frames(frames), _frameDuration(d) {
                _frame.w = w;
                _frame.h = h;
                _frame.x = 0;
                _frame.y = 0;
                _frameElapsed = 0.0;
                _max_x = w * (frames - 1);
            }

            /**
             * \brief Add to the amount of time the current frame has been rendered,
             *        and advance the frame as necessary.
             *
             * \param time double Amount of time in seconds to add.
             */
            void advance(double time);

            /**
             * \brief The current frame for the Sprite.
             *
             * \return Frame inside the Sprite.
             */
            const SDL_Rect* frame() const;

            /**
             * \brief The sheet of frames representing the Sprite.
             *
             * \return Entire Sprite.
             */
            std::shared_ptr<Renderer::Texture> sheet() const;

        private:
            /**
             * \brief The entire sheet worth of frames for this sprite.
             */
            std::shared_ptr<Renderer::Texture> _sheet;

            /**
             * \brief Number of frames in the sheet.
             */
            int _frames;

            /**
             * \brief Portion of the sheet representing the current frame.
             */
            SDL_Rect _frame;

            /**
             * \brief Time each frame should be rendered for before moving to
             * the next frame in the sheet.
             */
            double _frameDuration;

            /**
             * \brief Amount of time that has elapsed for the current frame.
             */
            double _frameElapsed;

            /**
             * \brief Maximum x co-ordinate, i.e. start of last frame.
             */
            int _max_x;
    };
}

#endif
