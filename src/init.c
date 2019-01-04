//
// Created by amin on 12/24/18.
//


#include <SDL_events.h>
#include <stdbool.h>
#include <SDL_system.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <zconf.h>
#include <time.h>
#include <bits/types/stack_t.h>
#include "init.h"
#include "structs.h"
#include "view.h"
#include "physics.h"
#include "stack.h"
#include "logic.h"


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


        SDL_SetRenderDrawColor(renderer, 255, 225, 175, 255);
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
        /// TODO error while decommenting this!!
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

Bullet* init_bullet(Tank *t, double ratio) {
    Bullet* b = malloc(sizeof(Bullet));
    b->x = t->x + t->barrel_lenght*cos(t->angle);
    b->y = t->y - t->barrel_lenght*sin(t->angle);
    b->angle = -t->angle;
    b->radius = 0.03*ratio;
    b->life_time = 5000;
    return b;
}

Tank *init_tank(Map *map, int k, bool *** ocupied) {
    Tank *t = map->tanks[k];
    t->is_alive = true;
    t->bullet = 5;
    do{
        t->x = rand()%((int)map->maxx-1);
        t->y = rand()%((int)map->maxy-1);
    }while((*ocupied)[(int)t->x][(int)t->y]);
    (*ocupied)[(int)t->x][(int)t->y] = true;
    t->x = map->ratio*(0.65+t->x) + (1000-map->ratio*(map->maxx-1))/2 + 40;
    t->y = map->ratio*(0.65+t->y) + (1000-map->ratio*(map->maxy-1))/2 + 40;
    t->angle = rand();
    t->lenght = 0.4*map->ratio;
    t->width = 0.35*map->ratio;
    t->barrel_lenght = 0.3*map->ratio;
    t->barrel_thickness = 0.08*map->ratio;

    switch(k){
        case 0:
            t->light_color =  255 | (95 << 8) | (66 << 16) | (255 << 24);
            t->dark_color = 255 | (255 << 24);
            break;
        case 1:
            t->light_color =  66 | (134 << 8) | (244<< 16) | (255 << 24);
            t->dark_color = 0 | (80 << 8) | (255<< 16) | (255 << 24);
            break;
        case 2:
            t->light_color =  243 | (112 << 8) | (255 << 16) | (255 << 24);
            t->dark_color = 187 | (0 << 8) | (255 << 16) | (255 << 24);
            break;
        case 3:
            t->light_color =  155 | (255 << 8) | (106 << 16) | (255 << 24);
            t->dark_color = 0 | (255 << 8) | (38<< 16) | (255 << 24);
            break;
    }

    return t;
}

void start_game(Map *map, SDL_Window *window, SDL_Renderer **renderer) {
    map->end_time = -1;
    map->maxx = map->maxy = 0;
    updlode_walls(map);
    map->bullets = NULL;
    bool **ocupied = calloc((int)map->maxx ,sizeof(bool*));
    for(int i = 0 ; i<map->maxx ; i++){
        ocupied[i] = calloc((int)map->maxy ,sizeof(bool));
    }
    for(int i = 0 ; i<map->maxx ; i++)
        for(int j = 0 ; j<map->maxy  ; j++)
            ocupied[i][j] = false;
    srand(time(NULL));
    for(int i = 0 ; i<map->players ; i++){
        map->tanks[i] = init_tank(map, i, &ocupied);
//        printf("Score of tank %d: %d\n", i+1, map->tanks[i]->score);
    }
//    window = SDL_CreateWindow("Alter Tank", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED,map->maxx*map->ratio + 325, 1000, SDL_WINDOW_OPENGL);
//    *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void dfs(Cell ***cells, int x, int y, int n, int m) {
    int xway[4] = { -1 ,  0 , +1 ,  0 };
    int yway[4] = {  0 , +1 ,  0 , -1 };
    (*cells)[x][y].checked = true;
    int way;
    bool flag = false;
    for (int i = 0; i < 4; i++) {
        if ((*cells)[x][y].access[i] == -1 && !(*cells)[x + xway[i]][y + yway[i]].checked)
            flag = true;
        if ((*cells)[x][y].access[i] == -1 && (*cells)[x + xway[i]][y + yway[i]].checked )
            (*cells)[x][y].access[i] = (*cells)[x + xway[i]][y + yway[i]].access[(i + 2) % 4] = 0;
    }
    if (!flag){
        if (!isempty())
            dfs(cells, peek() / m, pop() % m, n, m);
        return;
    }
    do{
        way = rand()%4;
    }while((*cells)[x][y].access[way] != -1 || (*cells)[x+xway[way]][y+yway[way]].checked);
    (*cells)[x+xway[way]][y+yway[way]].access[(way+2)%4] = (*cells)[x][y].access[way] = 1;
    push(x*m + y);
    dfs(cells, x+xway[way], y+yway[way], n, m);
}

