//
// Created by amin on 12/18/18.
//

#include <SDL_events.h>
#include "physics.h"
#include "structs.h"


void move_tank() {

}

void tank_colision() {


}


void move_bullet() {

}

void fire(Tank *t) {
    if (!t->bullet) {
        printf("No bullet available.\n");
        return;
    }
    t->bullet--;
    Bullet b = init_bullet(t);
    move_bullet(b);
}

int handle_events(Tank *t) {
    SDL_Event event;
    int flag = 1;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            flag = 0;
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                t->x += 5 * cos(-t->angle);
                t->y += 5 * sin(-t->angle);
                break;
            case SDLK_DOWN:
                t->x -= 5 * cos(-t->angle);
                t->y -= 5 * sin(-t->angle);
                break;
            case SDLK_RIGHT:
                t->angle -= 0.05;
                break;
            case SDLK_LEFT:
                t->angle += 0.05;
                break;
            case SDLK_m:
                fire(t);
            default:
                break;
        }

    }

}
