#pragma once
#include "SDL.h"
#include "Vec2.h"
#include "SDLWrapper.h"

class Player
{
public:
	Player(SDL_Texture * body, SDL_Texture * eye, Vector2 pos, Vector2 dir) :
		m_body(body), m_eye(eye), m_pos(pos), m_dir(dir),
		//TODO: set it proper
		m_crnMargin(1.f)
	{
		int w;
		SDL_QueryTexture(body, NULL, NULL, &w, NULL);
		m_scaleForEye = w/2;
		m_scaleForAim = w * 5;
	}

	void draw(SDLWrapper * sdl);
	void move(float stepSize = 0.5f);

	Vector2 m_pos;
	Vector2 m_dir;
private:
	SDL_Texture * m_body;
	SDL_Texture * m_eye;

	float m_scaleForEye;
	float m_scaleForAim;
	float m_crnMargin;

};