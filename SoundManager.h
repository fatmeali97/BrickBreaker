#pragma once
#include "Game.h"
#include <string>
#include <map>


class SoundManager
{
public:
	bool LoadMusicAndSound(const char* fileName, std::string id, int type);

	void PlaySound(std::string id, int loop, int ms = 0);
	void PlayMusic(std::string id, int loop, int ms = 0); 
	void ChangeVolume(std::string id);

	static SoundManager* Instance()
	{
		if (s_mInstance == 0)
		{
			s_mInstance = new SoundManager();
			return s_mInstance;
		}
		return s_mInstance;
	}
private:
	static SoundManager* s_mInstance;
	std::map<std::string, Mix_Chunk*> s_mSound; 
	std::map<std::string, Mix_Music*> s_mMusic;

	SoundManager();
	~SoundManager();
};

