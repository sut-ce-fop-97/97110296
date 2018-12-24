//
// Created by amin on 12/24/18.
//

#ifndef PROJECT_INIT_H
#define PROJECT_INIT_H

#include "structs.h"

static void button_process_event(button_t *btn, const SDL_Event *ev);

static bool button(SDL_Renderer *r, button_t *btn);

int determine_player_number();



#endif //PROJECT_INIT_H
