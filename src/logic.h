//
// Created by amin on 12/25/18.
//

#ifndef PROJECT_LOGIC_H
#define PROJECT_LOGIC_H

#include <stdbool.h>
#include "structs.h"

double max(double a, double b);
double min(double a, double b);
bool can_go(Tank *t, Wall **walls, int count_of_walls, int dir, int player);
bool can_turn(Tank *t, Wall **walls, int count_of_walls);

#endif //PROJECT_LOGIC_H
