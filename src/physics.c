//
// Created by amin on 12/18/18.
//

#include <SDL_events.h>
#include <time.h>
#include "physics.h"
#include "logic.h"


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
    b->life_time = 10000;
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






void handle_keys(Tank **tanks, int players, Wall **walls, int number_of_walls) {
    bool keys[4][5] = {};
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    if (keyboard[SDL_SCANCODE_RIGHT])
        keys[0][0] = 1;
    if (keyboard[SDL_SCANCODE_LEFT])
        keys[0][1] = 1;
    if (keyboard[SDL_SCANCODE_UP])
        keys[0][2] = 1;
    if (keyboard[SDL_SCANCODE_DOWN])
        keys[0][3] = 1;


    if (players > 1) {
        if (keyboard[SDL_SCANCODE_D])
            keys[1][0] = 1;
        if (keyboard[SDL_SCANCODE_A])
            keys[1][1] = 1;
        if (keyboard[SDL_SCANCODE_W])
            keys[1][2] = 1;
        if (keyboard[SDL_SCANCODE_S])
            keys[1][3] = 1;
    }

    if (players > 2) {
        if (players > 1) {
            if (keyboard[SDL_SCANCODE_H])
                keys[2][0] = 1;
            if (keyboard[SDL_SCANCODE_F])
                keys[2][1] = 1;
            if (keyboard[SDL_SCANCODE_T])
                keys[2][2] = 1;
            if (keyboard[SDL_SCANCODE_G])
                keys[2][3] = 1;
        }
    }

    if (players > 3) {
        if (players > 1) {
            if (keyboard[SDL_SCANCODE_L])
                keys[3][0] = 1;
            if (keyboard[SDL_SCANCODE_J])
                keys[3][1] = 1;
            if (keyboard[SDL_SCANCODE_I])
                keys[3][2] = 1;
            if (keyboard[SDL_SCANCODE_K])
                keys[3][3] = 1;
        }
    }

    for (int i = 0; i < players; i++) {
        for (int j = 0; j < 2; ++j) {
            if (keys[i][j]) {
                tanks[i]->angle += ((j & 1)-0.5) * 4.0 * (0.5 - keys[i][3]) * 0.0034 * sqrt(players);
                if (!can_turn(tanks[i], walls, number_of_walls))
                    tanks[i]->angle -= ((j & 1) - 0.5) * 4.0 * (0.5 - keys[i][3]) * 0.0034 * sqrt(players);
            }

        }
        for (int j = 2; j < 4; ++j) {
            if (keys[i][j]) {
                tanks[i]->x += (0.5-(j & 1)) * 2.0 * sqrt(players) * 0.3 * cos(-tanks[i]->angle);
                tanks[i]->y += (0.5-(j & 1)) * 2.0 * sqrt(players) * 0.3 * sin(-tanks[i]->angle);
                if (!can_go(tanks[i], walls, number_of_walls, !(j & 1), players)) {
                    tanks[i]->x -= (0.5-(j & 1)) * 2.0 *  sqrt(players) * 0.3 * cos(-tanks[i]->angle);
                    tanks[i]->y -= (0.5-(j & 1)) * 2.0 *  sqrt(players) * 0.3 * sin(-tanks[i]->angle);
                }
            }
        }
    }
}



int handle_event(Tank** tanks, Bullet_Node** bullets, int n) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
        if(event.type == SDL_KEYUP ){
            if(event.key.keysym.sym == SDLK_SLASH)
                fire(tanks[0], bullets);
            if(n>1 && event.key.keysym.sym == SDLK_q)
                fire(tanks[1], bullets);
            if(n>2 && event.key.keysym.sym == SDLK_r)
                fire(tanks[2], bullets);
            if(n>3 && event.key.keysym.sym == SDLK_u)
                fire(tanks[3], bullets);

        }
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
    t->bullet = 5;
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