#ifndef _DENGINE_RENDERER_INCL
#define _DENGINE_RENDERER_INCL

#include "Core.h"
#include <memory>

namespace dengine {
    /**
     * \brief Basic, double-buffered drawing functionality.
     */
    class Renderer {
        public:

            /**
             * \brief Texture
             */
            class Texture {
                /**
                 * \brief Points to the underlying texture resource.
                 */
                SDL_Texture* pTexture;

                /**
                 * \brief Wrap the given texture.
                 */
                Texture(SDL_Texture* t);

                public:

                /**
                 * \brief Perfect forwarding factory function.
                 */
                template<typename... Ts>
                static std::shared_ptr<Texture> create(Ts&&... params) {
                    return std::shared_ptr<Texture>(
                        new Texture(std::forward<Ts>(params)...)
                    );
                }


                /**
                 * \brief Return underlying SDL handle.
                 */
                SDL_Texture* resource();

                /**
                 * \brief Destroy the underlying texture resource.
                 */
                ~Texture();
            };
            

            /**
             * \brief Create a Renderer for the given Window.
             *
             * \param window_id unsigned int representing the unique identifier of the Window.
             * \param index int index of the render driver, -1 for the first matching flags.
             * \param flags unsigned int specification of the renderer.
             */
            Renderer(unsigned int window_id,
                     int index,
                     unsigned int flags);

            /**
             * \brief Destroy the Renderer and associated assets.
             */
            ~Renderer();

            /**
             * \brief Swaps the back-buffer with the currently displayed buffer.
             */
            void render();

            /**
             * \brief Clears any previous operations on the Renderer's back-buffer.
             */
            void clear();

            /**
             * \brief Copy the given texture, or part of texture, to the Renderer.
             *
             * \param texture SDL_Texture* texture to copy to the Renderer.
             * \param src SDL_Rect* part of the texture to copy, NULL for entire texture.
             * \param dst SDL_Rect* part of the Renderer to copy the texture to.
             */
            void copy(std::shared_ptr<Renderer::Texture> texture,
                      const SDL_Rect* src,
                      const SDL_Rect* dst);

            /**
             * \brief Copy the given texture, potentially applying some effects.
             *
             * \param texture SDL_Texture* texture to copy to the Renderer.
             * \param src SDL_Rect* part of the texture to copy, NULL for entire texture.
             * \param dst SDL_Rect* part of the Renderer to copy the texture to.
             * \param angle double angle in radians to rotate the texture.
             * \param flip SDL_RendererFlip dimension to flip the texture.
             */
            void copy(std::shared_ptr<Renderer::Texture> texture,
                      const SDL_Rect* src,
                      const SDL_Rect* dst,
                      const double angle,
                      const SDL_Point* center,
                      const SDL_RendererFlip flip);

            /**
             * \brief Set color for future draw operations in RGBa.
             *
             * \param red unsigned int Red value.
             * \param green unsigned int Green value.
             * \param blue unsigned int Blue value.
             * \param alpha unsigned int alpha value.
             */
            void draw_color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

            /**
             * \brief Draw line from (x1,y1) to (x2,y2).
             *
             * \param x1 int origin x coordinate.
             * \param y1 int origin y coordinate.
             * \param x2 int terminal x coordinate.
             * \param y2 int terminal y coordinate.
             */
            void draw_line(int x1, int y1, int x2, int y2);

            /**
             * \brief Draw several lines by connecting the given points.
             *
             * \param points std::vector<SDL_Point> set of points to connect.
             */
            void draw_lines(const std::vector<SDL_Point> points);

            /**
             * \brief Draw a single point at (x,y)
             *
             * \param x int x coordinate of point to draw.
             * \param y int y coordinate of point to draw.
             */
            void draw_point(int x, int y);

            /**
             * \brief Draw a set of points (not connecting by lines).
             *
             * \param points std::vector<SDL_Point> set of points to draw.
             */
            void draw_points(const std::vector<SDL_Point> points);

            /**
             * \brief Draw a non-filled rectangle.
             *
             * \param rect SDL_Rect* rectangle to draw.
             */
            void draw_rect(const SDL_Rect* rect);

            /**
             * \brief Draw a set of non-filled rectangles.
             *
             * \param rects std::vector<SDL_Rect> set of rectangles to draw.
             */
            void draw_rects(const std::vector<SDL_Rect> rects);

            /**
             * \brief Draw a filled rectangle.
             *
             * \param rect SDL_Rect* rectangle to draw.
             */
            void draw_fillrect(const SDL_Rect* rect);

            /**
             * \brief Draw a set of filled rectangles.
             *
             * \param rects std::vector<SDL_Rect> set of rectangles to draw.
             */
            void draw_fillrects(const std::vector<SDL_Rect> rects);

            /**
             * \brief Load a Texture based on a file.
             *
             * \param path std::string path to a file.
             */
            std::shared_ptr<Texture> texture(const std::string path);

        private:
            struct Impl; 

            /**
             * \brief Pointer to implementation details.
             */
            std::unique_ptr<Impl> pImpl;
    };
}

#endif
