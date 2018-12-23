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


//#define red 255 , 0, 0,255
#define light_red 255 , 95, 66,230
#define black 0,0 ,0, 255
//#define light_red2 242, 30, 0,230

SDL_Window *window;

SDL_Renderer *renderer;

SDL_Renderer* init_window(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return renderer;

}

void  quit_window(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void show_tank(Tank *t, SDL_Renderer *renderer) {

    Color red = {
            .light = 255 | (95 << 8) | (66<< 16) | (230<< 24),
            .dark = 255  | (255 << 24)
    };

    double a = t->angle, x = t->x, y = t->y;
    thickLineColor(renderer, x + 30 * cos(a), y - 30 * sin(a), x - 30 * cos(a), y + 30 * sin(a), 50, red.light);                                                                         //shasi
    thickLineColor(renderer, x, y, x + 40 * cos(a), y - 40 * sin(a), 10, red.dark);                                                                                                                 //barrel
//    thickLineColor(renderer, x, y, x + 40 * cos(a), y - 40 * sin(a), 10, red.dark);
    thickLineColor(renderer, x+30*cos(a)+20*sin(a) , y - 30 * sin(a) + 20 * cos(a), x - 30 * cos(a) + 20 * sin(a), y + 30 * sin(a) + 20 * cos(a), 10, red.dark);      //sheni 1
    thickLineColor(renderer, x+30*cos(a)-20*sin(a) , y - 30 * sin(a) - 20 * cos(a), x - 30 * cos(a) - 20 * sin(a), y + 30 * sin(a) - 20 * cos(a), 10, red.dark);      //sheni 2
    filledCircleColor(renderer, x, y, 20, red.dark);                                                                                                                                                                 //circle
    circleRGBA(renderer, x, y, 20, black);                                                                                                                                                                     //circle border

}


int to_int(char buff[50]) {
    int res = 0;
    while(*buff != NULL){
        res = 10*res + *buff - '0';
        buff++;
    }
    return res;
}

void show_walls(struct SDL_Renderer * renderer){
    FILE *file = fopen("/home/amin/Desktop/project/src/mapmap.txt", "r");
    char buff[50] = {};
    fscanf(file, "%s", buff);
    int n = to_int(buff);
    for(int i = 0 ; i<n ; i++){
        int x[4];
        for(int j = 0 ; j<4 ;j++){
            fscanf(file, "%s", buff);
            x[j] = to_int(buff);
        }
        thickLineRGBA(renderer, 20+130*x[0], 20+130*x[1], 20+130*x[2], 20+130*x[3], 5, black);
    }
    fclose(file);
}



void show_bullet(Bullet_Node **bullets, SDL_Renderer *renderer) {
    Bullet_Node *b_node = *bullets;
    while(b_node != NULL){
        if(b_node->b.life_time == 0){
            b_node = NULL;
            return;
        }
        filledCircleRGBA(renderer, (Sint16) b_node->b.x, (Sint16) b_node->b.y, (Sint16) b_node->b.radius, black);
        b_node->b.life_time--;
        b_node->b.x += 0.4*cos(b_node->b.angle);
        b_node->b.y += 0.4*sin(b_node->b.angle);
        b_node = b_node->next;
    }
}