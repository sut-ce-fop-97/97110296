//
// Created by amin on 12/18/18.
//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include "physics.h"
#include "structs.h"
#include "view.h"
#include "init.h"
#include "logic.h"


int main() {

    ///initializing
    Map *map = malloc(sizeof(Map));
    map->players = determine_player_number();
    if(!map->players)
        return 0;
    const float FPS =4/sqrt(map->players);
    map->tanks = malloc(sizeof(Tank*));
    for(int i = 0 ; i<map->players ; i++){
        map->tanks[i] = malloc(sizeof(Tank));
        map->tanks[i]->score = 0;
    }


    /// SDL startings
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, 1325, 1000, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    start_game(map, window, &renderer);

    while (handle_event(map)) {

        ///seting renderer
        int start_ticks = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 206, 239, 255, 255);
        SDL_RenderClear(renderer);

        ///hamdling keys
        handle_keys(map);

        ///End time
        check_end(map, &renderer, window);


        ///showings
        show_walls(map, renderer);
        for(int i = 0 ; i<map->players ; i++)
            if(map->tanks[i]->is_alive)
                show_tank(map->tanks[i], renderer);
        show_scores(map , renderer);
        if(map->bullets != NULL)
            show_bullet(map, renderer);



        ///present render
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < FPS);
    }

    /// SDL endings
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


