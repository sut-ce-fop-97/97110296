//
// Created by amin on 12/18/18.
//

#include "structs.h"

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

void show_tank(Tank *t, SDL_Renderer *pRenderer);
void show_walls(struct SDL_Renderer * renderer, Wall **walls, int n);
double generate_walls(Wall ***walls, int *n, int *maxx, int *maxy);
void show_bullet(Bullet_Node **bullets, SDL_Renderer *renderer, double players);
void show_scores(Tank **tanks, int n, SDL_Renderer *renderer, double d);

#endif //PROJECT_VIEW_H
