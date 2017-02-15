#include <iostream>
#include <memory>
#include <cstring>
#include <random>
#include "dengine.h"

using namespace std;
using namespace dengine;

void print_vector(const Vector2d *v) {
    auto deg = degrees(v->theta());
    cout << "{ x: " << v->x() << ", y: " << v->y() << ", m: "
         << v->magnitude() << ", t_rad: " << v->theta()
         << ", t_deg: " << deg << " }" << endl;
}

void draw_vector(Renderer* rend, int x, int y, Vector2d r, unsigned int red, unsigned int green, unsigned int blue, double scale) {
    auto rp = r * scale;
    auto rx = rp.x();
    auto ry = rp.y();

    rend->draw_color(red, green, blue, 255);
    rend->draw_line(x, y, x+rx, y+ry);
}

struct GameObject {
    Motion motion;
    std::shared_ptr<Sprite> sprite; 
    bool alive;
};

struct Scene {
    std::shared_ptr<Renderer::Texture> shipTexture;
    std::shared_ptr<Renderer::Texture> asteroidTexture;
    std::shared_ptr<Renderer::Texture> asteroid2Texture;
    std::shared_ptr<Renderer::Texture> bulletTexture;
    double heading;
    std::vector<GameObject> projectiles;
    std::vector<GameObject> asteroids;
    GameObject ship;
    double last_render;
};

std::vector<GameObject> create_asteroids(int count, int max_x, int max_y, std::shared_ptr<Renderer::Texture> t) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> xs(1, max_x);
    std::uniform_int_distribution<> ys(1, max_y);
    std::uniform_real_distribution<> mag(25, 200);
    std::uniform_real_distribution<> theta(0, (2.0 * M_PI));
    std::vector<GameObject> roids;

    for (int i = 0; i < count; ++i) {
        GameObject obj;
        obj.motion = Motion(
            Vector2d(xs(mt), ys(mt)),
            Vector2d::magnitude_direction(mag(mt), theta(mt))
        );
        obj.sprite = std::make_shared<Sprite>(t, 1, 32, 32, 1.0);
        obj.alive = true;
        roids.push_back(obj);
    }

    return roids;
}

