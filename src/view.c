//
// Created by amin on 12/18/18.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "view.h"
#include "structs.h"
#include "physics.h"


#define black 0,0 ,0, 255




void show_tank(Tank *t, SDL_Renderer *renderer) {
    double a = t->angle, x = t->x, y = t->y;
    thickLineColor(renderer, x + t->lenght/2 * cos(a), y - t->lenght/2 * sin(a), x - t->lenght/2 * cos(a), y + t->lenght/2 * sin(a), t->width, t->light_color);                                                                         //shasi
    thickLineColor(renderer, x, y, x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), t->barrel_thickness, t->dark_color);                                                                                                                 //barrel
    thickLineColor(renderer, x+t->lenght/2*cos(a)+0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) + 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) + 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) + 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 1
    thickLineColor(renderer, x+t->lenght/2*cos(a)-0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) - 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) - 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) - 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 2
    filledCircleColor(renderer, x, y, 0.4*t->width, t->dark_color);                                                                                                                                                                 //circle
    circleRGBA(renderer, x, y, 0.4*t->width, black);                                                                                                                                                                     //circle border

}


int to_int(char buff[5]) {
    int res = 0;
    char* it = buff;
    while(*it != '\0'){
        res = 10*res + *it - '0';
        it++;
    }
    return res;
}

void show_walls(struct SDL_Renderer * renderer, long long int ** walls, int n){
    for(int i = 0 ; i<n ; i++)
        thickLineRGBA(renderer, walls[i][0], walls[i][1], walls[i][2], walls[i][3], 5, black);
}

int max(int a, int b){
    if(a>b)
        return a;
    return b;
}

double generate_walls(long long int ***walls, int *n, int *maxx, int *maxy) {
    FILE *file = fopen("/home/amin/Desktop/project/src/mapmap.txt", "r");
    char buff[5] ;
    for(int i = 0 ; i<5 ; i++)
        buff[i] = '\0';
    fscanf(file, "%s", buff);
    *n = to_int(buff);
    (*walls) = malloc(*n* sizeof(long long*));
    for(int i = 0 ; i<*n ; i++)
        (*walls)[i] = malloc(4*sizeof(long long));
    for(int i = 0 ; i<*n ; i++){
        for(int j = 0 ; j<4 ;j++){
            for(int k = 0 ; k<5 ; k++)
                buff[k] = '\0';
            fscanf(file, "%s", buff);
            (*walls)[i][j] = to_int(buff);
            if(j & 1)
                *maxy = max(*maxy, (*walls)[i][j]);
            else
                *maxx = max(*maxx, (*walls)[i][j]);

        }
    }
    int max_of_max = max(*maxx, *maxy);
    double ratio = 960.0 / max_of_max;
    for(int i = 0 ; i<*n ; i++)
        for(int j = 0 ; j<4 ; j++){
            (*walls)[i][j] *= ratio;
            (*walls)[i][j] += 20;
        }
    fclose(file);
    return  ratio;
}

void show_bullet(Bullet_Node **bullets, SDL_Renderer *renderer, double players) {
    Bullet_Node *b_node = *bullets;
    while(b_node != NULL){
        if(b_node->b.life_time == 0){
            b_node = NULL;
            return;
        }
        filledCircleRGBA(renderer, (Sint16) b_node->b.x, (Sint16) b_node->b.y, (Sint16) b_node->b.radius, black);
        b_node->b.life_time--;
        b_node->b.x += sqrt(players) * 0.4*cos(b_node->b.angle);
        b_node->b.y += sqrt(players) * 0.4*sin(b_node->b.angle);
        b_node = b_node->next;
    }
}


void show_scores(Tank **tanks, int n, SDL_Renderer *renderer, double d) {
    int x = d + 20, y = 160;
    for(int i = 0 ; i<n ; i++){
        Tank* tmp_tank = malloc(sizeof(Tank));
        tmp_tank->bullet = tanks[i]->bullet;
        tmp_tank->lenght = 150;
        tmp_tank->width = 125;
        tmp_tank->barrel_lenght = 100;
        tmp_tank->barrel_thickness = 20;

        switch(i){
            case 0:
                tmp_tank->light_color =  255 | (95 << 8) | (66 << 16) | (255 << 24);
                tmp_tank->dark_color = 255 | (255 << 24);
                break;
            case 1:
                tmp_tank->light_color =  66 | (134 << 8) | (244<< 16) | (255 << 24);
                tmp_tank->dark_color = 0 | (80 << 8) | (255<< 16) | (255 << 24);
                break;
            case 2:
                tmp_tank->light_color =  243 | (112 << 8) | (255 << 16) | (255 << 24);
                tmp_tank->dark_color = 187 | (0 << 8) | (255 << 16) | (255 << 24);
                break;
            case 3:
                tmp_tank->light_color =  155 | (255 << 8) | (106 << 16) | (255 << 24);
                tmp_tank->dark_color = 0 | (255 << 8) | (38<< 16) | (255 << 24);
                break;
        }
        tmp_tank->x = x;
        tmp_tank->y = y;
        tmp_tank->angle = M_PI/2;
        y += 50+tmp_tank->lenght/2 + tmp_tank->barrel_lenght;
        show_tank(tmp_tank, renderer);
    }
}