//
// Created by amin on 12/18/18.
//

#include <SDL_events.h>
#include <time.h>
#include "physics.h"


void move_tank() {

}

void tank_colision() {


}


void move_bullet() {

}

Bullet* init_bullet(Tank *t) {
    Bullet* b = malloc(sizeof(Bullet));
    b->x = t->x + 40*cos(t->angle);
    b->y = t->y - 40*sin(t->angle);
    b->angle = -t->angle;
    b->radius = 3;
    b->life_time = 1000;
    return b;
}

void fire(Tank *t, Bullet_Node **bullets) {
    if (!t->bullet) {
        printf("%d bullet available.\n", t->bullet);
        return;
    }
    t->bullet--;
    add_bullet(init_bullet(t), bullets);
}

void handle_keys(Tank *t) {
//    SDL_Event event;
//    while(SDL_PollEvent(&event)){
//
//        if(event.type == SDL_KEYDOWN )
//            if(event.key.keysym.sym == SDLK_m)
//                fire(t, bullets);
//    }

    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    if(keyboard[SDL_SCANCODE_RIGHT]){
        t->angle -= 2.0*(0.5-keyboard[SDL_SCANCODE_DOWN])*0.0034;
    }
    if(keyboard[SDL_SCANCODE_LEFT]){
        t->angle += 2.0*(0.5-keyboard[SDL_SCANCODE_DOWN])*0.0034;
    };
    if(keyboard[SDL_SCANCODE_UP]){
        t->x += 0.3 * cos(-t->angle);
        t->y += 0.3 * sin(-t->angle);
    }
    if(keyboard[SDL_SCANCODE_DOWN]){
        t->x -= 0.3 * cos(-t->angle);
        t->y -= 0.3 * sin(-t->angle);
    }
//
//    if(keyboard[SDL_SCANCODE_M]){
//        fire(t, bullets);
//    }

}


int handle_event(Tank* t, Bullet_Node** bullets) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
        if(event.type == SDL_KEYUP )
            if(event.key.keysym.sym == SDLK_m)
                fire(t, bullets);
    }
    return 1;
}

void add_bullet(Bullet* b, Bullet_Node** bullets) {
    Bullet_Node* new_bull = malloc(sizeof(Bullet_Node));
    new_bull->b = *b;
    if(*bullets != NULL) {
        new_bull->next = *bullets;
    }
    else {
        new_bull->next = NULL;
        *bullets = malloc(sizeof(Bullet_Node));
    }
    *bullets = new_bull;
}


Tank *init_tank(double ratio, int maxx, int maxy, int k) {
    Tank *t = malloc(sizeof(Tank));
    srand(time(NULL));
    t->x = ratio*(0.65+rand()%(maxx-1));
    t->y = ratio*(0.65+rand()%(maxy-1));
    t->bullet = 500;
    t->angle = rand();
    t->lenght = 0.4*ratio;
    t->width = 0.35*ratio;
    t->barrel_lenght = 0.3*ratio;
    t->barrel_thickness = 0.08*ratio;

    switch(k){
        case 0:
            t->light_color =  255 | (95 << 8) | (66 << 16) | (230 << 24);
            t->dark_color = 255 | (255 << 24);
            break;
        case 1:
            t->light_color =  66 | (134 << 8) | (244<< 16) | (230 << 24);
            t->dark_color = 0 | (80 << 8) | (255<< 16) | (230 << 24);
            break;
        case 2:
            t->light_color =  243 | (112 << 8) | (255 << 16) | (230 << 24);
            t->dark_color = 187 | (0 << 8) | (255 << 16) | (230 << 24);
            break;
        case 3:
            t->light_color =  155 | (255 << 8) | (106 << 16) | (230 << 24);
            t->dark_color = 0 | (255 << 8) | (38<< 16) | (230 << 24);
            break;
    }

    return t;
}