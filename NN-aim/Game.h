#pragma once
#include "Player.h"
#include "SDLWrapper.h"
#include "utils.h"

//some game constants
const int width = 640;
const int height = 480;
const int bufferZoneSize = 100;
const int playerFieldWidth = (width - bufferZoneSize) / 2;


//size in pixels
const float playerRad = 25.f;
const float playerEyeRad = 5.f;
const float bulletRad = 5.f;
const float fovLen = 5.f;

//max speed
//offset = speed * dir
const float playerSpeed = 2.f;
const float bulletSpeed = 4.f;

//start pos
const Vector2 leftStPos(100.f, 240.f);
const Vector2 rightStPos(540.f, 240.f);
const Vector2 leftStDir(1.f, 0.f);
const Vector2 rightStDir(-1.f, 0.f);


class Game
{
public:
	Game();
	~Game();
	bool init(SDLWrapper * sdl);

	void draw();

	Player * m_players[2];
private:
	SDLWrapper * m_sdl;
	SDL_Rect m_plAreas[2];
	std::vector<std::pair<Vector2, Vector2>> m_bullets;
	SDL_Texture * m_texBullet;
};