void generate_walls(Cell ***cells, int a, int b) {
    int n = a, m = b;
    for(int i = 0 ; i<n ; i++)
        for(int j = 0 ; j<m ;j++)
        {
            (*cells)[i][j].checked = false;
            for (int k = 0; k < 4; ++k) {
                (*cells)[i][j].access[k] = -1;
            }
            if(i == 0)
                (*cells)[i][j].access[0] = 0;
            if(j == 0)
                (*cells)[i][j].access[3] = 0;
            if(i == n-1)
                (*cells)[i][j].access[2] = 0;
            if(j == m-1)
                (*cells)[i][j].access[1] = 0;

        }
    dfs( cells, rand()%n, rand()%m, n , m);
}

void updlode_walls(Map *map) {
    srand(time(NULL));
    int n  = 3+(rand()%8), m  = 3+(rand()%8);
    Cell **cells = calloc(n, sizeof(Cell*));
    for(int i = 0 ; i<n ; i++)
        cells[i] = calloc(m , sizeof(Cell));
    generate_walls(&cells, n, m);
    write_to_file(cells, n, m);
    FILE *file = fopen("/home/amin/Desktop/project/src/map.txt", "r");
    char buff[5] ;
    for(int i = 0 ; i<5 ; i++)
        buff[i] = '\0';
    fscanf(file, "%s", buff);
    map->count_of_walls = to_int(buff);
    map->walls = malloc(map->count_of_walls* sizeof(Wall*));
    for(int i = 0 ; i<map->count_of_walls ; i++)
        map->walls[i] = malloc(sizeof(Wall));
    for(int i = 0 ; i<map->count_of_walls ; i++){
        for(int j = 0 ; j<4 ;j++){
            for(int k = 0 ; k<5 ; k++)
                buff[k] = '\0';
            fscanf(file, "%s", buff);
            map->walls[i]->pos[j] = to_int(buff);
            if(j & 1)
                map->maxy = max(map->maxy, map->walls[i]->pos[j]);
            else
                map->maxx = max(map->maxx, map->walls[i]->pos[j]);

        }
        if(map->walls[i]->pos[0] == map->walls[i]->pos[2])
            map->walls[i]->dir = VERTICAL;
        else
            map->walls[i]->dir = HORIZONTAL;
    }
    int max_of_max = max(map->maxx, map->maxy);
    double ratio = 960.0 / max_of_max;
    for(int i = 0 ; i<map->count_of_walls ; i++)
        for(int j = 0 ; j<4 ; j++){
            map->walls[i]->pos[j] *= ratio;
            map->walls[i]->pos[j] += 20;
            if(j&1)
                map->walls[i]->pos[j] += (1000-ratio*(map->maxy))/2 - 20;
            else
                map->walls[i]->pos[j] += (1000-ratio*(map->maxx))/2 - 20;
        }
    fclose(file);
    map->ratio = ratio;
}



