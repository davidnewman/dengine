#include "App.h"

using namespace dengine;

// Public
App::App(unsigned int flags) {
    auto code = SDL_Init(flags);

    if (code != 0)
        throw new SdlException(code);
}

App::~App() {
    SDL_Quit();
}

void App::delay(unsigned int mseconds) {
    SDL_Delay(mseconds);
}

void App::run() {
    bool terminate = false;
    SDL_Event e;

    while(!terminate) {
        while(SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    terminate = true;
                    break;
                default:
                    invoke_listeners(e.type, &e);
                    break;
            }
        }

        if(render_handler) {
            render_handler();
        }
    }
}

void App::add_listener(const ListenerKey event, Listener cb) {
    if (listeners.count(event) == 0) {
        listeners.insert(ListenerMap::value_type(event, ListenerCollection()));
    }

    listeners[event].push_back(cb);
}

void App::on_render(RenderHandler cb) {
    if(!render_handler) {
        render_handler = cb;
    }
}

// Private
void App::invoke_listeners(const ListenerKey event, const SDL_Event* event_info) {
    if (listeners.count(event) > 0) {
        for (auto listener : listeners[event]) {
            listener(event_info);
        }
    }
}
