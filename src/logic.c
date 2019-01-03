//
// Created by amin on 12/25/18.
//

#include "logic.h"





#include "structs.h"
#include "physics.h"
#include "init.h"
#include "effects.h"


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

bool can_go(Map *map, int player_number, int dir) {
    double x = map->tanks[player_number]->x, y = map->tanks[player_number]->y, radius = 1.5;
    update_corners(map->tanks[player_number]);
    for(int i = 0 ; i<map->count_of_walls ; i++){
        if(dir) {
            if (collide(map->walls[i],map->tanks[player_number]->corners[1].x ,map->tanks[player_number]->corners[1].y, radius, map->tanks[player_number]->width)          //head-right
                || collide(map->walls[i], map->tanks[player_number]->corners[4].x, map->tanks[player_number]->corners[4].y, 5, map->tanks[player_number]->width)           //head-left
                || collide(map->walls[i], map->tanks[player_number]->corners[0].x, map->tanks[player_number]->corners[0].y, radius, map->tanks[player_number]->width)      //barrel
                || collide(map->walls[i], x, y, map->tanks[player_number]->width * 0.65, map->tanks[player_number]->width))                                                 //center                                       //center
                return 0;
        }
        else if(collide(map->walls[i], map->tanks[player_number]->corners[2].x , map->tanks[player_number]->corners[2].y, radius, map->tanks[player_number]->width)   //tail-right
           || collide(map->walls[i], map->tanks[player_number]->corners[3].x, map->tanks[player_number]->corners[3].y, radius, map->tanks[player_number]->width)      //tail-left
              || collide(map->walls[i], x, y, map->tanks[player_number]->width * 0.65, map->tanks[player_number]->width))                                             //center
                return 0;

    }
    return 1;
}

bool can_turn(Map *map , int player_number) {
    update_corners(map->tanks[player_number]);
    double x = map->tanks[player_number]->x, y = map->tanks[player_number]->y, a = map->tanks[player_number]->angle, radius = 0.5;
    for(int i = 0 ; i<map->count_of_walls ; i++){
        if (collide(map->walls[i], map->tanks[player_number]->corners[1].x, map->tanks[player_number]->corners[1].y, radius, 0)                         //head-right
            || collide(map->walls[i], map->tanks[player_number]->corners[4].x, map->tanks[player_number]->corners[4].y, radius, 0)                      //head-left
            || collide(map->walls[i], x + map->tanks[player_number]->barrel_lenght * cos(a), y - map->tanks[player_number]->barrel_lenght * sin(a), 1, 0)
            || collide(map->walls[i], map->tanks[player_number]->corners[2].x, map->tanks[player_number]->corners[2].y, radius, 0)   //tail-right
            || collide(map->walls[i], map->tanks[player_number]->corners[3].x, map->tanks[player_number]->corners[3].y, radius, 0) //tail-left
            || collide(map->walls[i], x, y, map->tanks[player_number]->lenght / 2, 0))
                return 0;
    }
    return 1;
}

int meet_wall(Map *map, Bullet b) {
    for(int i = 0 ; i<map->count_of_walls ; i++){
        if(map->walls[i]->dir == HORIZONTAL) {
            double minpos = min(map->walls[i]->pos[0], map->walls[i]->pos[2]), maxpos = max(map->walls[i]->pos[0], map->walls[i]->pos[2]);
            if(abs(b.y - map->walls[i]->pos[1]) < b.radius && ((abs(b.x - minpos) < b.radius && b.x < minpos )
                                                            || (abs(b.x - maxpos) < b.radius && b.x > maxpos )))
                return 2;
            if(b.x >  minpos && b.x < maxpos && abs(b.y-map->walls[i]->pos[3])<b.radius)
                return 1;

        } else {
            double minpos = min(map->walls[i]->pos[1], map->walls[i]->pos[3]), maxpos = max(map->walls[i]->pos[1], map->walls[i]->pos[3]);
            if(abs(b.x - map->walls[i]->pos[0]) < b.radius && ((abs(b.y - minpos) < b.radius && b.y < minpos )
                                                               || (abs(b.y - maxpos) < b.radius && b.y > maxpos )))
                return 1;
            if (b.y > minpos && b.y < maxpos && abs(b.x - map->walls[i]->pos[0]) < b.radius)
                return 2;

        }
    }
    return  0;
}

bool is_lefthand(Point p, Line l) {
    return ((l.p[1].x - l.p[0].x)*(p.y-l.p[0].y) - (l.p[1].y-l.p[0].y)*(p.x-l.p[0].x) < 0);
}

void check_end(Map *map) {
    if(map->end_time > -1){
        map->end_time--;
        if(map->end_time == 0){
            for(int i = 0 ; i<map->players; i++)
                if(map->tanks[i]->is_alive)
                    map->tanks[i]->score++;
            start_game(map);
        }
    }
}

bool meet_tank(Map *map, Bullet b){
    for(int i = 0 ; i<map->players ; i++){
        Tank *t = map->tanks[i];
        if(!t->is_alive) continue;
        update_corners(t);
        bool flag = true ;
        for(int j = 0 ; j<5 ; j++){
            Point p;
            p.x = b.x;
            p.y = b.y;
            Line l;
            l.p[0].x = t->corners[j].x;
            l.p[0].y = t->corners[j].y;
            l.p[1].x = t->corners[(j+1)%5].x;
            l.p[1].y = t->corners[(j+1)%5].y;
            if(is_lefthand(p, l)){
                flag = false;
                break;
            }
        }
        if(flag){
            map->tanks[i]->is_alive = false;
//            play_sound_effect();
            /// TODO play sound without delay
            int c = 0 ;
            for(int i= 0 ; i<map->players ; i++){
                if(map->tanks[i]->is_alive)
                    c++;
            }
            if(c  == 1)
                map->end_time = 1000;
            return 1;
        }
    }
    return 0;
}