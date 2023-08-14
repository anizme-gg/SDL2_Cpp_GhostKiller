#include "MainObject.h"

MainObject::MainObject()
{
    x_pos = 0; y_pos = 420;
    x_val = y_val = 0;
    status = 1;
    input_type.left = input_type.right = 0;
    input_type.down = input_type.up = 0;
    map_x = map_y = 0;

    boom = false;
    numOfBullet = 1;
    type_bullet = 1;
    hp = 10;
    isAlive = true;
    flame_id = 0;
}

void MainObject::Show(SDL_Renderer* des)
{
    BaseObject::Free();
    flame_.Free();
    aim.Free();
    shade_.Free();
    if(type_bullet == 2){
        aim.LoadImg("sonePlayer/Boom_aim.png", des);
    }
    if(status == WALK_LEFT){
        LoadImg("sonePlayer/SpaceShipL.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
        shade_.LoadImg("sonePlayer/shade.png", des);
        shade_.SetRect(rect_.x + 20, rect_.y + 20);
        shade_.Render(des, NULL, -90);

        SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
        flame_id++;
        if(flame_id % 2 == 0){
            flame_.LoadImg("sonePlayer/Flame_01.png", des);
            flame_.SetRect(rect_.x + rect_.w, rect_.y + rect_.h / 2 - flame_.GetRect().h / 2);
            flame_.Render(des, NULL, -90);
        }
        else{
            flame_.LoadImg("sonePlayer/Flame_02.png", des);
            flame_.SetRect(rect_.x + rect_.w, rect_.y + rect_.h / 2 - flame_.GetRect().h / 2);
            flame_.Render(des, NULL, -90);
        }
        if(type_bullet == 2){
            aim.SetRect(rect_.x - 237, rect_.y);
            aim.Render(des, NULL);
        }
    }
    else if(status == WALK_RIGHT){
        LoadImg("sonePlayer/SpaceShipR.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
        shade_.LoadImg("sonePlayer/shade.png", des);
        shade_.SetRect(rect_.x + 20, rect_.y + 20);
        shade_.Render(des, NULL, 90);

        SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
        flame_id++;
        if(flame_id % 2 == 0){
            flame_.LoadImg("sonePlayer/Flame_01.png", des);
            flame_.SetRect(rect_.x - flame_.GetRect().w, rect_.y + rect_.h / 2 - flame_.GetRect().h / 2);
            flame_.Render(des, NULL, 90);
        }
        else{
            flame_.LoadImg("sonePlayer/Flame_02.png", des);
            flame_.SetRect(rect_.x - flame_.GetRect().w, rect_.y + rect_.h / 2 - flame_.GetRect().h / 2);
            flame_.Render(des, NULL, 90);
        }
        if(type_bullet == 2){
            aim.SetRect(rect_.x + 237, rect_.y);
            aim.Render(des, NULL);
        }
    }
    else if(status == WALK_UP){
        LoadImg("sonePlayer/SpaceShipU.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

        shade_.LoadImg("sonePlayer/shade.png", des);
        shade_.SetRect(rect_.x + 20, rect_.y + 20);
        shade_.Render(des, NULL);

        SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
        flame_id++;
        if(flame_id % 2 == 0){
            flame_.LoadImg("sonePlayer/Flame_01.png", des);
            flame_.SetRect(rect_.x + rect_.w / 2 - flame_.GetRect().w / 2, rect_.y + rect_.h);
            flame_.Render(des, NULL);
        }
        else{
            flame_.LoadImg("sonePlayer/Flame_02.png", des);
            flame_.SetRect(rect_.x + rect_.w / 2 - flame_.GetRect().w / 2, rect_.y + rect_.h);
            flame_.Render(des, NULL);
        }

        if(type_bullet == 2){
            aim.SetRect(rect_.x, rect_.y - 237);
            aim.Render(des, NULL);
        }
    }
    else{
        LoadImg("sonePlayer/SpaceShipD.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;

        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

        shade_.LoadImg("sonePlayer/shade.png", des);
        shade_.SetRect(rect_.x + 20, rect_.y + 20);
        shade_.Render(des, NULL, 180);

        SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
        flame_id++;
        if(flame_id % 2 == 0){
            flame_.LoadImg("sonePlayer/Flame_01.png", des);
            flame_.SetRect(rect_.x + rect_.w / 2 - flame_.GetRect().w / 2, rect_.y - flame_.GetRect().h);
            flame_.Render(des, NULL, 180);
        }
        else{
            flame_.LoadImg("sonePlayer/Flame_02.png", des);
            flame_.SetRect(rect_.x + rect_.w / 2 - flame_.GetRect().w / 2, rect_.y - flame_.GetRect().h);
            flame_.Render(des, NULL, 180);
        }

        if(type_bullet == 2){
            aim.SetRect(rect_.x, rect_.y + 237);
            aim.Render(des, NULL);
        }
    }
}

void MainObject::HandleInputAction(SDL_Event event, SDL_Renderer* screen, Map& map_data, Mix_Chunk* bullet_sound[2], bool isSound)
{
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT){
            status = WALK_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
        }
        if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT){
            status = WALK_LEFT;
            input_type.left = 1;
            input_type.right = 0;
        }
        if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN){
            status = WALK_DOWN;
            input_type.down = 1;
            input_type.up = 0;
        }
        if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP){
            status = WALK_UP;
            input_type.up = 1;
            input_type.down = 0;
        }
        if(event.key.keysym.sym == SDLK_r){
            type_bullet = 1;
            if(isSound){
                Mix_PlayChannel(-1, change, 0);
            }

        }
        if(event.key.keysym.sym == SDLK_e && boom){
            type_bullet = 2;
            if(isSound){
                Mix_PlayChannel(-1, change, 0);
            }
        }
    }
    else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
        case SDLK_d:
            input_type.right = 0;
            break;
        case SDLK_a:
            input_type.left = 0;
            break;
        case SDLK_s:
            input_type.down = 0;
            break;
        case SDLK_w:
            input_type.up = 0;
            break;
        }
        if(input_type.up) status = WALK_UP;
        if(input_type.down) status = WALK_DOWN;
        if(input_type.right) status = WALK_RIGHT;
        if(input_type.left) status = WALK_LEFT;
    }
    if((event.key.keysym.sym == SDLK_j) && p_bullet_list_.size() < numOfBullet)
    {
        if(isSound){
            if(type_bullet == 1) Mix_PlayChannel(-1, bullet_sound[0], 0);
            else Mix_PlayChannel(-1, bullet_sound[1], 0);
        }

        BulletObject* p_bullet = new BulletObject();
        p_bullet->set_type(type_bullet);
        p_bullet->set_is_move(true);
        p_bullet->LoadBullet(screen);

        if(status == WALK_UP){
            p_bullet->set_bullet_dir(BulletObject::DIR_UP);
            p_bullet->set_y_val(-BUL_SPEED);
            p_bullet->set_x_val(0);
            p_bullet->set_angle(-90);
            p_bullet->SetRect(rect_.x, rect_.y);
            p_bullet->set_pos(x_pos, y_pos);
        }
        else if(status == WALK_RIGHT){
            p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            p_bullet->set_x_val(BUL_SPEED);
            p_bullet->set_y_val(0);
            p_bullet->set_angle(0);
            p_bullet->SetRect(rect_.x, rect_.y);
            p_bullet->set_pos(x_pos, y_pos);
        }
        else if(status == WALK_LEFT){
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->set_x_val(-BUL_SPEED);
            p_bullet->set_y_val(0);
            p_bullet->set_angle(180);
            p_bullet->SetRect(rect_.x, rect_.y);
            p_bullet->set_pos(x_pos, y_pos);
        }
        else{
            p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
            p_bullet->set_y_val(BUL_SPEED);
            p_bullet->set_x_val(0);
            p_bullet->set_angle(90);
            p_bullet->SetRect(rect_.x, rect_.y);
            p_bullet->set_pos(x_pos, y_pos);
        }
        p_bullet_list_.push_back(p_bullet);
    }
}

