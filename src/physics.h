//
// Created by amin on 12/18/18.
//



#ifndef PROJECT_PHYSICS_H
#define PROJECT_PHYSICS_H


#include "structs.h"

void move_tank();
void tank_colision();
int handle_event(Tank* t , Bullet_Node** bullets);
void handle_keys(Tank *t);
void add_bullet(Bullet* b, Bullet_Node** bullets);

Tank *init_tank(double ratio, int maxx, int maxy, int i);

#endif //PROJECT_PHYSICS_H


