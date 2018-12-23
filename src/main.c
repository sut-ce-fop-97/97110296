//
// Created by amin on 12/18/18.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "logic.h"
#include "physics.h"
#include "structs.h"
#include "view.h"



int main() {


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



    Tank *tank = init_tank();
    const double FPS = 1000;
    int flag = 1;
    Bullet_Node* bullets = NULL;

    while (handle_event(tank, &bullets)) {

        ///creating renderer
        int start_ticks = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        ///hamdling keys
        handle_keys(tank, &bullets);


        ///showings
        if(bullets != NULL)
            show_bullet(&bullets, renderer);
        show_tank(tank, renderer);
        show_walls(renderer);


        ///terminating render
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 30 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


