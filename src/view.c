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
#include <zconf.h>
#include "view.h"
#include "structs.h"
#include "physics.h"
#include "logic.h"
#include "init.h"

#define black 0,0 ,0, 255


//Uint32 getpixel(SDL_Surface *surface, int x, int y)
//{
//    int bpp = surface->format->BytesPerPixel;
//    /* Here p is the address to the pixel we want to retrieve */
//    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
//
//    switch(bpp) {
//        case 1:
//            return *p;
//            break;
//
//        case 2:
//            return *(Uint16 *)p;
//            break;
//
//        case 3:
//            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
//                return p[0] << 16 | p[1] << 8 | p[2];
//            else
//                return p[0] | p[1] << 8 | p[2] << 16;
//            break;
//
//        case 4:
//            return *(Uint32 *)p;
//            break;
//
//        default:
//            return 0;       /* shouldn't happen, but avoids warnings */
//    }
//}


#define red 255, 0, 0 , 255

void show_tank(Tank *t, SDL_Renderer *renderer) {
    double a = t->angle, x = t->x, y = t->y;
    thickLineColor(renderer, x + t->lenght/2 * cos(a), y - t->lenght/2 * sin(a), x - t->lenght/2 * cos(a), y + t->lenght/2 * sin(a), t->width, t->light_color);                                                                         //shasi
    thickLineColor(renderer, x, y, x + t->barrel_lenght * cos(a), y - t->barrel_lenght * sin(a), t->barrel_thickness, t->dark_color);                                                                                                                 //barrel
    thickLineColor(renderer, x+t->lenght/2*cos(a)+0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) + 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) + 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) + 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 1
    thickLineColor(renderer, x+t->lenght/2*cos(a)-0.4*t->width*sin(a) , y - t->lenght/2 * sin(a) - 0.4*t->width * cos(a), x - t->lenght/2 * cos(a) - 0.4*t->width * sin(a), y + t->lenght/2 * sin(a) - 0.4*t->width * cos(a), 0.25*t->width, t->dark_color);      //sheni 2
    filledCircleColor(renderer, x, y, 0.4*t->width, t->dark_color);                                                                                                                                                                 //circle
    circleRGBA(renderer, x, y, 0.4*t->width, black);                                                                                                                                                                     //circle border

}

int to_int(char buff[5]) {
    int res = 0;
    char* it = buff;
    while(*it != '\0'){
        res = 10*res + *it - '0';
        it++;
    }
    return res;
}

void show_walls(Map *map, struct SDL_Renderer * renderer){
    SDL_Rect rect ;
    rect.x = 1.*(960-map->ratio*map->maxx)/2 + 20;
    rect.y = 1.*(960-map->ratio*map->maxy)/2 + 20;
    rect.h = map->ratio*map->maxy;
    rect.w = map->ratio*map->maxx;
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderFillRect(renderer,&rect);
    for(int i = 0 ; i<map->count_of_walls ; i++)
        thickLineRGBA(renderer, map->walls[i]->pos[0], map->walls[i]->pos[1], map->walls[i]->pos[2], map->walls[i]->pos[3], 0.03*map->ratio, black);
}

