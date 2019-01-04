//
// Created by amin on 12/24/18.
//

#ifndef PROJECT_INIT_H
#define PROJECT_INIT_H

#include "structs.h"

static void button_process_event(button_t *btn, const SDL_Event *ev);
static bool button(SDL_Renderer *r, button_t *btn);
int determine_player_number();
Bullet* init_bullet(Tank *t, double ratio);
Tank *init_tank(Map *map, int k, bool *** ocupied);
void start_game(Map *map, SDL_Window *window, SDL_Renderer **renderer);
void generate_walls(Cell ***cells, int a, int b);
void make_tank(Tank *t, double ratio) ;


#endif //PROJECT_INIT_H
