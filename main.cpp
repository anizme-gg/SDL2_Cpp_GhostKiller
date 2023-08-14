#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "GameMap.h"
#include "ImpTime.h"
#include "ThreatObject.h"
#include "TextObject.h"
#include "GhostNest.h"
#include <ctime>

SDL_Window* g_window = NULL;
SDL_Renderer* g_screen = NULL;
SDL_Event g_event;
Mix_Chunk* bg;
Mix_Chunk* g_sound_bullet[2];
Mix_Chunk* g_sound_exp[2];

bool isSound = true;

BaseObject g_background;
TTF_Font* font_score = NULL;
int score = 0;

int ShowMenu(SDL_Surface* menu_img, SDL_Renderer* des, TTF_Font* font)
{
    menu_img = IMG_Load("img/bg.png");
    if(menu_img == NULL) return 1;
    const int item_num = 3;
    SDL_Rect pos_arr[item_num];
    pos_arr[0].x = 100;
    pos_arr[0].y = 300;

    pos_arr[1].x = 100;
    pos_arr[1].y = 400;

    pos_arr[2].x = 50;
    pos_arr[2].y = 500;

    TextObject text_menu[item_num];
    text_menu[0].SetText("PLAY");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("TUTORIAL");
    text_menu[2].SetColor(TextObject::WHITE_TEXT);
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    int xm = 0, ym = 0;
    SDL_Event m_event;

    BaseObject sound, mute;
    sound.LoadImg("img/sound.png", g_screen);
    sound.SetRect(580, 10);
    sound.SetRectSize(40, 40);

    mute.LoadImg("img/mute.png", g_screen);
    mute.SetRectSize(40, 40);
    mute.SetRect(580, 10);

    SDL_Texture* menu_tt = SDL_CreateTextureFromSurface(des, menu_img);

    while(true)
    {
        SDL_RenderCopy(des, menu_tt, NULL, NULL);

        for(int i = 0; i < item_num; i++){
            text_menu[i].Free();
            text_menu[i].LoadFromRenderText(font, des);
            text_menu[i].RenderText(des);
        }

        if(isSound) sound.Render(des);
        else mute.Render(des);

        while(SDL_PollEvent(&m_event)){
            switch (m_event.type){
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for(int i = 0;i < item_num; i++){
                    SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                    SDL_Rect sub = {xm, ym, 0, 0};
                    if(checkCollision(sub, main)){
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                    }
                    else{
                        text_menu[i].SetColor(TextObject::WHITE_TEXT);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = m_event.button.x;
                ym = m_event.button.y;

                for(int i = 0;i < item_num; i++){
                    SDL_Rect sub = {xm, ym, 0, 0};
                    SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                    if(checkCollision(sub, main)){
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                        return i;
                    }
                    else{
                        text_menu[i].SetColor(TextObject::WHITE_TEXT);
                    }
                }
                {
                    SDL_Rect sub = {xm, ym, 0, 0};
                    if(checkCollision(sub, sound.GetRect())){
                        if(isSound){
                            Mix_Pause(-1);
                            isSound = false;
                        }
                        else{
                            Mix_Resume(-1);
                            isSound = true;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE) return 1;
            default:
                break;
            }
        }
        SDL_RenderPresent(des);
    }
    sound.Free();
    mute.Free();
    text_menu[0].Free();
    text_menu[1].Free();
    text_menu[2].Free();
    SDL_FreeSurface(menu_img);
    menu_img = NULL;
    SDL_DestroyTexture(menu_tt);
    menu_tt = NULL;
    return 1;
}

int ShowResult(SDL_Surface* result_img, SDL_Renderer* des, TTF_Font* font, bool e)
{
    Mix_HaltChannel(-1);
    Mix_Chunk* res;
    SDL_RenderClear(des);
    result_img = IMG_Load("img/bg1.png");
    if(result_img == NULL) return 0;

    std::string str_score = "";
    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    if(e){
        str_score += "WINNER!";
        score_game.SetRect(200, 200);
        res = Mix_LoadWAV("soneSound/win.WAV");
    }
    else{
        str_score += "LOSER!!! SCORE: ";
        std::string str_val = std::to_string(score);
        str_score += str_val;
        score_game.SetRect(110, 200);
        res = Mix_LoadWAV("soneSound/loser.WAV");
    }
    Mix_PlayChannel(-1, res, 0);
    score_game.SetText(str_score);

    const int item_num = 2;
    SDL_Rect pos_arr[item_num];
    pos_arr[0].x = 250;
    pos_arr[0].y = 300;

    pos_arr[1].x = 160;
    pos_arr[1].y = 350;

    TextObject text_menu[item_num];
    text_menu[0].SetText("EXIT");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("PLAY AGAIN");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    SDL_Event m_event;
    int xm = 0, ym = 0;

    BaseObject sound;
    sound.LoadImg("img/sound.png", g_screen);
    sound.SetRect(580, 10);
    sound.SetRectSize(40, 40);

    BaseObject mute;
    mute.LoadImg("img/mute.png", g_screen);
    mute.SetRectSize(40, 40);
    mute.SetRect(580, 10);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(des, result_img);
    score_game.LoadFromRenderText(font, des);

    while(true){
        SDL_RenderCopy(des, texture, NULL, NULL);\
        score_game.RenderText(des);

        if(isSound) sound.Render(des);
        else mute.Render(des);

        for(int i = 0; i < item_num; i++){
            text_menu[i].Free();
            text_menu[i].LoadFromRenderText(font, des);
            text_menu[i].RenderText(des);
        }


        while(SDL_PollEvent(&m_event)){
            switch(m_event.type){
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:{
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for(int i = 0;i < item_num; i++){
                    SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                    SDL_Rect sub = {xm, ym, 0, 0};
                    if(checkCollision(sub, main)){
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                    }
                    else{
                        text_menu[i].SetColor(TextObject::WHITE_TEXT);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                xm = m_event.button.x;
                ym = m_event.button.y;

                for(int i = 0; i < item_num; i++){
                    SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                    SDL_Rect sub = {xm, ym, 0, 0};
                    if(checkCollision(sub, main)){
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                        return i;
                    }
                    else{
                        text_menu[i].SetColor(TextObject::WHITE_TEXT);
                    }
                }
                {
                    SDL_Rect sub = {xm, ym, 0, 0};
                    if(checkCollision(sub, sound.GetRect())){
                        if(isSound){
                            Mix_Pause(-1);
                            isSound = false;
                        }
                        else{
                            Mix_Resume(-1);
                            isSound = true;
                        }
                    }
                }
                break;
            }
            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE) return 0;
            default:
                break;
            }
        }
        SDL_RenderPresent(des);
    }
    score_game.Free();
    SDL_FreeSurface(result_img);
    result_img = NULL;
    sound.Free();
    mute.Free();
    text_menu[0].Free();
    text_menu[1].Free();
    Mix_FreeChunk(res);
    score_game.Free();
    return 0;
}

int ShowTutorial(SDL_Surface* tut1_img, SDL_Surface* tut2_img, SDL_Renderer* des, TTF_Font* font)
{
    font = TTF_OpenFont("font/zorque.otf", 30);
    tut1_img = IMG_Load("img/Tut1.png");
    tut2_img = IMG_Load("img/Tut2.png");
    const int item_num = 2;
    SDL_Rect pos_arr[item_num];
    pos_arr[0].x = 20;
    pos_arr[0].y = 600;

    pos_arr[1].x = 540;
    pos_arr[1].y = 600;

    TextObject text_menu[item_num];
    text_menu[0].SetText("MENU");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("NEXT");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    int xm = 0, ym = 0;
    SDL_Event m_event;
    int d = 1;
    BaseObject sound;
    sound.LoadImg("img/sound.png", g_screen);
    sound.SetRect(580, 10);
    sound.SetRectSize(40, 40);

    BaseObject mute;
    mute.LoadImg("img/mute.png", g_screen);
    mute.SetRectSize(40, 40);
    mute.SetRect(580, 10);

    SDL_Texture* menu_tt = SDL_CreateTextureFromSurface(des, tut1_img);
    SDL_Texture* menu_tt2 = SDL_CreateTextureFromSurface(des, tut2_img);
    while(d != 0)
    {

        if(d == 1){
            SDL_RenderCopy(des, menu_tt, NULL, NULL);

            text_menu[0].SetText("MENU");
            text_menu[1].SetText("NEXT");

            if(isSound) sound.Render(des);
            else mute.Render(des);

            for(int i = 0; i < item_num; i++){
                text_menu[i].Free();
                text_menu[i].LoadFromRenderText(font, des);
                text_menu[i].RenderText(des);
            }

            while(SDL_PollEvent(&m_event)){
                switch (m_event.type){
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for(int i = 0;i < item_num; i++){
                        SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, main)){
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                        else{
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for(int i = 0; i < item_num; i++){
                        SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, main)){
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                            if(i == 0) d = 0;
                            else d = 2;
                        }
                        else{
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                    {
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, sound.GetRect())){
                            if(isSound){
                                Mix_Pause(-1);
                                isSound = false;
                            }
                            else{
                                Mix_Resume(-1);
                                isSound = true;
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(m_event.key.keysym.sym == SDLK_ESCAPE) return 1;
                default:
                    break;
                }
            }
            SDL_RenderPresent(des);
        }
        if(d == 2){
            text_menu[0].SetText("BACK");
            text_menu[1].SetText("MENU");

            SDL_RenderCopy(des, menu_tt2, NULL, NULL);

            if(isSound) sound.Render(des);
            else mute.Render(des);
            for(int i = 0; i < item_num; i++){
                text_menu[i].Free();
                text_menu[i].LoadFromRenderText(font, des);
                text_menu[i].RenderText(des);
            }

            while(SDL_PollEvent(&m_event)){
                switch (m_event.type){
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for(int i = 0;i < item_num; i++){
                        SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, main)){
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                        else{
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for(int i = 0;i < item_num; i++){
                        SDL_Rect main = {pos_arr[i].x, pos_arr[i].y, text_menu[i].GetWidth(), text_menu[i].GetHeight()};
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, main)){
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                            if(i == 0) d = 1;
                            else d = 0;
                        }
                        else{
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                    {
                        SDL_Rect sub = {xm, ym, 0, 0};
                        if(checkCollision(sub, sound.GetRect())){
                            if(isSound){
                                Mix_Pause(-1);
                                isSound = false;
                            }
                            else{
                                Mix_Resume(-1);
                                isSound = true;
                            }
                        }
                    }

                    break;
                case SDL_KEYDOWN:
                    if(m_event.key.keysym.sym == SDLK_ESCAPE) return 1;
                default:
                    break;
                }
            }
            SDL_RenderPresent(des);
        }
    }
    if(d == 0) return 3;
    return 1;
}

bool Init()
{
    bool sc = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return false;
    }
    //Set a hint with normal priority
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //Create window
    g_window = SDL_CreateWindow("SONE", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL) sc = false;
    else{
        //Create renderer for window
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) sc = false;
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            //Declare SDL_Image
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)) sc = false;
        }

        if(TTF_Init() == -1){
            sc = false;
        }
        else{
            font_score = TTF_OpenFont("font/zorque.otf", 20);
            if(font_score == NULL){
                sc = false;
            }
            if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) sc = false;
            else{
                g_sound_bullet[0] = Mix_LoadWAV("soneSound/shootR2.WAV");
                g_sound_bullet[1] = Mix_LoadWAV("soneSound/shootE1.WAV");
                g_sound_exp[0] = Mix_LoadWAV("soneSound/hitGhost.WAV");
                g_sound_exp[1] = Mix_LoadWAV("soneSound/hitTotem.WAV");
                if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL || g_sound_exp[1] == NULL)
                    sc = false;

            }
        }

    }
    return sc;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/bg1.png", g_screen);
    return ret;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen); g_screen = NULL;
    SDL_DestroyWindow(g_window); g_window = NULL;
    Mix_FreeChunk(g_sound_bullet[0]);
    Mix_FreeChunk(g_sound_bullet[1]);
    Mix_FreeChunk(g_sound_exp[0]);
    Mix_FreeChunk(g_sound_exp[1]);
    g_sound_bullet[0] = g_sound_bullet[1] = NULL;
    g_sound_exp[0] = g_sound_exp[1] = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}

