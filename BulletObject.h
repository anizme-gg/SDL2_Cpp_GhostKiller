#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include <sstream>

#define BULLET_LIFE_1 5
#define BULLET_LIFE_2 15
#define BULLET_2_STOP 7

class BulletObject : public BaseObject
{
    public:
        BulletObject();
        ~BulletObject();

        enum BulletDirection
        {
            DIR_DOWN = 20,
            DIR_RIGHT = 21,
            DIR_UP = 22,
            DIR_LEFT = 23,
        };

        void set_x_val(const int& xVal) {x_val = xVal;}
        void set_y_val(const int& yVal) {y_val = yVal;}
        void set_pos(const int& xPos, const int& yPos) {x_pos = xPos; y_pos = yPos;}

        int get_x_val() const {return x_val;}
        int get_y_val() const {return y_val;}
        int get_x_pos() const {return x_pos;}
        int get_y_pos() const {return y_pos;}

        void set_is_move(const bool& isMove) {
            is_move_ = isMove;
            if(type == 1) max_dis = 320;
            else if(type == 2) max_dis = 232;
        }
        bool get_is_move() const {return is_move_;}

        void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
        int get_bullet_dir() const {return bullet_dir_;}

        void HandleMove(const int& x_border, const int& y_border, Map& map_data);
        void Show(SDL_Renderer* des, int x, int y);

        int get_type() const {return type;}
        void set_angle(double a) {angle = a;}

        bool LoadBullet(SDL_Renderer* des);
        void set_type(int t) {type = t;}

        int get_mood() {return mood;}
    private:
        double angle;
        int x_pos;
        int y_pos;
        int x_val;
        int y_val;
        int type;

        int dis;
        int mood;
        bool is_move_;
        unsigned int bullet_dir_;
        int max_dis;

        BaseObject shade;
};

#endif // BULLETOBJECT_H
