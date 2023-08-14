#include "ImpTime.h"

ImpTime::ImpTime()
{
    start_tick = 0;
    paused_tick = 0;
    is_paused_ = false;
    is_started_ = false;

}

ImpTime::~ImpTime()
{
    //dtor
}

void ImpTime::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks();
}

void ImpTime::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void ImpTime::paused()
{
    if(is_started_ && !is_paused_)
    {
        is_paused_ = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}


void ImpTime::unpaused()
{
    if(is_paused_)
    {
        is_paused_ = false;
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int ImpTime::get_ticks()
{
    if(is_started_)
    {
        if(is_paused_) return paused_tick;
        else return SDL_GetTicks() - start_tick;
    }
}

bool ImpTime::is_started()
{
    return is_started_;
}

bool ImpTime::is_paused()
{
    return is_paused_;
}

