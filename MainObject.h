#ifndef MAINOBJECT_H
#define MAINOBJECT_H
#pragma once

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define PLAYER_SPEED 10

class MainObject : public BaseObject
{
     public:
        MainObject();
        ~MainObject();

        enum WalkType{
            WALK_DOWN = 0,
            WALK_RIGHT = 1,
            WALK_UP = 2,
            WALK_LEFT = 3,
        };
        void set_x_val(const float& xVal) {x_val = xVal;}
        void set_y_val(const float& yVal) {y_val = yVal;}
        void set_x_pos(const float& xp) {x_pos = xp;}
        void set_y_pos(const float& yp) {y_pos = yp;}

        int get_x_pos() {return x_pos;};
        int get_y_pos() {return y_pos;};

        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event event, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[2], bool isSound);

        void DoPlayer(Map& map_data, bool isSound);
        void CheckToMap(Map& map_data, bool isSound);
        void SetMapXY(const int map_x, const int map_y)
        {this->map_x = map_x; this->map_y = map_y;}
        void CenterEntityOnMap(Map& map_data);
        //void UpdateImagePlayer(SDL_Renderer* des);

        void set_bullet_list(std::vector<BulletObject*> bullet_list)
        {
            p_bullet_list_ = bullet_list;
        }
        std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
        void HandleBullet(SDL_Renderer* des, Map& map_data);
        bool get_is_alive() {
            if(hp <= 0) isAlive = false;
            return isAlive;

        }
        void hp_change(int val, bool isSound) {
            hp += val;
            if(isSound){
                Mix_PlayChannel(-1, hpChange, 0);
            }
        }
        int get_hp() {return hp;}
        void set_is_alive(bool x) {isAlive = x;}
        int getType_bullet() {return type_bullet;}

    private:
        Mix_Chunk* hpChange = Mix_LoadWAV("soneSound/hp--.WAV");
        Mix_Chunk* change = Mix_LoadWAV("soneSound/changeStatus.WAV");
        Mix_Chunk* bonus = Mix_LoadWAV("soneSound/eatBoom.WAV");

        std::vector<BulletObject*> p_bullet_list_;
        int numOfBullet;
        int type_bullet;

        float x_val;
        float y_val;

        float x_pos;
        float y_pos;

        Input input_type;
        int status;
        bool isAlive;

        float hp;

        int map_x;
        int map_y;

        bool boom;
        BaseObject flame_;
        BaseObject shade_;
        BaseObject aim;
        int flame_id;
};

#endif // MAINOBJECT_H