void MainObject::HandleBullet(SDL_Renderer* des, Map& map_data)
{
    for(int i = 0; i < p_bullet_list_.size(); i++)
    {
        if(p_bullet_list_[i] != NULL)
        {
            p_bullet_list_[i]->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, map_data);
            p_bullet_list_[i]->Show(des, map_x, map_y);
            if(!p_bullet_list_[i]->get_is_move())
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
        }
    }
}

void MainObject::DoPlayer(Map& map_data, bool isSound)
{
    x_val = 0;
    y_val = 0;

    if(input_type.left == 1){
        x_val -= PLAYER_SPEED;
    }
    if(input_type.right == 1){
        x_val += PLAYER_SPEED;
    }
    if(input_type.up == 1){
        y_val -= PLAYER_SPEED;
    }
    if(input_type.down == 1){
        y_val += PLAYER_SPEED;
    }

    //kiem tra va cham
    CheckToMap(map_data, isSound);
    CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
    if(map_data.start_x < 0) map_data.start_x = 0;
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;

    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if(map_data.start_y < 0) map_data.start_y = 0;
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
}

void MainObject::CheckToMap(Map& map_data, bool isSound)
{
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

    bool sound = false;
    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){
        if(x_val > 0)   //main object dang di chuyen ve ben phai
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                x_pos = x2 * TILE_SIZE - (rect_.w + 1);
                x_val = 0;
            }
            if(val1 == BOOM_ITEM){
                boom = true;
                map_data.tile[y1][x2] = 0;
                sound = true;

            }
            else if(val2 == BOOM_ITEM){
                boom = true;
                map_data.tile[y2][x2] = 0;
                sound = true;
            }
        }
        else if(x_val < 0)   //main object dang di chuyen ve ben trai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
            if(val1 == BOOM_ITEM){
                boom = true;
                map_data.tile[y1][x1] = 0;
                sound = true;
            }
            else if(val2 == BOOM_ITEM){
                boom = true;
                map_data.tile[y2][x1] = 0;
                sound = true;
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

            if((val1 >= WALL_VAL&& val1 <= WALL_END) || (val2 >= WALL_VAL && val2 <= WALL_END)){
                y_pos = y2 * TILE_SIZE - (rect_.h + 1);
                y_val = 0;
            }
            if(val1 == BOOM_ITEM){
                boom = true;
                map_data.tile[y2][x1] = 0;
                sound = true;
            }
            else if(val2 == BOOM_ITEM){
                boom = true;
                map_data.tile[y2][x2] = 0;
                sound = true;
            }
        }
        else if(y_val < 0)   //main object dang di chuyen len tren
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if((val1 >= WALL_VAL && val1 <= WALL_END) || (val2 >= WALL_VAL&& val2 <= WALL_END)){
                y_pos = (y1 + 1) * TILE_SIZE;
                y_val = 0;
            }
            if(val1 == BOOM_ITEM){
                boom = true;
                map_data.tile[y1][x1] = 0;
                sound = true;
            }
            else if(val2 == BOOM_ITEM){
                boom = true;
                map_data.tile[y1][x2] = 0;
                sound = true;
            }
        }
    }
    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0) x_pos = 0;
    else if(x_pos + rect_.w > map_data.max_x) x_pos = map_data.max_x - rect_.w;
    if(y_pos < 0) y_pos = 0;
    else if(y_pos + rect_.h > map_data.max_y) y_pos = map_data.max_y - rect_.h;

    if(sound && isSound){
        Mix_PlayChannel(-1, bonus, 0);
        sound = false;
    }
}

MainObject::~MainObject()
{
    Mix_FreeChunk(hpChange);
    Mix_FreeChunk(change);
}
