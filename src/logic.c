//
// Created by amin on 12/25/18.
//

#include "logic.h"





#include "structs.h"


//
//thickLineColor(renderer, x + t->lenght/2 * cos(a), y - t->lenght/2 * sin(a), x - t->lenght/2 * cos(a), y + t->lenght/2 * sin(a), t->width, t->light_color);                                                                         //shasi
//thickLineColor(renderer, x, y, x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), t->barrel_thickness, t->dark_color);                                                                                                                 //barrel
//thickLineColor(renderer, x+t->lenght/2*cos(a)+0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) + 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) + 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) + 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 1
//thickLineColor(renderer, x+t->lenght/2*cos(a)-0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) - 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) - 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) - 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 2
//filledCircleColor(renderer, x, y, 0.4*t->width, t->dark_color);                                                                                                                                                                 //circle
//circleRGBA(renderer, x, y, 0.4*t->width, black);                                                                                                                                                                     //circle border
//

double min(double a, double b) {
    if(a<b)
        return a;
    return b;
}


double max(double a, double b){
    if(a>b)
        return a;
    return b;
}

bool collide(Wall *wall, double x, double y, double radius, double tank_width) {
    if (wall->dir == HORIZONTAL) {
        if (x > min(wall->pos[0], wall->pos[2]) && x < max(wall->pos[0], wall->pos[2]) &&
            abs(y - wall->pos[3]) < radius)
            return 1;
        if (abs(wall->pos[3] - y) < tank_width / 8 &&
            min(abs(wall->pos[0] - x), abs(wall->pos[2] - x)) < tank_width / 32)
            return 1;
    } else {
        if (y > min(wall->pos[1], wall->pos[3]) && y < max(wall->pos[1], wall->pos[3]) &&
               abs(x - wall->pos[0]) < radius)
        return 1;

    if (abs(wall->pos[0] - x) < tank_width / 2 && min(abs(wall->pos[1] - y), abs(wall->pos[3] - y)) < tank_width / 32)
        return 1;
    }


    return 0;
}


bool can_go(Tank *t, Wall **walls, int count_of_walls, int dir, int player) {
    double x = t->x, y = t->y, a = t->angle, radius = 1.5;
    static int level = 0;
    for(int i = 0 ; i<count_of_walls ; i++){
        if(dir) {
            if (collide(walls[i], x + (t->lenght / 2) * cos(a) + (t->width / 2) * sin(a),
                        y - (t->lenght / 2) * sin(a) + (t->width / 2) * cos(a), radius, t->width)                         //head-right
                || collide(walls[i], x + (t->lenght / 2) * cos(a) - (t->width / 2) * sin(a),
                           y - (t->lenght / 2) * sin(a) - (t->width / 2) * cos(a), 5, t->width)                      //head-left
                || collide(walls[i], x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), radius, t->width)      //barrel
                || collide(walls[i], x, y, t->width * 0.65, t->width))                                                        //center                                       //center
                return 0;
        }
        else if(collide(walls[i], x - t->lenght / 2 * cos(a) + t->width / 2 * sin(a),
                        y + t->lenght / 2 * sin(a) + t->width / 2 * cos(a), radius, t->width)   //tail-right
           || collide(walls[i], x - t->lenght / 2 * cos(a) - t->width / 2 * sin(a),
                      y + t->lenght / 2 * sin(a) - t->width / 2 * cos(a), radius, t->width) //tail-left
              || collide(walls[i], x, y, t->width * 0.65, t->width))                                                                              //center
                return 0;

    }
    return 1;
}


bool can_turn(Tank *t, Wall **walls, int count_of_walls) {
    double x = t->x, y = t->y, a = t->angle, radius = 0.5;
    for(int i = 0 ; i<count_of_walls ; i++){
        if (collide(walls[i], x + (t->lenght / 2) * cos(a) + (t->width / 2) * sin(a),
                    y - (t->lenght / 2) * sin(a) + (t->width / 2) * cos(a), radius, 0)                         //head-right
            || collide(walls[i], x + (t->lenght / 2) * cos(a) - (t->width / 2) * sin(a),
                       y - (t->lenght / 2) * sin(a) - (t->width / 2) * cos(a), radius, 0)                      //head-left
            || collide(walls[i], x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), 1, 0)
            || collide(walls[i], x - t->lenght / 2 * cos(a) + t->width / 2 * sin(a),
                       y + t->lenght / 2 * sin(a) + t->width / 2 * cos(a), radius, 0)   //tail-right
            || collide(walls[i], x - t->lenght / 2 * cos(a) - t->width / 2 * sin(a),
                       y + t->lenght / 2 * sin(a) - t->width / 2 * cos(a), radius, 0) //tail-left
            || collide(walls[i], x, y, t->lenght / 2, 0))
                return 0;
    }
    return 1;
}