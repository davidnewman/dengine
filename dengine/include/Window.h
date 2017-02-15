#ifndef _DENGINE_WINDOW_INCL
#define _DENGINE_WINDOW_INCL

#include <string>
#include <memory>

#include "Common.h"
#include "Surface.h"

namespace dengine {
    /**
     * \brief Window in the underlying windowing system.
     *
     * This class wraps the SDL_Window stuct and provides man of the basic
     * operations that you'd want to perform on an SDL_Window.
     */
    class Window {
        public:

            /**
             * \brief Destroy the underlying resources.
             */
            ~Window();

            /**
             * \brief Perfect-forwarding factory method.
             *
             * This method perfect-forwards all arguments to a private constructor.
             * This is done to ensure that clients are utilizing resource management
             * classes such as std::unique_ptr.
             */
            template<typename... Ts>
            static std::shared_ptr<Window> create(Ts&&... params) {
                return std::shared_ptr<Window>(
                    new Window(std::forward<Ts>(params)...)
                );
            }

            /**
             * \brief Provides access to the Window's Surface to allow for drawing.
             *
             * The Surface that is returned by this method should not be destroyed directly,
             * but rather cleaned up by the Window object.
             */
            std::shared_ptr<Surface> window_surface() const;

            /**
             * \brief Update/redraw the contents of the Window.
             */
            void update();

            /**
             * \brief Get the unique ID of the underlying Window.
             */
            unsigned int id();

        private:
            /**
             * \brief The internal representation of the Window.
             */
            struct Impl;

            /**
             * \brief Pointer to the internal representation of Window.
             */
            std::unique_ptr<Impl> pImpl;

            /**
             * \brief Creates a new Window with the given title, width, height, etc.
             *
             * \param title title of the Window.
             * \param x x coordinate of the upper left corner of the window.
             * \param y y coordinate of the upper left corner of the window.
             * \param w width of the window in pixels.
             * \param h height of the window in pixels.
             * \param flags options pertaining to the window.
             */
            Window(std::string title,
                   int x, int y,
                   int w, int h,
                   SDL_WindowFlags flags);
    };
}

#endif
