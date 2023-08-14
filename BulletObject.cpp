#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val = y_val = 0;
    x_pos = y_pos = 0;
    is_move_ = false;
    type = 1;
    mood = 0;
    angle = 0;
    dis = 0;
    max_dis = 320;
}

bool BulletObject::LoadBullet(SDL_Renderer* screen)
{
    BaseObject::Free();
    std::stringstream ss;
    ss << "sonePlayer/shot" << type << "_" << mood << ".png";
    return LoadImg(ss.str(), screen);
}

void BulletObject::HandleMove(const int& x_border, const int& y_border, Map& map_data)
{
    if(type == 1){
        if(mood < BULLET_LIFE_1) mood++;
        if(dis > max_dis){
        is_move_ = false;
        return;
        }
    }
    else if(type == 2){
        if(mood == BULLET_2_STOP){
            if(dis >= max_dis){
                x_val = y_val = 0;
                mood++;
            }
        }
        else if(mood < BULLET_LIFE_2) mood++;
        else if(mood == BULLET_LIFE_2){
            is_move_ = false;
            return;
        }
    }
    dis += (abs(x_val) + abs(y_val));
    if(type == 1){
        /* (y1, x1) ******** (y2, x1)
        *                   *
        *                   *
       (y1, x2) ******** (y2, x2) */
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;
        //check horizontal
        if(bullet_dir_ == DIR_LEFT || bullet_dir_ == DIR_RIGHT){
            int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;
            //o thu bao nhieu
            x1 = (x_pos + x_val + 1) / TILE_SIZE;
            x2 = (x_pos + x_val + rect_.w - 1) / TILE_SIZE;

            y1 = (y_pos) / TILE_SIZE;
            y2 = (y_pos + height_min) / TILE_SIZE;

            if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
                if(x_val > 0)   //main object dang di chuyen ve ben phai
                {
                    int val1 = map_data.tile[y1][x2];
                    int val2 = map_data.tile[y2][x2];

                    if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                        is_move_ = false;
                    }
                }
                else if(x_val < 0)   //main object dang di chuyen ve ben trai
                {
                    int val1 = map_data.tile[y1][x1];
                    int val2 = map_data.tile[y2][x1];

                    if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                        is_move_ = false;
                    }
                }
            }
        }
        else if(bullet_dir_ == DIR_DOWN || bullet_dir_ == DIR_UP){
            //check vertical
            int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;
            x1 = (x_pos) / TILE_SIZE;
            x2 = (x_pos + width_min) / TILE_SIZE;

            y1 = (y_pos + y_val + 1) / TILE_SIZE;
            y2 = (y_pos + y_val + rect_.h - 1) / TILE_SIZE;

            if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
                if(y_val > 0)   //main object dang di chuyen xuong duoi
                {
                    int val1 = map_data.tile[y2][x1];
                    int val2 = map_data.tile[y2][x2];

                    if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                        is_move_ = false;
                    }
                }
                else if(y_val < 0)   //main object dang di chuyen len tren
                {
                    int val1 = map_data.tile[y1][x1];
                    int val2 = map_data.tile[y1][x2];

                    if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                        is_move_ = false;
                    }
                }
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    rect_.x += x_val;
    rect_.y += y_val;

    if(rect_.y > y_border) is_move_ = false;
    else if(rect_.y < 0) is_move_ = false;
    if(rect_.x > x_border) is_move_ = false;
    else if(rect_.x < 0) is_move_ = false;
}

void BulletObject::Show(SDL_Renderer* des, int x, int y)
{
    std::stringstream ss;
    BaseObject::Free();
    shade.Free();
    if(is_move_){
        if(type == 2 && 3 < mood && mood <= BULLET_2_STOP){
            shade.LoadImg("sonePlayer/shade.png", des);
            shade.SetRect(rect_.x + 20, rect_.y + 20);
            shade.SetRectSize(30, 30);
            shade.Render(des, NULL);
        }
        ss << "sonePlayer/shot" << type << "_" << mood << ".png";
        LoadImg(ss.str(), des);
    }
    else if(type == 1){
        ss << "sonePlayer/Explosion_1" << ".png";
        LoadImg(ss.str(), des);
    }
    rect_.x = x_pos - x;
    rect_.y = y_pos - y;
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopyEx(des, p_object_, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}

BulletObject::~BulletObject()
{

}