int main(int argc, char* argv[])
{
    srand(time(0));
    ImpTime fps_timer;
    if(!Init()) return -1;
    if(!LoadBackground()) return -1;

    bool isWin = false;
    bool canBeWin = true;
    bool is_quit = false;

    int delay = 30;
    isSound = true;

    TTF_Font* menu_font = TTF_OpenFont("font/zorque.otf", 50);
    while(!is_quit)
    {
        Mix_FreeChunk(bg);
        bg = Mix_LoadWAV("soneSound/background.WAV");
        Mix_PlayChannel(-1, bg, INT_MAX);
        SDL_RenderClear(g_screen);
        SDL_Surface* menu = NULL;
        int ret = ShowMenu(menu, g_screen, menu_font);
        SDL_Surface* tut1 = NULL;
        SDL_Surface* tut2 = NULL;
        while(ret != 1 && ret != 0){
            SDL_RenderClear(g_screen);
            if(ret == 2) ret = ShowTutorial(tut1, tut2, g_screen, menu_font);
            if(ret == 3) ret = ShowMenu(menu, g_screen, menu_font);
        }
        if(ret == 1){
            is_quit = true;
            canBeWin = false;
            break;
        }
        SDL_FreeSurface(menu);
        SDL_FreeSurface(tut1);
        SDL_FreeSurface(tut2);
        menu = NULL; tut1 = NULL; tut2 = NULL;

        GameMap game_map;
        game_map.LoadMap("soneMap/sonemap.txt");
        game_map.LoadTiles(g_screen);

        BaseObject ui;
        ui.LoadImg("sonePlayer/soneUI.png", g_screen);
        int w = ui.GetRect().w / 10;
        ui.SetRectSize(w * 2, ui.GetRect().h);
        ui.SetRect(20, 0);

        BaseObject sound;
        sound.LoadImg("img/sound.png", g_screen);
        sound.SetRect(580, 10);
        sound.SetRectSize(40, 40);

        BaseObject mute;
        mute.LoadImg("img/mute.png", g_screen);
        mute.SetRectSize(40, 40);
        mute.SetRect(580, 10);

        TextObject score_game;
        score_game.SetColor(TextObject::RED_TEXT);
        score_game.SetRect(29, 45);

        BaseObject skill;

        MainObject player;
        std::vector<ThreatObject*> ghosts;
        int createGhost1 = 0;
        int createGhost2 = 0;
        int numGhost = 0;
        int time1 = 70;
        int time2 = 70;
        GhostNest nest1, nest2;
        nest2.set_x_pos(1900);

        Map map_data = game_map.getMap();

        Mix_Chunk* start = Mix_LoadWAV("soneSound/start.WAV");
        Mix_PlayChannel(-1, start, 0);
        while((!isWin && canBeWin) || delay > 0){
            createGhost1++;
            createGhost2++;

            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT){
                    isWin = true;
                    is_quit = true;
                }
                player.HandleInputAction(g_event, g_screen, map_data, g_sound_bullet, isSound);
                if(g_event.type == SDL_MOUSEBUTTONDOWN){
                    int x = g_event.button.x;
                    int y = g_event.button.y;
                    SDL_Rect mouse = {x, y, 0, 0};
                    if(checkCollision(mouse, sound.GetRect())){
                        if(isSound){
                            Mix_Pause(-1);
                            isSound = false;
                        }
                        else{
                            Mix_Resume(-1);
                            isSound = true;
                        }
                    }
                }
            }
            //SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            if(!player.get_is_alive()){
                canBeWin = false;
                isWin = false;
                delay = 0;
            }
            player.SetMapXY(map_data.start_x, map_data.start_y);
            player.DoPlayer(map_data, isSound);

            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);
            //std::cout << numGhost << std::endl;
            if(nest1.is_alive() || nest1.get_deadMood() < 14){
                nest1.SetMapXY(map_data.start_x, map_data.start_y);
                nest1.CheckToBullet(player, g_sound_exp[1], isSound);
                nest1.Show(g_screen);
                if(nest1.is_angry()) time1 = 20;

                if(createGhost1 % time1 == 0 && numGhost < 50){
                ThreatObject* ghost = new ThreatObject();
                numGhost++;
                ghosts.push_back(ghost);
                ghost->set_x_pos(nest1.get_x_pos());
                ghost->set_y_pos(nest1.get_y_pos());
                ghost->LoadImg("soneGhost/Ghost_fly.png", g_screen);
                ghost = NULL;
                }
            }
            else{
                nest1.Free();
                map_data.tile[9][9] = map_data.tile[9][10] = map_data.tile[9][11] = 0;
                map_data.tile[10][9] = map_data.tile[10][10] = map_data.tile[10][11] = 0;
                map_data.tile[11][9] = map_data.tile[11][10] = map_data.tile[11][11] = 0;

            }
            if(nest2.is_alive() || nest2.get_deadMood() < 14){
                nest2.SetMapXY(map_data.start_x, map_data.start_y);
                nest2.CheckToBullet(player, g_sound_exp[1], isSound);
                nest2.Show(g_screen);
                if(nest2.is_angry()) time2 = 20;

                if(createGhost2 % time2 == 0 && numGhost < 50){
                ThreatObject* ghost = new ThreatObject();
                numGhost++;
                ghosts.push_back(ghost);
                ghost->set_x_pos(nest2.get_x_pos());
                ghost->set_y_pos(nest2.get_y_pos());
                ghost->LoadImg("soneGhost/Ghost_fly.png", g_screen);
                ghost = NULL;
                }
            }
            else{
                nest2.Free();
                map_data.tile[9][29] = map_data.tile[9][30] = map_data.tile[9][31] = 0;
                map_data.tile[10][29] = map_data.tile[10][30] = map_data.tile[10][31] = 0;
                map_data.tile[11][29] = map_data.tile[11][30] = map_data.tile[11][31] = 0;
            }
            player.HandleBullet(g_screen, map_data);

            if(!nest1.is_alive() && !nest2.is_alive()) isWin = true;
            int n = ghosts.size();

            for(int i = 0; i < n; i++){
                    int x = player.get_x_pos();
                    int y = player.get_y_pos();
                    if(!ghosts[i]->is_alive() && ghosts[i]->get_deadMood() >= 8){
                        score += 1;
                        ghosts[i]->Free();
                        ghosts.erase(ghosts.begin() + i);
                        numGhost--;
                        continue;
                    }
                    ghosts[i]->SetMapXY(map_data.start_x, map_data.start_y);
                    int x1 = ghosts[i]->get_x_pos();
                    int y1 = ghosts[i]->get_y_pos();
                    int key = ghosts[i]->get_timeChangeDir();
                    if(abs(x - x1) < 30 && key > 1){
                        if(y > y1) ghosts[i]->set_dir(27);
                        else ghosts[i]->set_dir(25);
                    }
                    if(abs(y - y1) < 30 && key > 1){
                        if(x > x1) ghosts[i]->set_dir(28);
                        else ghosts[i]->set_dir(26);
                    }
                    ghosts[i]->DoPlayer(map_data, player, g_sound_exp[0], isSound);
                    ghosts[i]->Show(g_screen);
            }


            SDL_Rect hp = {w * (player.get_hp() - 1), 0, w,ui.GetRect().h};
            ui.Render(g_screen, &hp);

            //Show game score
            std::string str_score = "SCORE: ";
            std::string str_val = std::to_string(score);
            str_score += str_val;

            score_game.Free();
            score_game.SetText(str_score);
            score_game.LoadFromRenderText(font_score, g_screen);
            score_game.RenderText(g_screen);

            if(isSound) sound.Render(g_screen);
            else mute.Render(g_screen);

            skill.Free();
            if(player.getType_bullet() == 2){
                skill.LoadImg("sonePlayer/Skill_Boom1.png", g_screen);
            }
            else{
                skill.LoadImg("sonePlayer/Skill_Shot1.png", g_screen);
            }
            skill.SetRect(150, 30);
            skill.Render(g_screen, NULL);

            player.Show(g_screen);

            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000 / FRAME_PER_SECOND;
            if(real_imp_time < time_one_frame){
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >= 0) SDL_Delay(delay_time);
            }
            if(isWin) delay--;
        }
        Mix_FreeChunk(start);
        SDL_RenderClear(g_screen);
        if(!is_quit){
            ui.Free();
            skill.Free();
            player.Free();
            int n = ghosts.size();
            for(int i = 0; i < n; i++) ghosts[i]->Free();
            nest1.Free(); nest2.Free();
            SDL_Surface* finalSur = NULL;
            if(ShowResult(finalSur, g_screen, menu_font, isWin) != 1) is_quit = true;
            else{
                is_quit = false;
                isWin = false;
                canBeWin = true;
                score = 0;
                delay = 30;
            }
            SDL_FreeSurface(finalSur);
            finalSur = NULL;

            score_game.Free();
            sound.Free();
            mute.Free();
        }
    }

    close();
    return 0;
}
