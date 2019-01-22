//
// Created by amin on 1/22/19.
//

#include <SDL_render.h>
#include <stdbool.h>
#include "structs.h"

#ifndef PROJECT_UI_H
#define PROJECT_UI_H



static void button_process_event(button_t *buttons, int k, const SDL_Event *ev, int *focus) ;
static bool button(SDL_Renderer *r, button_t *btn) ;
int start_UI(SDL_Window *pWindow, SDL_Renderer *renderer) ;
int pause_UI(Map *map);


#endif //PROJECT_UI_H

