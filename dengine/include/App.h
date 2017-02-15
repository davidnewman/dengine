#ifndef _DENGINE_APP_INCL
#define _DENGINE_APP_INCL

#include "Common.h"
#include "App.h"
#include "Surface.h"

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace dengine {
    class App {
        using Listener = std::function<void (const SDL_Event*)>;
        using ListenerKey = unsigned int;
        using ListenerCollection = std::vector<Listener>;
        using ListenerMap = std::map<ListenerKey, ListenerCollection>;
        using RenderHandler = std::function<void ()>;

        public:
            App(unsigned int flags);
            ~App();

            void delay(unsigned int mseconds);
            void run();
            void add_listener(const ListenerKey event, Listener cb);
            void on_render(RenderHandler cb);

        private:
            ListenerMap listeners;
            RenderHandler render_handler;

            void invoke_listeners(const ListenerKey event, const SDL_Event* event_info);
    };
}

#endif
