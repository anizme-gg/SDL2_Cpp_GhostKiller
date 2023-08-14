#include "BaseObject.h"
//khoi tao 1 object
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = rect_.y = rect_.w = rect_.h = 0;
}
//load anh cho p_object_
bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    p_object_ = new_texture;

    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopyEx(des, p_object_, clip, &renderquad, angle, center, flip);
}
//giai phong object
void BaseObject::Free()
{
    if(p_object_ != NULL){
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = rect_.h = 0;
    }
}

BaseObject::~BaseObject()
{
    Free();
}
