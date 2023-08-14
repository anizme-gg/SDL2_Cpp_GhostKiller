#ifndef THREATOBJECT_H
#define THREATOBJECT_H
#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include <sstream>

#define TIME 15
#define GHOST_CLIPS 6
#define GHOST_DIE 8

class ThreatObject : public BaseObject
{
    public:
        ThreatObject();
        ~ThreatObject();

        enum GhostDirection
        {
            DIR_UP = 25,
            DIR_LEFT = 26,
            DIR_DOWN = 27,
            DIR_RIGHT = 28,
        };

        void set_x_val(const float& xVal) {x_val = xVal;}
        void set_y_val(const float& yVal) {y_val = yVal;}

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
        void DoPlayer(Map& gMap, MainObject& p, Mix_Chunk* exp_sound, bool isSound);
        void CheckToMap(Map& gMap);
        void CheckToBullet(MainObject& p, Mix_Chunk* exp_sound, bool isSound);
        int get_mood() const {return mood;}
        int get_deadMood() {return deadMood;}
        void set_mood(int x) {mood = x;}
        void set_hp(const int& x) {hp = x;}

        void set_dir(int x) {ghost_dir = x;};
        int get_timeChangeDir() {return timeChangeDir;}
    private:
        int map_x;
        int map_y;

        float x_val;
        float y_val;
        float x_pos;
        float y_pos;

        int unsigned ghost_dir;
        bool isChange;
        bool isAlive;

        int timeChangeDir;
        int mood;
        int deadMood;
        int hp;



        BaseObject shade_;
};

#endif // THREATOBJECT_H
