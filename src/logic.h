//
// Created by amin on 12/25/18.
//

#ifndef PROJECT_LOGIC_H
#define PROJECT_LOGIC_H

#include <stdbool.h>
#include "structs.h"

double max(double a, double b);
double min(double a, double b);
bool can_go(Map *map, int player_number, int dir);
bool can_turn(Map *map, int player_number);
int meet_wall(Map *map, Bullet b);
bool meet_tank(Map *map, Bullet b);

#endif //PROJECT_LOGIC_H
