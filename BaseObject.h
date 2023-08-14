#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "CommonFunc.h"
//object nao cung co nhung tinh nang nay
//thanh vien: 1 texture, o vuong boc (de xu ly va cham)
//tinh nang: load anh cho texture, gan o vuong, render tai vi tri xdinh
class BaseObject
{
    public:
        BaseObject();
        ~BaseObject();
        void SetRect(int x, int y){rect_.x = x; rect_.y = y;}
        void SetRectSize(int w, int h){rect_.w = w; rect_.h = h;}
        SDL_Rect GetRect() {return rect_;}
        SDL_Texture* GetObject() const {return p_object_;}

        //load image from file cho p_object_
        bool LoadImg(std::string path, SDL_Renderer* screen);
        //render p_object_ at position clip
        void Render(SDL_Renderer* des, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //Delocate
        void Free();
    protected:
        SDL_Texture* p_object_;
        SDL_Rect rect_;
};

#endif // BASEOBJECT_H
