//
// Created by amin on 1/22/19.
//

#include <SDL2_gfxPrimitives.h>
#include "UI.h"
#include "init.h"


#define black 0,0 ,0, 255



static void button_process_event(button_t *buttons, int k, const SDL_Event *ev, int *focus) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEMOTION ){
        if(ev->button.x >= buttons[k].draw_rect.x &&
           ev->button.x <= (buttons[k].draw_rect.x + buttons[k].draw_rect.w) &&
           ev->button.y >= buttons[k].draw_rect.y &&
           ev->button.y <= (buttons[k].draw_rect.y + buttons[k].draw_rect.h) &&
           !buttons[k].focused) {

            buttons[k].colour.b -= 30;
            buttons[k].colour.g -= 30;
            buttons[k].colour.r -= 30;
            for(int i = 0 ; i<4 ; i++)
                buttons[i].focused = false;
            buttons[k].focused = true;
            *focus = k;
        }
        else if(!(ev->button.x >= buttons[k].draw_rect.x &&
                  ev->button.x <= (buttons[k].draw_rect.x + buttons[k].draw_rect.w) &&
                  ev->button.y >= buttons[k].draw_rect.y &&
                  ev->button.y <= (buttons[k].draw_rect.y + buttons[k].draw_rect.h)) &&
                buttons[k].focused){
            buttons[k].colour.b += 30;
            buttons[k].colour.g += 30;
            buttons[k].colour.r += 30;
            buttons[k].focused = false;

        }
    }
    if((ev->type == SDL_MOUSEBUTTONDOWN && ev->button.button == SDL_BUTTON_LEFT && buttons[k].focused) ||
            ev->key.keysym.sym == SDLK_RETURN && buttons[k].focused) {
        buttons[k].pressed = true;
        buttons[k].colour.g -= 20;
        buttons[k].colour.r -= 20;
    }

}

