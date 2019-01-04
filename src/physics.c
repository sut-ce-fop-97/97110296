//
// Created by amin on 12/18/18.
//

#include <SDL_events.h>
#include <time.h>
#include <zconf.h>
#include "physics.h"
#include "logic.h"
#include "init.h"


void fire(Tank *t, Bullet_Node **bullets, double ratio) {
    if (!t->bullet) {
        printf("%d bullet available.\n", t->bullet);
        return;
    }
    t->bullet--;
    add_bullet(init_bullet(t , ratio), bullets);
}

void handle_keys(Map *map) {
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


    if (map->players > 1) {
        if (keyboard[SDL_SCANCODE_D])
            keys[1][0] = 1;
        if (keyboard[SDL_SCANCODE_A])
            keys[1][1] = 1;
        if (keyboard[SDL_SCANCODE_W])
            keys[1][2] = 1;
        if (keyboard[SDL_SCANCODE_S])
            keys[1][3] = 1;
    }

    if (map->players > 2) {
        if (keyboard[SDL_SCANCODE_H])
            keys[2][0] = 1;
        if (keyboard[SDL_SCANCODE_F])
            keys[2][1] = 1;
        if (keyboard[SDL_SCANCODE_T])
            keys[2][2] = 1;
        if (keyboard[SDL_SCANCODE_G])
            keys[2][3] = 1;
    }

    if (map->players > 3) {
        if (keyboard[SDL_SCANCODE_L])
            keys[3][0] = 1;
        if (keyboard[SDL_SCANCODE_J])
            keys[3][1] = 1;
        if (keyboard[SDL_SCANCODE_I])
            keys[3][2] = 1;
        if (keyboard[SDL_SCANCODE_K])
            keys[3][3] = 1;
    }

    for (int i = 0; i < map->players; i++) {
        if(map->tanks[i]->is_alive){
            for (int j = 0; j < 2; ++j) {
                if (keys[i][j]) {
                    map->tanks[i]->angle += ((j & 1)-0.5) * 4.0 * (0.5 - keys[i][3]) * 0.025 ;
                    if (!can_turn(map , i))
                        map->tanks[i]->angle -= ((j & 1) - 0.5) * 4.0 * (0.5 - keys[i][3]) * 0.025 ;
                }

            }
            for (int j = 2; j < 4; ++j) {
                if (keys[i][j]) {
                    map->tanks[i]->x += (0.5-(j & 1)) * 2.0 * cos(-map->tanks[i]->angle);
                    map->tanks[i]->y += (0.5-(j & 1)) * 2.0 * sin(-map->tanks[i]->angle);
                    int tmp = (!(j & 1) ? 0 : 3);
                    if (!can_go(map , i , tmp)) {
                        map->tanks[i]->x -= (0.5-(j & 1)) * 2.0 * cos(-map->tanks[i]->angle);
                        map->tanks[i]->y -= (0.5-(j & 1)) * 2.0 * sin(-map->tanks[i]->angle);
                    }
                }
            }
        }
    }
}

int handle_event(Map *map) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;
        }
        if(event.type == SDL_KEYUP ){
            if(event.key.keysym.sym == SDLK_SLASH && map->tanks[0]->is_alive)
                fire(map->tanks[0], &map->bullets, map->ratio);
            if(map->players>1 && event.key.keysym.scancode == SDL_SCANCODE_Q && map->tanks[1]->is_alive)
                fire(map->tanks[1], &map->bullets, map->ratio);
            if(map->players>2 && event.key.keysym.scancode == SDL_SCANCODE_R && map->tanks[2]->is_alive)
                fire(map->tanks[2], &map->bullets, map->ratio);
            if(map->players>3 && event.key.keysym.scancode == SDL_SCANCODE_U && map->tanks[3]->is_alive)
                fire(map->tanks[3], &map->bullets, map->ratio);



        }
    }
    return 1;
}

void add_bullet(Bullet *b, Bullet_Node **bullets) {
    Bullet_Node *new_bull = malloc(sizeof(Bullet_Node));
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

void update_corners(Tank *t){
    double a = t->angle, y = t->y , x = t->x;
    t->corners[0].x = x + (t->lenght / 2) * cos(a) - (t->width / 2) * sin(a);
    t->corners[0].y = y - (t->lenght / 2) * sin(a) - (t->width / 2) * cos(a);
    t->corners[1].x = x + t->barrel_lenght * cos(a);
    t->corners[1].y = y - t->barrel_lenght * sin(a);
    t->corners[2].x =  x + (t->lenght / 2) * cos(a) + (t->width / 2) * sin(a);
    t->corners[2].y = y - (t->lenght / 2) * sin(a) + (t->width / 2) * cos(a);
    t->corners[3].x = x - t->lenght / 2 * cos(a) + t->width / 2 * sin(a);
    t->corners[3].y = y + t->lenght / 2 * sin(a) + t->width / 2 * cos(a);
    t->corners[4].x = x - t->lenght / 2 * cos(a) - t->width / 2 * sin(a);
    t->corners[4].y = y + t->lenght / 2 * sin(a) - t->width / 2 * cos(a);
}

