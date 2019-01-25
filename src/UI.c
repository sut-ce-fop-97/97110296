//
// Created by amin on 1/22/19.
//

#include <SDL2_gfxPrimitives.h>
#include "UI.h"
#include "init.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>


#define black 0,0 ,0, 255

int deltax[] = {  0  , -90 , 0 , +90 ,  0  }
,deltay[] = { -90 ,  0  , 0 ,  0  , +90 };


void show_button(SDL_Renderer *r, button_t *btn, Map *map, bool error) {
    if(error)
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
    SDL_RenderFillRect(r, &btn->draw_rect);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderDrawRect(r, &btn->draw_rect);
    if(error)
        stringRGBA(map->renderer, btn->draw_rect.x + btn->draw_rect.w/2 - 4* strlen(btn->text),
                   btn->draw_rect.y + btn->draw_rect.h/2 -3 , btn->text, 100, 0,0, 150);
    else
        stringRGBA(map->renderer, btn->draw_rect.x + btn->draw_rect.w/2 - 4* strlen(btn->text),
                   btn->draw_rect.y + btn->draw_rect.h/2 -3 , btn->text, black);

}

static void button_process_event(button_t *buttons, int k, const SDL_Event *ev, int *focus, int mode) {
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
            (ev->key.keysym.sym == SDLK_RETURN && buttons[k].focused && mode)) {
        buttons[k].pressed = true;
        buttons[k].colour.g -= 20;
        buttons[k].colour.r -= 20;
    }

}

static bool button(button_t *btn) {

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}

void tab_controler(SDL_Event evt, button_t *buttons, int *focus, int n) {

    if(evt.type == SDL_KEYUP){
        if(evt.key.keysym.sym == SDLK_DOWN || evt.key.keysym.sym == SDLK_TAB){
            if(buttons[*focus].focused) {
                buttons[*focus].colour.b += 30;
                buttons[*focus].colour.g += 30;
                buttons[*focus].colour.r += 30;
            }
            buttons[*focus].focused = false;
            *focus = (*focus+1)%n;
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
            *focus = (*focus-1+n)%n;
            buttons[*focus].focused = true;
            buttons[*focus].colour.b -= 30;
            buttons[*focus].colour.g -= 30;
            buttons[*focus].colour.r -= 30;
        }

    }

}

