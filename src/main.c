//
// Created by amin on 12/18/18.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <zconf.h>
#include "physics.h"
#include "structs.h"
#include "view.h"
#include "init.h"


//
//thickLineColor(renderer, x + t->lenght/2 * cos(a), y - t->lenght/2 * sin(a), x - t->lenght/2 * cos(a), y + t->lenght/2 * sin(a), t->width, t->light_color);                                                                         //shasi
//thickLineColor(renderer, x, y, x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), t->barrel_thickness, t->dark_color);                                                                                                                 //barrel
//thickLineColor(renderer, x+t->lenght/2*cos(a)+0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) + 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) + 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) + 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 1
//thickLineColor(renderer, x+t->lenght/2*cos(a)-0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) - 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) - 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) - 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 2
//filledCircleColor(renderer, x, y, 0.4*t->width, t->dark_color);                                                                                                                                                                 //circle
//circleRGBA(renderer, x, y, 0.4*t->width, black);                                                                                                                                                                     //circle border
//

//bool collide(int *wall, double x, double y,int raduis) {
//    if(wall[0] == wall[2]){
//        ///TODO
//    }
//    return 0;
//}
//
//bool can_turn(Tank *t, int direction, int **walls, int count_of_walls) {
//    double x = t->x, y = t->y, a = t->angle;
//    for(int i = 0 ; i<count_of_walls ; i++){
//        if(collide(walls[i], x+t->lenght/2*cos(a)+0.65*t->width*sin(a) ,y - t->lenght/2 * sin(a) + 0.65*t->width * cos(a), 1));
//    }
//    return 0;
//}


int main() {

    int player_number = determine_player_number();

    if(!player_number)
        return 0;

    const float FPS = 0.00001*sqrt(sqrt(player_number));
    Bullet_Node* bullets = NULL;
    long long **walls;
    int walls_count;
    int maxx = 0, maxy = 0;

    double ratio = generate_walls(&walls, &walls_count, &maxx, &maxy);


    Tank **tanks = malloc(sizeof(Tank*));
    for(int i = 0 ; i<player_number ; i++){
        tanks[i] = init_tank(ratio, maxx, maxy, i);
        sleep(1);
    }


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, maxx*ratio+350, maxy*ratio+40, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    while (handle_event(tanks, &bullets, player_number)) {

        ///creating renderer
        int start_ticks = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        ///hamdling keys
        handle_keys(tanks, player_number);


        ///showings
        if(bullets != NULL)
            show_bullet(&bullets, renderer, player_number);
        for(int i = 0 ; i<player_number ; i++)
            show_tank(tanks[i], renderer);
        show_walls(renderer, walls, walls_count);
        show_scores(tanks, player_number, renderer, ratio*(maxx+1));

        ///present render
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < FPS);
    }

    ///terminate windows
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