void run() {
    dengine::App app{SDL_INIT_VIDEO};

    const int max_y = 480;
    const int max_x = 640;
    const double start_heading = 0.0;
    
    auto w = dengine::Window::create(
        "SDL Tutorial",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        max_x, max_y,
        SDL_WINDOW_SHOWN
    );
    Renderer rend(w->id(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Scene scene;
    scene.shipTexture = rend.texture("/home/den/github/dengine/examples/asteroids/assets/ship.png");
    scene.asteroidTexture = rend.texture("/home/den/github/dengine/examples/asteroids/assets/asteroid-large-1.png");
    scene.asteroid2Texture = rend.texture("/home/den/github/dengine/examples/asteroids/assets/asteroid-large-2.png");
    scene.bulletTexture = rend.texture("/home/den/github/dengine/examples/asteroids/assets/bullet.png");
    scene.ship.sprite = std::make_shared<Sprite>(scene.shipTexture, 1, 32, 32, 1.0);
    scene.ship.motion = Motion(Vector2d(max_x / 2, max_y / 2));
    scene.heading = start_heading;
    scene.asteroids = create_asteroids(10, max_x, max_y, scene.asteroid2Texture);
    scene.last_render = SDL_GetTicks();


    auto on_keydown = [&scene, max_x, max_y, start_heading](const SDL_Event *e) {
        auto key = e->key.keysym.sym;
        Vector2d a{0.0, 0.0};
        double forward_accel{100.0};
        double turn = 0.25;

        switch (key) {
            case SDLK_w:
                // accelerate
                a = Vector2d::magnitude_direction(forward_accel, scene.heading);
                scene.ship.motion.accelerate(a);
                break;
            case SDLK_s:
                // stop
                scene.ship.motion.stop();
                break;
            case SDLK_a:
                // turn left
                scene.heading -= turn;
                if (scene.heading < 0.0) {
                    scene.heading = (2.0 * M_PI);
                }
                a = Vector2d::magnitude_direction(
                    scene.ship.motion.acceleration().magnitude(),
                    scene.heading
                );
                scene.ship.motion.accelerate(a);
                break;
            case SDLK_d:
                // turn right
                scene.heading += turn;
                if (scene.heading > (2.0 * M_PI)) {
                    scene.heading = 0.0;
                }
                a = Vector2d::magnitude_direction(
                    scene.ship.motion.acceleration().magnitude(),
                    scene.heading
                );
                scene.ship.motion.accelerate(a);
                break;
            case SDLK_RETURN:
                // reset
                scene.ship.motion = Vector2d(max_x / 2, max_y / 2);
                scene.heading = start_heading;
                scene.asteroids = create_asteroids(10, max_x, max_y, scene.asteroid2Texture);
                break;
            case SDLK_SPACE:
                auto v = scene.ship.motion.velocity();
                auto d = scene.ship.motion.displacement();
                d = Vector2d{d.x() + 16, d.y() + 16};
                v = Vector2d::magnitude_direction(200 + abs(v.magnitude()), scene.heading);
                Motion p{d, v};
                GameObject obj;
                obj.motion = p;
                obj.sprite = std::make_shared<Sprite>(scene.bulletTexture, 1, 8, 8, 1.0);
                obj.alive = true;
                scene.projectiles.push_back(obj);
                break;
        }
    };

    auto on_keyup = [&scene](const SDL_Event* e) {
        auto key = e->key.keysym.sym;
        auto a = scene.ship.motion.acceleration();

        switch (key) {
            case SDLK_w:
                scene.ship.motion.accelerate(
                    Vector2d::magnitude_direction(
                        0.0,
                        a.theta()
                    )
                );
                break;
        }
    };

    auto render = [&scene, &w, &rend,  max_x, max_y]() {
       
        auto current = SDL_GetTicks();
        auto last = scene.last_render;
        auto delta = (current - last) / 1000.0;
        scene.last_render = current;

        auto p = scene.ship.motion.displacement();

        SDL_Rect r;
        r.w = 32;
        r.h = 32;
        r.x = p.x();
        r.y = p.y();

        SDL_Rect wr;
        wr.w = 640;
        wr.h = 480;
        wr.x = 0;
        wr.y = 0;

        rend.clear();
        rend.draw_color(0x00, 0x00, 0x00, 255);
        rend.draw_fillrect(&wr);

        
        rend.copy(scene.ship.sprite->sheet(), scene.ship.sprite->frame(), &r, degrees(scene.heading), NULL, SDL_FLIP_VERTICAL);
        scene.ship.motion.move(delta);

        // draw the bullets!
        if (scene.projectiles.size() > 0) {
            SDL_Rect pr;
            pr.w = 8;
            pr.h = 8;

            for (auto& projectile : scene.projectiles) {
                projectile.motion.move(delta);
                auto pv = projectile.motion.displacement();
                auto px = pv.x();
                auto py = pv.y();
                if (px < max_x &&
                    px > 0 &&
                    py < max_y &&
                    py > 0) {

                    pr.x = px - 1;
                    pr.y = py - 1;

                    // detect collision
                    for (auto& roid : scene.asteroids) {
                        auto rd = roid.motion.displacement();
                        SDL_Rect r;
                        r.w = 32;
                        r.h = 32;
                        r.x = rd.x();
                        r.y = rd.y();

                        if (roid.alive && (SDL_HasIntersection(&r, &pr) == SDL_TRUE)) {
                            projectile.alive = false;
                            roid.alive = false;
                            break;
                        }
                    }

                    if (projectile.alive) {
                        rend.draw_fillrect(&pr);
                        rend.copy(projectile.sprite->sheet(), projectile.sprite->frame(), &pr);
                    }
                } else {
                    projectile.alive = false;
                }
            }

            vector<GameObject> alive;
            for (auto& p : scene.projectiles) {
                if (p.alive) {
                    alive.push_back(p);
                }
            }
            scene.projectiles = alive;

            alive.clear();
            for (auto& r : scene.asteroids) {
                if (r.alive) {
                    alive.push_back(r);
                }
            }
            scene.asteroids = alive;
        }

        // draw the asteroids!
        if (scene.asteroids.size() > 0) {
            SDL_Rect rr;
            rr.w = 32;
            rr.h = 32;

            for (auto& roid : scene.asteroids) {
                auto rv = roid.motion.displacement();
                auto rx = rv.x();
                auto ry = rv.y();
                if (roid.alive &&
                    rx < max_x &&
                    rx >= 0 &&
                    ry < max_y &&
                    ry >= 0) {

                    rr.x = rx;
                    rr.y = ry;
                    rend.copy(roid.sprite->sheet(), roid.sprite->frame(), &rr);
                    roid.motion.move(delta);

                } else {
                    // roid moved off screen, let's put it back on screen
                    if (rx >= max_x) {
                        rx = 0;
                    } else if (rx < 0) {
                        rx = max_x - 1;
                    }

                    if (ry >= max_y) {
                        ry = 0;
                    } else if (ry < 0) {
                        ry = max_y -1;
                    }
                    
                    roid.motion = Motion(
                        Vector2d(rx, ry),
                        roid.motion.velocity()
                    );
                }
            }
        }

        rend.render();
        w->update();
    };

    app.add_listener(SDL_KEYDOWN, on_keydown);
    app.add_listener(SDL_KEYUP, on_keyup);
    app.on_render(render);
    app.run();
}

int main() {

    run(); 

    return 0;
}
