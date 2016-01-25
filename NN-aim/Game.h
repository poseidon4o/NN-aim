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
const float fovLen = 8.f;

//max speed
//offset = speed * dir
const float playerSpeed = 2.f;
const float bulletSpeed = 4.f;
const float rotStep = 0.05f;

//start pos
const Vector2 leftStPos(100.f, 240.f);
const Vector2 rightStPos(540.f, 240.f);
const Vector2 leftStDir(1.f, 0.f);
const Vector2 rightStDir(-1.f, 0.f);

struct Bullet
{
	Bullet() : active(false) {}
	Vector2 pos;
	Vector2 dir;
	bool active;
};


class Game
{
public:
	Game();
	~Game();
	bool init(SDLWrapper * sdl);

	void draw();
	void move();
	void reset();
	void getScore(int& left, int& right);

	//players are 0 and 1
	void move(int player);
	void turnLeft(int player);
	void turnRight(int player);
	void changeFov(int player, float mult);
	void shoot(int player);

	bool playerInFov(int player);
	bool bulletInFov(int player);
	float currentFov(int player);
	bool canShoot(int player);

	Player * m_players[2];
private:
	SDLWrapper * m_sdl;
	SDL_Rect m_plAreas[2];
	//at any moment every player can shoot only 1 bullet
	Bullet m_bullets[2];
	int m_score[2];
	SDL_Texture * m_texBullet;

	void checkForHit();
	void remInactiveBullets();
	bool checkForColision(const Vector2& lPos, const Vector2& rPos, const float lRad, const float rRad);
};