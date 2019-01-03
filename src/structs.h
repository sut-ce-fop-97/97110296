//
// Created by amin on 12/18/18.
//


#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    double x, y;
}Point;

typedef struct {
    int bullet;
    double x, y, angle;
    double radius ,barrel_lenght, barrel_thickness , width, lenght;
    int light_color, dark_color;
    int score;
    Point corners[5];
    bool is_alive;
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

typedef struct {
    Tank **tanks;
    Wall **walls;
    Bullet_Node *bullets;
    int players;
    int count_of_walls;
    int count_of_bullets;
    double maxx, maxy, ratio;

}Map;

typedef struct {
    Point p[2];
}Line;

#endif //PROJECT_STRUCTS_H
