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

Bullet* init_bullet(Tank *t, double ratio) {
    Bullet* b = malloc(sizeof(Bullet));
    b->x = t->x + t->barrel_lenght*cos(t->angle);
    b->y = t->y - t->barrel_lenght*sin(t->angle);
    b->angle = -t->angle;
    b->radius = 0.03*ratio;
    b->life_time = 5000;
    return b;
}

void init_tank(Map *map, int k, bool *** ocupied) {
    Tank *t = map->tanks[k];

    for(int j = 0 ; j<5 ;j++)
        t->keys[j] = malloc(100*sizeof(char));
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

            t->keys[0] = "/\\";
            t->keys[1] = "<-";
            t->keys[2] = "/";
            t->keys[3] = "->";
            t->keys[4] = "\\/";
            break;
        case 1:
            if(map->ai_mode){
                t->light_color =  100 | (100 << 8) | (100<< 16) | (255 << 24);
                t->dark_color = 50 | (50 << 8) | (50<< 16) | (255 << 24);
            } else{
                t->light_color =  66 | (134 << 8) | (244<< 16) | (255 << 24);
                t->dark_color = 0 | (80 << 8) | (255<< 16) | (255 << 24);
                t->keys[0] = "W";
                t->keys[1] = "A";
                t->keys[2] = "Q";
                t->keys[3] = "D";
                t->keys[4] = "S";
            }
            break;
        case 2:
            t->light_color =  243 | (112 << 8) | (255 << 16) | (255 << 24);
            t->dark_color = 187 | (0 << 8) | (255 << 16) | (255 << 24);
            t->keys[0] = "T";
            t->keys[1] = "F";
            t->keys[2] = "R";
            t->keys[3] = "H";
            t->keys[4] = "G";
            break;
        case 3:
            t->light_color =  155 | (255 << 8) | (106 << 16) | (255 << 24);
            t->dark_color = 0 | (255 << 8) | (38<< 16) | (255 << 24);
            t->keys[0] = "I";
            t->keys[1] = "J";
            t->keys[2] = "U";
            t->keys[3] = "L";
            t->keys[4] = "K";
            break;
    }
    map->tanks[k] = t;
}

void create_tanks(Map *map) {
    map->tanks = malloc(sizeof(Tank*));
    for(int i = 0 ; i<4 ; i++){
        map->tanks[i] = malloc(sizeof(Tank));
        map->tanks[i]->score = 0;
    }
}

bool start_game(Map *map) {
    if(!map->players)
        return false;
    if(map->players == 1){
        map->players = 2;
        map->ai_mode = true;
    } else
        map->ai_mode = false;
    map->round++;
    map->end_time = -1;
    map->maxx = map->maxy = 0;
    updlode_walls(map);
    map->bullets = NULL;
//    define_tanks(map);
    bool **ocupied = calloc((int)map->maxx ,sizeof(bool*));
    for(int i = 0 ; i<map->maxx ; i++){
        ocupied[i] = calloc((int)map->maxy ,sizeof(bool));
    }
    for(int i = 0 ; i<map->maxx ; i++)
        for(int j = 0 ; j<map->maxy  ; j++)
            ocupied[i][j] = false;
    srand(time(NULL));

    for(int i = 0 ; i<4 ; i++)
        init_tank(map, i, &ocupied);

    return 1;
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
    walls_to_file(cells, n, m);
    FILE *file = fopen("map.txt", "r");
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
                map->walls[i]->pos[j] += (960-ratio*(map->maxy))/2 ;
            else
                map->walls[i]->pos[j] += (960-ratio*(map->maxx))/2 ;
        }
    fclose(file);
    map->ratio = ratio;
}

int load_last_game(Map *map) {
    FILE *f ;
    if(!(f = fopen("lastGame.txt", "r"))){

        printf("\033[0;31m"); //Set the text to the color red
        printf("Last game not saved.\n"); //Display Hello in red
        printf("\033[0m");
        return 0;

    }

    fscanf(f, "%d %d %d\n%d %d %d %d",&map->round, &map->players , &map->ai_mode,
            &map->tanks[0]->score, &map->tanks[1]->score, &map->tanks[2]->score, &map->tanks[3]->score);
    fclose(f);
    return 1;

}



