#include "GhostNest.h"

GhostNest::GhostNest()
{
    x_val = 0;
    y_val = 0;
    x_pos = 620;
    y_pos = 600;
    hp = 10;
    mood = 0;
    deadMood = 0;
    isAlive = true;
    isAngry = false;
}

GhostNest::~GhostNest()
{
    //dtor
}

void GhostNest::Show(SDL_Renderer* des)
{
    BaseObject::Free();
    ui.Free();
    if(isAlive){
        SDL_Rect ret;
        if(isAngry){
            BaseObject::LoadImg("soneFort/Totem_red.png", des);
            rect_.x = x_pos - map_x;
            rect_.y = y_pos - map_y;
            ret = {mood * (rect_.w / 8), 0, rect_.w / 8, rect_.h};
            rect_.w /= 8;
            rect_.w *= 1.5;
            rect_.h *= 1.5;

            mood++;
            mood = mood % 8;

            ui.LoadImg("sonePlayer/soneUI.png", des);
            SDL_Rect retUI = {(hp - 1) * (ui.GetRect().w / 10), 0, ui.GetRect().w / 10, ui.GetRect().h};
            ui.SetRectSize(ui.GetRect().w / 10, ui.GetRect().h);
            ui.SetRect(rect_.x + 20, rect_.y + rect_.h * 0.8);
            ui.Render(des, &retUI);

        }
        else{
            BaseObject::Free();
            BaseObject::LoadImg("soneFort/Totem_red_kill.png", des);
            rect_.x = x_pos - map_x;
            rect_.y = y_pos - map_y - 40;
            ret = {mood * (rect_.w / 14), 0, rect_.w / 14, rect_.h};
            rect_.w /= 14;
            rect_.w *= 1.5;
            rect_.h *= 1.5;
            mood++;
            mood %= 14;
        }
        BaseObject::Render(des, &ret);
    }
    else if(deadMood < 14){
        BaseObject::Free();
        BaseObject::LoadImg("soneFort/Totem_red_die.png", des);
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        SDL_Rect ret = {deadMood * (rect_.w / 14), 0, rect_.w / 14, rect_.h};
        rect_.w /= 14;
        rect_.w *= 1.5;
        BaseObject::Render(des, &ret);
        deadMood++;
    }
}

void GhostNest::CheckToBullet(MainObject& p, Mix_Chunk* exp_sound, bool isSound)
{
    std::vector<BulletObject*> bullet = p.get_bullet_list();
    SDL_Rect mainRect = rect_;
    mainRect.x = mainRect.x + 30;
    mainRect.y = mainRect.y + 60;
    mainRect.w /= 2;
    mainRect.h /= 3;
    SDL_Rect subRect = p.GetRect();
    if(isAlive && checkCollision(mainRect, subRect)){
        p.hp_change(-11, isSound);
        hp--;
        Mix_PlayChannel(-1, exp_sound, 0);
    }
    for(int i = 0; i < bullet.size(); i++){
        SDL_Rect tmpRect = bullet[i]->GetRect();
        /*if(isAlive && bullet[i]->get_type() == 1 && checkCollision(mainRect, tmpRect)){
            //bullet[i]->set_is_move(false);
            //bullet.erase(bullet.begin() + i);
            //p.set_bullet_list(bullet);
        }*/
        if(isAlive && (bullet[i]->get_type() == 2 && bullet[i]->get_mood() == BULLET_2_STOP + 1) && checkCollision(mainRect, tmpRect)){
            hp--;
            //bullet[i]->set_is_move(false);
            //bullet.erase(bullet.begin() + i);
            isAngry = true;
            p.set_bullet_list(bullet);
            Mix_PlayChannel(-1, exp_sound, 0);
        }
        if(hp <= 0) isAlive = false;
    }
}


