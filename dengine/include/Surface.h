#ifndef _DENGINE_SURFACE_INCL
#define _DENGINE_SURFACE_INCL

#include <memory>

#include "Common.h"

namespace dengine {
    /**
     * \brief Wraps the SDL_Surface struct.
     *
     * Wraps the SDL_Surface struct to ensure it is cleaned up properly.
     */
    class Surface {

        public:

            /**
             * \brief Frees the underlying Surface resources.
             */
            ~Surface();

            /**
             * \brief Perfect forwarding factory function.
             */
            template<typename... Ts>
            static std::unique_ptr<Surface> create(Ts&&... params) {
                return std::unique_ptr<Surface>(
                    new Surface(std::forward<Ts>(params)...)
                );
            }


            /**
             * \brief Filles the Surface with the given color in the defined region.
             */
            void fill_rect(const SDL_Rect* rect, unsigned int r, unsigned int g, unsigned b, unsigned int a = 0);

            /**
             * \brief Blit the contents of this Surface onto the destination Surface.
             */
            void blit(const SDL_Rect* srcRect, std::shared_ptr<Surface> dst, SDL_Rect* dstRect);

            SDL_Surface* resource();

        private:
            /**
             * \brief Internal representation of the Surface.
             */
            struct Impl;

            /**
             * \brief Pointer to the internal represenation of the Surface.
             */
            std::unique_ptr<Impl> pImpl;

            /**
             * \brief Constructs a Surface to wrap the given SDL_Surface.
             */
            Surface(SDL_Surface* sp);

            /**
             * \brief Path to an image resource to be loaded into a new Surface.
             *
             * \param file path to an image resource to be loaded into a new Surface.
             */
            Surface(std::string file);
    };
}

#endif
