#include "CommonFunc.h"

int CommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = BaseObject::LoadImg("img/soneMenu1.png");
    if(g_img_menu)
}

SDL_Surface* CommonFunc::LoadImage(std::string path)
{
    SDL_Surface* loaded_image = NULL;
    SDL_Surface* optimize_image = NULL;
    loaded_image = IMG_Load(path.c_str());
    if(loaded_image != NULL){
        optimize_image = SDL_
    }
}

bool CommonFunc::checkCollision( SDL_Rect a, SDL_Rect b )
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
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