void write_to_file(Cell **cells, int n, int m) {
    FILE *map_prim = fopen("/home/amin/Desktop/project/src/map_prim.txt", "w");
    int counter = 2;
    for (int i = 0; i < m; ++i) {
        int j = 0 ;
        while(j<n){
            while(j<n && cells[j][i].access[3])
                j++;
            int tmp = j;
            while(j<n && !cells[j][i].access[3])
                j++;
            counter++;
            if(tmp!=j)
                fprintf(map_prim, "%d %d %d %d\n", i, tmp, i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < m) {
            while (j < m && cells[i][j].access[0])
                j++;
            int tmp = j;
            while (j < m && !cells[i][j].access[0])
                j++;
            counter++;
            if(tmp!=j)
                fprintf(map_prim, "%d %d %d %d\n", tmp, i, j, i);
        }
    }
    fprintf(map_prim, "%d 0 %d %d\n",  m,m,n );
    fprintf(map_prim, "0 %d %d %d\n",  n,m,n );

    char ch;
    FILE *map = fopen("/home/amin/Desktop/project/src/map.txt", "w");
    fprintf(map, "%d\n", counter);
    fclose(map_prim);
    map_prim = fopen("/home/amin/Desktop/project/src/map_prim.txt", "r");
    while( ( ch = fgetc(map_prim) ) != EOF )
        fputc(ch, map);
    remove("/home/amin/Desktop/project/src/map_prim.txt");
    fclose(map);
    fclose(map_prim);
}

void show_bullet(Map *map, SDL_Renderer *renderer) {
    Bullet_Node *b_node = map->bullets;
    srand(time(NULL));
    while(b_node != NULL){
        if(b_node->b.life_time == 0){
            b_node = b_node->next;
            /// TODO cut the linked list
            continue;
        }
        switch (meet_wall(map, b_node->b)){
            case 1:
                b_node->b.angle *= -1;
                break;
            case 2:
                b_node->b.angle = M_PI - b_node->b.angle;
                break;
            default:
                break;
        }
        filledCircleRGBA(renderer, (Sint16) b_node->b.x, (Sint16) b_node->b.y, (Sint16) b_node->b.radius, black);
        b_node->b.life_time--;
        b_node->b.x += 1.2 *cos(b_node->b.angle);
        b_node->b.y += 1.2 *sin(b_node->b.angle);
        if(meet_tank(map, b_node->b)){
            b_node->b.life_time = 0;
            ///todo terminate this bullet
        }
        b_node = b_node->next;
    }
}

void show_scores(Map *map, SDL_Renderer *renderer) {
    SDL_Rect rect;
    rect.x = 1000;
    rect.y = 0;
    rect.h = 1040;
    rect.w = 2000;
    SDL_SetRenderDrawColor(renderer, 89, 190, 255, 255);
    SDL_RenderFillRect(renderer,&rect);
    double x = 1120, y = 160;
    for(int i = 0 ; i<map->players ; i++){
        Tank* tmp_tank = malloc(sizeof(Tank));
        tmp_tank->bullet = map->tanks[i]->bullet;
        tmp_tank->lenght = 150;
        tmp_tank->width = 125;
        tmp_tank->barrel_lenght = 100;
        tmp_tank->barrel_thickness = 25;
        switch(i){
            case 0:
                tmp_tank->light_color =  255 | (95 << 8) | (66 << 16) | (255 << 24);
                tmp_tank->dark_color = 255 | (255 << 24);
                break;
            case 1:
                tmp_tank->light_color =  66 | (134 << 8) | (244<< 16) | (255 << 24);
                tmp_tank->dark_color = 0 | (80 << 8) | (255<< 16) | (255 << 24);
                break;
            case 2:
                tmp_tank->light_color =  243 | (112 << 8) | (255 << 16) | (255 << 24);
                tmp_tank->dark_color = 187 | (0 << 8) | (255 << 16) | (255 << 24);
                break;
            case 3:
                tmp_tank->light_color =  155 | (255 << 8) | (106 << 16) | (255 << 24);
                tmp_tank->dark_color = 0 | (255 << 8) | (38<< 16) | (255 << 24);
                break;
        }
        tmp_tank->x = x;
        tmp_tank->y = y;
        tmp_tank->angle = M_PI/2;
        show_tank(tmp_tank, renderer);
        char s[20] ;
        sprintf(s,"%d",map->tanks[i]->score);
        char ss[30] = "Score: ";
        strcat(ss, s);
        if(map->tanks[i]->is_alive)
            stringRGBA(renderer, x+80, y-15, ss ,black);
        else
            stringRGBA(renderer, x+80, y-15, ss ,red);
        char sss[30] = "Bullets: ";
        sprintf(s,"%d",map->tanks[i]->bullet);
        strcat(sss, s);
        if(map->tanks[i]->is_alive)
            stringRGBA(renderer, x+80, y+10, sss ,black);
        else
            stringRGBA(renderer, x+80, y+10, sss ,red);
        y += 50+tmp_tank->lenght/2 + tmp_tank->barrel_lenght;
    }

    x = 1118, y = 158;
    stringRGBA(renderer, x-3, y-20, "/\\", black);
    stringRGBA(renderer, x-24,y, "<- / ->", black);
    stringRGBA(renderer, x-3, y+20, "\\/", black);

    if(map->players>1){
        y += 225;
        stringRGBA(renderer, x, y-20, "W", black);
        stringRGBA(renderer, x-16,y, "A Q D", black);
        stringRGBA(renderer, x, y+20, "S", black);
    }

    if(map->players>2){
        y += 225;
        stringRGBA(renderer, x, y-20, "T", black);
        stringRGBA(renderer, x-16,y, "F R H", black);
        stringRGBA(renderer, x, y+20, "G", black);
    }

    if(map->players>3){
        y += 225;
        stringRGBA(renderer, x, y-20, "I", black);
        stringRGBA(renderer, x-16,y, "J U L", black);
        stringRGBA(renderer, x, y+20, "K", black);
    }
}