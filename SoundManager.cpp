#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    if (Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096) == -1)
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

SoundManager::~SoundManager()
{
    std::cout << "Destructor of SoundManager is called" << std::endl;
}

bool SoundManager::LoadMusicAndSound(const char* fileName,
    std::string id, int type)
{
    //type 1 => music; 
    //type 0 => sound;

    if (type == 1)
    {
        Mix_Music* music = Mix_LoadMUS(fileName);
        if (music == 0)
        {
            std::cout << "Could not load music "
                << Mix_GetError() << std::endl;
            return false;
        }
        s_mMusic[id] = music;
        return true;
    }
    else
    {
        if (type == 0)
        {
            Mix_Chunk* chunk = Mix_LoadWAV(fileName);
            if (chunk == 0)
            {
                std::cout << "Could not load sfx" << Mix_GetError() << std::endl;
                return false;
            }
            s_mSound[id] = chunk;
            return true;
        }
    }
}

void SoundManager::PlayMusic(std::string id,
    int loop, int ms)
{
    if (Mix_FadeInMusic(s_mMusic[id], loop, ms))
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

void SoundManager::ChangeVolume(std::string id)
{
    Mix_VolumeMusic(15);
}

void SoundManager::PlaySound(std::string id,
    int loop, int ms)
{
    if (Mix_FadeInChannel(-1, s_mSound[id], loop, ms))
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

SoundManager* SoundManager::s_mInstance = 0;
