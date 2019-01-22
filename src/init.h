//
// Created by amin on 12/24/18.
//

#ifndef PROJECT_INIT_H
#define PROJECT_INIT_H

#include "structs.h"

static bool button(SDL_Renderer *r, button_t *btn);
int start_UI(SDL_Window *pWindow, SDL_Renderer *renderer);
Bullet* init_bullet(Tank *t, double ratio);
Tank *init_tank(Map *map, int k, bool *** ocupied);
bool start_game(Map *map);
void generate_walls(Cell ***cells, int a, int b);
int load_last_game(Map *map);

#endif //PROJECT_INIT_H
