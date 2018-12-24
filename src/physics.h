//
// Created by amin on 12/18/18.
//



#ifndef PROJECT_PHYSICS_H
#define PROJECT_PHYSICS_H


#include "structs.h"

void tank_colision();
int handle_event(Tank** tanks , Bullet_Node** bullets, int n);
void handle_keys(Tank **tanks, int players/*, Wall **walls, int number_of_walls*/);
void add_bullet(Bullet* b, Bullet_Node** bullets);

Tank *init_tank(double ratio, int maxx, int maxy, int i);

#endif //PROJECT_PHYSICS_H


