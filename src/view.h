//
// Created by amin on 12/18/18.
//

#include "structs.h"

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

SDL_Renderer * init_window();
void show_tank(Tank *t, SDL_Renderer *pRenderer);
void show_walls(struct SDL_Renderer * renderer);
void event_handler();
void  quit_window();
void show_bullet(Bullet_Node **bullets, SDL_Renderer *renderer);
#endif //PROJECT_VIEW_H
