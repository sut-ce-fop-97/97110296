//
// Created by amin on 12/18/18.
//

#include "structs.h"

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

void show_tank(Tank *t, SDL_Renderer *pRenderer);
void show_walls(Map *map, struct SDL_Renderer * renderer);
void updlode_walls(Map *map);
void show_bullet(Map *map, SDL_Renderer *renderer);
void show_scores(Map *map, SDL_Renderer *renderer);
void write_to_file(Cell **cells, int n, int m);
int to_int(char buff[5]);

#endif //PROJECT_VIEW_H
