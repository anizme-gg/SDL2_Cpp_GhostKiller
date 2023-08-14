#pragma once

#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
/*
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];*/
//Screen
const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 180;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 255;


#define TILE_SIZE 64
#define MAX_MAP_X 40
#define MAX_MAP_Y 25
#define WALL_VAL 20
#define WALL_END 41
#define BUL_SPEED 30
#define BOOM_ITEM 10

struct Map
{
    //toa do
    int start_x;
    int start_y;
    //gia tri toi da cua ban do
    int max_x;
    int max_y;
    //tile[i][j]: dang map ma o (i, j) se hien thi
    int tile[MAX_MAP_Y][MAX_MAP_X];
    //file chua ban raw map (00 01 ...)
    std::string file_name;
};

struct Input{
    int down;
    int right;
    int up;
    int left;
    //int shoot;
};

static bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;
    //If none of the sides from A are outside B
    return true;
}



#endif // COMONFUNC_H
