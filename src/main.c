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
#include "logic.h"
#include "physics.h"
#include "structs.h"
#include "view.h"
#include "init.h"



int main() {

    int player_number = detemine_player_number();

    if(!player_number)
        return 0;

    const double FPS = 1000;
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
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, maxx*ratio+240, maxy*ratio+40, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    while (handle_event(tanks[0], &bullets)) {

        ///creating renderer
        int start_ticks = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        ///hamdling keys
        handle_keys(tanks[0]);


        ///showings
        if(bullets != NULL)
            show_bullet(&bullets, renderer);
        for(int i = 0 ; i<player_number ; i++)
            show_tank(tanks[i], renderer);
        show_walls(renderer, walls, walls_count);
        show_scores(tanks, player_number, ratio, maxx, maxy, renderer);

        ///present render
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 100 / FPS);
    }

    ///terminate windows
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


