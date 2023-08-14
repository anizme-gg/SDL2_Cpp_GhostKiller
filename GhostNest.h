#ifndef GHOSTNEST_H
#define GHOSTNEST_H

#define NEST_CLIPS 10

#include "BaseObject.h"
#include "MainObject.h"
#include "CommonFunc.h"

class GhostNest : public BaseObject
{
    public:
        GhostNest();
        ~GhostNest();

        void set_x_pos(const float& xp) {x_pos = xp;}
        void set_y_pos(const float& yp) {y_pos = yp;}

        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}

        void SetMapXY(const int& mp_x, const int& mp_y)
        {map_x = mp_x; map_y = mp_y;}

        void Show(SDL_Renderer* des);
        bool is_alive() const {
            return isAlive;
        }
        void CheckToBullet(MainObject& p, Mix_Chunk* exp_sound, bool isSound);
        int get_deadMood() {return deadMood;}

        bool is_angry() {return isAngry;}
    private:
        int map_x;
        int map_y;

        float x_val;
        float y_val;
        float x_pos;
        float y_pos;

        bool isAlive;

        bool isAngry;
        int deadMood;
        int mood;
        int hp;

        BaseObject ui;
};

#endif // GHOSTNEST_H