int starting_UI(Map *map) {

    // varriables
    int res = 0;
    int quit = 0;
    enum {
        STATE_IN_MENU,
        STATE_IN_GAME,
    } state = 0;

    // checking renderer
    if (map->window == NULL){
        fprintf(stderr, "create pWindow failed: %s\n", SDL_GetError());
        return 1;   // 'error' return status is !0. 1 is good enough
    }
    if(!map->renderer) {   // renderer creation may fail too
        fprintf(stderr, "create renderer failed: %s\n", SDL_GetError());
        return 1;
    }


    // buttons initing
    int mainx = 662, mainy = 300;
    button_t buttons[5];
    for(int i = 0 ; i<5 ; i++){

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

    buttons[4].colour.r = 100;
    buttons[4].colour.g = 100;
    buttons[4].colour.b = 100;
    buttons[4].colour.a = 255;

    buttons[4].draw_rect.x = 20;
    buttons[4].draw_rect.y = 880;
    buttons[4].draw_rect.h = 100;
    buttons[4].draw_rect.w = 200;

    strcpy(buttons[0].text, "One Player");
    strcpy(buttons[1].text, "Two Players");
    strcpy(buttons[2].text, "Three Players");
    strcpy(buttons[3].text, "Four Players");
    strcpy(buttons[4].text, "Settings");




    mainy += 45;
    mainx -= 37;
    int focus = 4;

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
            for(int i = 0 ; i<5 ; i++)
                button_process_event(buttons, i, &evt, &focus, 0);
            tab_controler(evt, buttons, &focus, 5);



        }


        SDL_SetRenderDrawColor(map->renderer, 255, 225, 175, 255);
        SDL_RenderClear(map->renderer);


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
        for(int i = 0 ; i<5 ;i++)
            show_button(map->renderer, buttons+i, map, 0);

        if(state == STATE_IN_MENU) {
            for(int i = 0 ; i<4 ; i++){
                if(button(buttons + i)){
                    res = i+1;
                    state = STATE_IN_GAME;
                }
            }
            if(button(buttons + 4 )){
                SDL_Delay(200);
                settings_UI(map);
                buttons[4].colour.g += 20;
                buttons[4].colour.r += 20;
            }

        } else if(state == STATE_IN_GAME) {
            SDL_Delay(200);
            quit = 1;
        }

        stringRGBA(map->renderer, mainx - 60, mainy - 100, "How many players do we have?", black);


        SDL_RenderPresent(map->renderer);
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
    button_t buttons[5];
    for(int i = 0 ; i<5 ; i++){

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


    buttons[4].colour.r = 100;
    buttons[4].colour.g = 100;
    buttons[4].colour.b = 100;
    buttons[4].colour.a = 255;

    buttons[4].draw_rect.x = 20;
    buttons[4].draw_rect.y = 880;
    buttons[4].draw_rect.h = 100;
    buttons[4].draw_rect.w = 200;


    strcpy(buttons[4].text, "Settings");
    strcpy(buttons[0].text, "Resume");
    strcpy(buttons[1].text, "Restart");
    strcpy(buttons[2].text, "Load last Game");
    strcpy(buttons[3].text, "Quit");

    mainy += 45;
    mainx -= 23;
    int focus = 4;


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
            for(int i = 0 ; i<5 ; i++)
                button_process_event(buttons, i, &evt, &focus, 0);

            tab_controler(evt, buttons, &focus, 5);


        }


        SDL_SetRenderDrawColor(map->renderer, 255, 225, 175, 255);
        SDL_RenderClear(map->renderer);


        for(int i = 0 ; i<5 ;i++)
            show_button(map->renderer, buttons+i, map, 0);


        if(state == STATE_IN_MENU) {
            if(button(buttons))
                state = STATE_IN_GAME;
            if(button(buttons + 1)){
                map->round = 0;
                map->players = starting_UI(map);
                for(int i = 0 ; i<5 ; i++){
                    map->tanks[i]->score = 0;
                    map->tanks[i]->bullet = 5;
                }
                if(!start_game(map))
                    return 0;
                return 1;
            }
            if(button(buttons + 2)){
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
            if(button(buttons + 3))
                return 0;

            if(button(buttons + 4)){
                SDL_Delay(200);
                settings_UI(map);
                buttons[4].colour.g += 20;
                buttons[4].colour.r += 20;
            }



        } else if(state == STATE_IN_GAME) {
            SDL_Delay(200);
            quit = 1;
        }


        SDL_RenderPresent(map->renderer);
    }

    return 1;
}

const char *to_letter(int i) {
    char result[5];

//        SDLK_UNKNOWN = 0,
//
//        SDLK_SPACE = ' ',
//        SDLK_QUOTE = '\'',
//        SDLK_COMMA = ',',
//        SDLK_MINUS = '-',
//        SDLK_PERIOD = '.',
//        SDLK_0 = '0',
//        SDLK_1 = '1',
//        SDLK_2 = '2',
//        SDLK_3 = '3',
//        SDLK_4 = '4',
//        SDLK_5 = '5',
//        SDLK_6 = '6',
//        SDLK_7 = '7',
//        SDLK_8 = '8',
//        SDLK_9 = '9',
//        SDLK_COLON = ':',
//        SDLK_EQUALS = '=',
//        /*
//           Skip uppercase letters
//         */
//        SDLK_BACKSLASH = '\\',
//        SDLK_BACKQUOTE = '`',
//        SDLK_a = 'a',
//        SDLK_b = 'b',
//        SDLK_c = 'c',
//        SDLK_d = 'd',
//        SDLK_e = 'e',
//        SDLK_f = 'f',
//        SDLK_g = 'g',
//        SDLK_h = 'h',
//        SDLK_i = 'i',
//        SDLK_j = 'j',
//        SDLK_k = 'k',
//        SDLK_l = 'l',
//        SDLK_m = 'm',
//        SDLK_n = 'n',
//        SDLK_o = 'o',
//        SDLK_p = 'p',
//        SDLK_q = 'q',
//        SDLK_r = 'r',
//        SDLK_s = 's',
//        SDLK_t = 't',
//        SDLK_u = 'u',
//        SDLK_v = 'v',
//        SDLK_w = 'w',
//        SDLK_x = 'x',
//        SDLK_y = 'y',
//        SDLK_z = 'z',

//        SDLK_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
//        SDLK_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
//        SDLK_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
//        SDLK_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),
//
//        SDLK_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
//        SDLK_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
//        SDLK_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
//        SDLK_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
//        SDLK_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
//        SDLK_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
//        SDLK_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
//        SDLK_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
//        SDLK_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
//        SDLK_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
//        SDLK_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
//        SDLK_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
//        SDLK_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
//        SDLK_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

        


}

