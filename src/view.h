//
// Created by amin on 12/18/18.
//

#include "structs.h"

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

void show_tank(Tank *t, SDL_Renderer *pRenderer);
void show_walls(struct SDL_Renderer * renderer, long long** walls, int n);
void event_handler();
void  quit_window();
double generate_walls(long long int ***walls, int *n, int *maxx, int *maxy);
void show_bullet(Bullet_Node **bullets, SDL_Renderer *renderer);
void show_scores(Tank **tanks, int n, double ratio, int maxx, int minn, SDL_Renderer *renderer);

#endif //PROJECT_VIEW_H
