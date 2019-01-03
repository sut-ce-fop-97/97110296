//
// Created by amin on 12/24/18.
//


#include <SDL_events.h>
#include <stdbool.h>
#include <SDL_system.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "init.h"
#include "structs.h"


#define black 0,0 ,0, 255

static void button_process_event(button_t *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
           ev->button.x >= btn->draw_rect.x &&
           ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
           ev->button.y >= btn->draw_rect.y &&
           ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}

static bool button(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}

int determine_player_number(){
    int res = 0;
    int quit = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Choose number of players",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 300, 300,SDL_WINDOW_OPENGL);

    if (window == NULL){
        fprintf(stderr, "create window failed: %s\n", SDL_GetError());
        return 1;   // 'error' return status is !0. 1 is good enough
    }

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {   // renderer creation may fail too
        fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect rct;
    rct.x = 0 ;
    rct.y = 0;
    rct.h = 500;
    rct.w = 800;

    // button state - colour and rectangle
    button_t one_player = {
            .colour = { .r = 251, .g = 255, .b = 25, .a = 255 },
            .draw_rect = { .x = 20, .y = 20, .w = 260, .h = 63 },
    };

    button_t two_player = {
            .colour = { .r = 255, .g = 192, .b = 35, .a = 255 },
            .draw_rect = { .x = 20, .y = 87, .w = 260, .h = 63 },
    };
    button_t three_player = {
            .colour = { .r = 255, .g = 145, .b = 34, .a = 255 },
            .draw_rect = { .x = 20, .y = 154, .w = 260, .h = 63 },
    };
    button_t four_player = {
            .colour = { .r = 255, .g = 85, .b = 33, .a = 255 },
            .draw_rect = { .x = 20, .y = 221, .w = 260, .h = 63 },
    };

    enum {
        STATE_IN_MENU,
        STATE_IN_GAME,
    } state = 0;

    while(!quit) {
        SDL_Event evt;    // no need for new/delete, stack is fine

        // event loop and draw loop are separate things, don't mix them
        while(SDL_PollEvent(&evt)) {
            // quit on close, window close, or 'escape' key hit
            if(evt.type == SDL_QUIT ||
               (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) ||
               (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
                return 0;
            }

            // pass event to button
            button_process_event(&one_player, &evt);
            button_process_event(&two_player, &evt);
            button_process_event(&three_player, &evt);
            button_process_event(&four_player, &evt);

        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);


/*//        TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

        SDL_Color White = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, "amin"); //now you can convert it into a texture

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 20;  //controls the rect's x coordinate
        Message_rect.y = 20; // controls the rect's y coordinte
        Message_rect.w = 100; // controls the width of the rect
        Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget too free your surface and texture*/

        if(state == STATE_IN_MENU) {
            if(button(renderer, &one_player)) {
//                printf("one_player button pressed\n");
                res = 1;
                printf("This feature will be added as soon as possible.\n");
//                state = STATE_IN_GAME;   // state change - button will not be drawn anymore
            } else if(button(renderer, &two_player)) {
                printf("two_player button pressed\n");
                res = 2;
                state = STATE_IN_GAME;   // state change - button will not be drawn anymore
            } else if(button(renderer, &three_player)) {
                printf("three_player button pressed\n");
                res = 3;
                state = STATE_IN_GAME;   // state change - button will not be drawn anymore
            } else if(button(renderer, &four_player)) {
                printf("four_player button pressed\n");
                res = 4;
                state = STATE_IN_GAME;   // state change - button will not be drawn anymore
            }
        } else if(state == STATE_IN_GAME) {
            quit = 1;
        }
//        stringRGBA(renderer, 110, 50, "One Player", black);
//        stringRGBA(renderer, 110, 117, "Two Player", black);
//        stringRGBA(renderer, 106, 182, "Three Player", black);
//        stringRGBA(renderer, 108, 250, "Four Player", black);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return res;

}