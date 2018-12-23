//
// Created by amin on 12/18/18.
//

#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

typedef struct {
    int bullet;
    double x, y, angle;
    const double radius ,barrel_lenght, barrel_thickness , width, lenght;
}Tank;

typedef struct {
    double x, y, angle;
    int radius, life_time;
}Bullet;

typedef struct Bullet_Node{
    Bullet b;
    struct Bullet_Node* next;
}Bullet_Node;

typedef struct {
    int light , dark;
}Color;



#endif //PROJECT_STRUCTS_H
