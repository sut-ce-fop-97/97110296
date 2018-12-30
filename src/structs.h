//
// Created by amin on 12/18/18.
//


#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

#include <SDL2/SDL.h>

typedef struct {
    int bullet;
    double x, y, angle;
    double radius ,barrel_lenght, barrel_thickness , width, lenght;
    int light_color, dark_color;
    int score;
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

}Co;

typedef struct {
    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;

    int pressed;
} button_t;

typedef enum{
    VERTICAL, HORIZONTAL
}direction;

typedef struct {
    double pos[4];
    direction dir;
}Wall;

#endif //PROJECT_STRUCTS_H
