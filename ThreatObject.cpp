#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    x_val = 0;
    y_val = 0;
    x_pos = 1080;
    y_pos = 1080;
    hp = 1;
    ghost_dir = rand() % 2 + 25;
    mood = 0;
    deadMood = 0;
    isChange = false;
    timeChangeDir = 0;
    isAlive = true;
}

ThreatObject::~ThreatObject()
{
    //dtor
}

void ThreatObject::Show(SDL_Renderer* des)
{
    SDL_RendererFlip p = SDL_FLIP_NONE;
    if(ghost_dir == DIR_DOWN || ghost_dir == DIR_RIGHT) p = SDL_FLIP_HORIZONTAL;
    SDL_Rect ret;
    BaseObject::Free();
    shade_.Free();
    if(isAlive){
        BaseObject::LoadImg("soneGhost/Ghost_fly.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        ret = {(96) * mood + 30, 20, 32, 32};
        rect_.w = rect_.h = 60;

        shade_.LoadImg("soneGhost/shade.png", des);
        shade_.SetRect(rect_.x + 30, rect_.y + 40);
        shade_.Render(des, NULL, 90, NULL, p);;

        mood++;
        mood = mood % GHOST_CLIPS;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
        SDL_RenderCopyEx(des, p_object_, &ret , &renderQuad, 0, NULL, p);
    }
    else if(deadMood < GHOST_DIE){
        BaseObject::LoadImg("soneGhost/Ghost_die.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        ret = {(rect_.w / GHOST_DIE) * deadMood, 0, rect_.w / GHOST_DIE, rect_.h};
        rect_.w /= GHOST_DIE;
        deadMood++;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
        SDL_RenderCopyEx(des, p_object_, &ret , &renderQuad, 0, NULL, p);
    }
}

void ThreatObject::DoPlayer(Map& map_data, MainObject& p, Mix_Chunk* exp_sound, bool isSound)
{
    if(ghost_dir == DIR_DOWN){
        x_val = 0;
        y_val = 10;
    }
    else if(ghost_dir == DIR_UP){
        x_val = 0;
        y_val = - 10;
    }
    else if(ghost_dir == DIR_RIGHT){
        x_val = 10;
        y_val = 0;
    }
    else if(ghost_dir == DIR_LEFT){
        x_val = - 10;
        y_val = 0;
    }
    CheckToMap(map_data);
    CheckToBullet(p, exp_sound, isSound);
    isChange = false;
}

void ThreatObject::CheckToMap(Map& map_data)
{
    if(!isAlive) return;
    if(timeChangeDir == TIME){
        timeChangeDir = 0;
        ghost_dir = rand() % 4 + 25;
    }
    /* (y1, x1) ******** (y2, x1)
        *                   *
        *                   *
       (y1, x2) ******** (y2, x2) */
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    //check horizontal
    int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;
    //o thu bao nhieu
    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + rect_.w - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){
        if(x_val > 0)   //main object dang di chuyen ve ben phai
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                x_pos = x2 * TILE_SIZE - (rect_.w + 1);
                x_val = 0;
                isChange = true;
            }
        }
        else if(x_val < 0)   //main object dang di chuyen ve ben trai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
                isChange = true;
            }
        }
    }

    //check vertical
    int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + rect_.h - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){
        if(y_val > 0)   //main object dang di chuyen xuong duoi
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                y_pos = y2 * TILE_SIZE - (rect_.h + 1);
                y_val = 0;
                isChange = true;
            }
        }
        else if(y_val < 0)   //main object dang di chuyen len tren
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                y_pos = (y1 + 1) * TILE_SIZE;
                y_val = 0;
                isChange = true;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0) x_pos = 0;
    else if(x_pos + rect_.w > map_data.max_x) x_pos = map_data.max_x - rect_.w;
    if(y_pos < 0) y_pos = 0;
    else if(y_pos + rect_.h > map_data.max_y) y_pos = map_data.max_y - rect_.h;

    if(isChange){
        timeChangeDir++;
        ghost_dir = rand() % 4 + 25;
        isChange = false;
    }
}

void ThreatObject::CheckToBullet(MainObject& p, Mix_Chunk* exp_sound, bool isSound)
{
    std::vector<BulletObject*> bullet = p.get_bullet_list();
    SDL_Rect mainRect = rect_;
    SDL_Rect subRect = p.GetRect();
    if(isAlive && checkCollision(mainRect, subRect)){
        p.hp_change(-1, isSound);
        isAlive = false;
        if(isSound) Mix_PlayChannel(-1, exp_sound, 0);
    }
    for(int i = 0; i < bullet.size(); i++){
        SDL_Rect tmpRect = bullet[i]->GetRect();
        if(isAlive && bullet[i]->get_type() == 1 && checkCollision(mainRect, tmpRect)){
            hp--;
            if(isSound) Mix_PlayChannel(-1, exp_sound, 0);
            bullet[i]->set_is_move(false);
            bullet.erase(bullet.begin() + i);
            p.set_bullet_list(bullet);
        }
        else if(isAlive && (bullet[i]->get_type() == 2 && bullet[i]->get_mood() == BULLET_2_STOP + 1) && checkCollision(mainRect, tmpRect)){
            hp--;
            bullet[i]->set_is_move(false);
            if(isSound) Mix_PlayChannel(-1, exp_sound, 0);
            bullet.erase(bullet.begin() + i);
            p.set_bullet_list(bullet);
        }
        if(hp <= 0) isAlive = false;
    }
}