static bool button(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawRect(r, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}

void tab_controler(SDL_Event evt, button_t *buttons, int *focus) {

    if(evt.type == SDL_KEYUP){
        if(evt.key.keysym.sym == SDLK_DOWN || evt.key.keysym.sym == SDLK_TAB){
            if(buttons[*focus].focused) {
                buttons[*focus].colour.b += 30;
                buttons[*focus].colour.g += 30;
                buttons[*focus].colour.r += 30;
            }
            buttons[*focus].focused = false;
            *focus = (*focus+1)%4;
            buttons[*focus].focused = true;
            buttons[*focus].colour.b -= 30;
            buttons[*focus].colour.g -= 30;
            buttons[*focus].colour.r -= 30;
        } if(evt.key.keysym.sym == SDLK_UP){
            if(buttons[*focus].focused) {
                buttons[*focus].colour.b += 30;
                buttons[*focus].colour.g += 30;
                buttons[*focus].colour.r += 30;
            }
            buttons[*focus].focused = false;
            *focus = (*focus+3)%4;
            buttons[*focus].focused = true;
            buttons[*focus].colour.b -= 30;
            buttons[*focus].colour.g -= 30;
            buttons[*focus].colour.r -= 30;
        }

    }

}

int start_UI(SDL_Window *window, SDL_Renderer *renderer) {

    // varriables
    int res = 0;
    int quit = 0;
    enum {
        STATE_IN_MENU,
        STATE_IN_GAME,
    } state = 0;

    // checking renderer
    if (window == NULL){
        fprintf(stderr, "create pWindow failed: %s\n", SDL_GetError());
        return 1;   // 'error' return status is !0. 1 is good enough
    }
    if(!renderer) {   // renderer creation may fail too
        fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
        return 1;
    }


    // buttons initing
    int mainx = 662, mainy = 300;
    button_t buttons[4];
    for(int i = 0 ; i<4 ; i++){

        buttons[i].pressed = 0;
        buttons[i].focused = false;

        buttons[i].colour.r = 255;
        buttons[i].colour.g = 245 - i*60;
        buttons[i].colour.b = 30;
        buttons[i].colour.a = 255;

        buttons[i].draw_rect.x = mainx - 200;
        buttons[i].draw_rect.y = mainy + i*120;
        buttons[i].draw_rect.h = 100;
        buttons[i].draw_rect.w = 400;


    }



    mainy += 45;
    mainx -= 37;
    int focus = 0;

    // main while
    while(!quit) {

        SDL_Event evt;


        while(SDL_PollEvent(&evt)) {
            // quit on close, pWindow close, or 'escape' key hit
            if(evt.type == SDL_QUIT ||
               (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) ||
               (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
                return 0;
            }

            // pass evtent to button
            for(int i = 0 ; i<4 ; i++)
                button_process_event(buttons, i, &evt, &focus);
            tab_controler(evt, buttons, &focus);



        }


        SDL_SetRenderDrawColor(renderer, 255, 225, 175, 255);
        SDL_RenderClear(renderer);


/*
        TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

        SDL_Color White = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, "amin"); //now you can convert it into a texture

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 20;  //controls the rect's x coordinate
        Message_rect.y = 20; // controls the rect's y coordinte
        Message_rect.w = 100; // controls the width of the rect
        Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the pWindow/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget too free your surface and texture
*/

        if(state == STATE_IN_MENU) {
            for(int i = 0 ; i<4 ; i++){
                if(button(renderer, buttons+i)){
                    res = i+1;
                    state = STATE_IN_GAME;
                }
            }

        } else if(state == STATE_IN_GAME) {
            SDL_Delay(200);
            quit = 1;
        }

        stringRGBA(renderer, mainx - 60, mainy - 100, "How many players do we have?", black);

        stringRGBA(renderer, mainx, mainy, "One Player", black);
        stringRGBA(renderer, mainx, mainy + 120, "Two Player", black);
        stringRGBA(renderer, mainx-4, mainy + 240, "Three Player", black);
        stringRGBA(renderer, mainx-2, mainy + 360, "Four Player", black);


        SDL_RenderPresent(renderer);
    }

    return res;

}

int pause_UI(Map *map){

    int quit = 0;

    enum {
        STATE_IN_MENU,
        STATE_IN_GAME,
    } state = 0;

    // checking map->renderer
    if (map->window == NULL){
        fprintf(stderr, "create pWindow failed: %s\n", SDL_GetError());
        return 0;   // 'error' return status is !0. 1 is good enough
    }
    if(!map->renderer) {   // map->renderer creation may fail too
        fprintf(stderr, "create map->renderer failed: %s\n", SDL_GetError());
        return 0;
    }


    // buttons initing
    int mainx = 662, mainy = 300;
    button_t buttons[4];
    for(int i = 0 ; i<4 ; i++){

        buttons[i].pressed = 0;
        buttons[i].focused = false;

        buttons[i].colour.r = 255;
        buttons[i].colour.g = 245 - i*60;
        buttons[i].colour.b = 30;
        buttons[i].colour.a = 255;

        buttons[i].draw_rect.x = mainx - 200;
        buttons[i].draw_rect.y = mainy + i*120;
        buttons[i].draw_rect.h = 100;
        buttons[i].draw_rect.w = 400;


    }



    mainy += 45;
    mainx -= 23;
    int focus = 0;


    // main while
    while(!quit) {

        SDL_Event evt;


        while(SDL_PollEvent(&evt)) {
            // quit on close, pWindow close, or 'escape' key hit
            if(evt.type == SDL_QUIT ||
               (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE)) {
                return 0;
            }
            if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
                return 1;

            // pass event to button
            for(int i = 0 ; i<4 ; i++)
                button_process_event(buttons, i, &evt, &focus);

            tab_controler(evt, buttons, &focus);


        }


        SDL_SetRenderDrawColor(map->renderer, 255, 225, 175, 255);
        SDL_RenderClear(map->renderer);


        if(state == STATE_IN_MENU) {
            if(button(map->renderer, buttons))
                state = STATE_IN_GAME;
            if(button(map->renderer, buttons+1)){
                map->round = 0;
                map->players = start_UI(map->window, map->renderer);
                for(int i = 0 ; i<4 ; i++){
                    map->tanks[i]->score = 0;
                    map->tanks[i]->bullet = 5;
                }
                if(!start_game(map))
                    return 0;
                return 1;
            }
            if(button(map->renderer, buttons+2)){
                if(load_last_game(map)){
                    start_game(map);
                    state = STATE_IN_GAME;
                }else{
                    buttons[2].focused = false;
                    buttons[2].pressed = false;
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR , "Error","Last game is not Saved.",map->window);
                    buttons[2].colour.g += 50;
                    buttons[2].colour.r += 50;
                    buttons[2].colour.b += 30;
                }
            }
            if(button(map->renderer, buttons+3))
                return 0;



        } else if(state == STATE_IN_GAME) {
            SDL_Delay(200);
            quit = 1;
        }

        stringRGBA(map->renderer, mainx+2, mainy, "Resume", black);
        stringRGBA(map->renderer, mainx, mainy + 120, "Restart", black);
        stringRGBA(map->renderer, mainx-28, mainy + 240, "Load last Game", black);
        stringRGBA(map->renderer, mainx+6, mainy + 360, "Quit", black);


        SDL_RenderPresent(map->renderer);
    }

    return 1; ///TODO
}