int settings_UI(Map *map){
    int focus = 3, mode = 0;
    bool is_valid[2] = {true, true};
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
    button_t keys[4][5];
    button_t back_btn, target_btn;

    back_btn.pressed = 0;
    back_btn.focused = false;
    strcpy(back_btn.text, "back");
    
    back_btn.colour.r = 120;
    back_btn.colour.g = 120;
    back_btn.colour.b = 120;
    back_btn.colour.a = 255;

    back_btn.draw_rect.x = 20;
    back_btn.draw_rect.y = 880;
    back_btn.draw_rect.h = 100;
    back_btn.draw_rect.w = 200;
    
    

    target_btn.pressed = 0;
    target_btn.focused = false;
    strcpy(target_btn.text, "Change Target");

    target_btn.colour.r = 200;
    target_btn.colour.g = 200;
    target_btn.colour.b = 200;
    target_btn.colour.a = 255;

    target_btn.draw_rect.x = 610;
    target_btn.draw_rect.y = 390;
    target_btn.draw_rect.h = 150;
    target_btn.draw_rect.w = 150;
    


    for(int i = 0 ; i<4 ; i++) {
        for (int j = 0; j < 5; j++) {

            keys[i][j].pressed = 0;
            keys[i][j].focused = false;

            strcpy(keys[i][j].text, map->tanks[i]->keys[j]);

            keys[i][j].colour.r = 200;
            keys[i][j].colour.g = 200;
            keys[i][j].colour.b = 200;
            keys[i][j].colour.a = 255;

            keys[i][j].draw_rect.x = 320 + (i&1)*650 + deltax[j];
            keys[i][j].draw_rect.y = 220 + (i>>1)*400 + deltay[j];
            keys[i][j].draw_rect.h = 91;
            keys[i][j].draw_rect.w = 91;
            
            
        }
        
    }



    // main while
    while(!quit) {
        SDL_Event evt;

        if(SDL_PollEvent(&evt)) {
            // quit on close, pWindow close, or 'escape' key hit
            if(evt.type == SDL_QUIT ||
               (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE)) {
                return 0;
            }
            if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
                return 1;
            if(evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_RETURN ){
                if(mode == 21 && is_valid[1]){
                    target_btn.colour.r = 170;
                    target_btn.colour.g = 170;
                    target_btn.colour.b = 170;
                    mode = 0;
                    is_valid[1] = true;
                } else if(0<mode && mode<21 && is_valid[0]){
                    map->tanks[(mode-1)/5]->keys[(mode-1)%5] = keys[(mode-1)/5][(mode-1)%5].text;
                    puts(map->tanks[(mode-1)/5]->keys[(mode-1)%5]);
                    keys[(mode-1)/5][(mode-1)%5].colour.r = 170;
                    keys[(mode-1)/5][(mode-1)%5].colour.g = 170;
                    keys[(mode-1)/5][(mode-1)%5].colour.b = 170;
                    mode = 0;
                    is_valid[0] = true;
                }
            }

            if(mode && evt.type == SDL_KEYDOWN){
                char pressed = (char)evt.key.keysym.sym;
                if ( mode == 21) {
                    if(evt.key.keysym.sym == SDLK_UP)
                        map->target++;
                    if(evt.key.keysym.sym == SDLK_DOWN)
                        map->target--;
                    int maxx = 0;
                    for(int i = 0 ; i<4 ; i++)
                        if(map->tanks[i]->score > maxx)
                            maxx = map->tanks[i]->score;
                    if(map->target <= maxx)
                        is_valid[1] = false;
                    else
                        is_valid[1] = true;

                } else if((/*isupper(pressed) &&*/ isalpha(pressed)) || isdigit(pressed) || pressed == 'O' || pressed == 'P' || pressed == 'Q' || pressed == 'R'){
                    char tmp[5];
                    switch(pressed){
                        case 'O':
                            strcpy(tmp, "->");
                            break;
                        case 'P':
                            strcpy(tmp, "<-");
                            break;
                        case 'Q':
                            strcpy(tmp, "\\/");
                            break;
                        case 'R':
                            strcpy(tmp, "/\\");
                            break;
                        default:
                             tmp[0] = toupper(pressed);
                             tmp[1] = '\0';
                            break;
                    }
                    bool flag = true;
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 5; j++)
                            if (!strcmp(keys[i][j].text, tmp) && 5*i + j + 1 != mode)
                                flag = false;
                    strcpy(keys[(mode-1)/5][(mode-1)%5].text, tmp);
                    if (flag)
                        is_valid[0] = true;
                    else
                        is_valid[0] = false;
                }
            }

            // pass event to button
            if(!mode){
                for(int i = 0 ; i<4 ; i++)
                    for(int j = 0 ; j<5 ; j++)
                        button_process_event(keys[i], j, &evt, &focus, 0);
                button_process_event(&back_btn, 0, &evt, &focus, 0);
                button_process_event(&target_btn, 0, &evt, &focus, 0);

            }

        }

        SDL_SetRenderDrawColor(map->renderer, 255, 225, 175, 255);
        SDL_RenderClear(map->renderer);

        for(int i = 0 ; i<4 ; i++)
            for(int j = 0 ; j<5 ; j++)
                show_button(map->renderer, &keys[i][j], map, (5*i+j+1 == mode)*!is_valid[0]);
        show_button(map->renderer, &back_btn, map, 0);
        show_button(map->renderer, &target_btn, map, (21 == mode)*!is_valid[1]);

        if(state == STATE_IN_MENU && !mode) {
            if(button(&back_btn))
                state = STATE_IN_GAME;
            if(button(&target_btn)) {
                target_btn.colour.b = 200;
                target_btn.colour.g = 50;
                target_btn.colour.r = 50;
                mode = 21;
            }
            for(int i = 0 ; i<4 ; i++)
                for(int j = 0 ; j<5; j++){
                    if(button(&keys[i][j])){
                        keys[i][j].colour.b = 200;
                        keys[i][j].colour.g = 50;
                        keys[i][j].colour.r = 50;
                        mode = 5*i + j + 1;
                    }
                }
        } else if(state == STATE_IN_GAME) {
            SDL_Delay(200);
            quit = 1;
        }
        stringRGBA(map->renderer, 336, 100, "Player 1", black);
        stringRGBA(map->renderer, 986, 100, "Player 2", black);
        stringRGBA(map->renderer, 336, 500, "Player 3", black);
        stringRGBA(map->renderer, 986, 500, "Player 4", black);

        char tmp[20];
        sprintf(tmp , "%d", map->target);
        if(mode && !is_valid[1])
            stringRGBA(map->renderer, 680, 480, tmp, 100, 0, 0 , 255);
        else
            stringRGBA(map->renderer, 680, 480, tmp, black);

        SDL_RenderPresent(map->renderer);

    }

    return 1;
}

