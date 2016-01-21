#pragma once
#include "SDL.h"
#include "Vec2.h"
#include "SDLWrapper.h"

class Player
{
public:
	Player(SDL_Texture * body, SDL_Texture * eye, Vector2 pos, Vector2 dir, float fovScale) :
		m_body(body), m_eye(eye), m_pos(pos), m_dir(dir), m_fovScale(fovScale),
		//TODO: set it proper
		m_crnMargin(1.f)
	{
		int w;
		SDL_QueryTexture(body, NULL, NULL, &w, NULL);
		m_scaleForEye = w / 2;
		m_fovScale *= w;
	}

	void draw(SDLWrapper * sdl);
	void move(float stepSize = 0.5f);
	//bool isInFov(const Vector2& pos, float radius);

	Vector2 m_pos;
	Vector2 m_dir;
private:
	SDL_Texture * m_body;
	SDL_Texture * m_eye;

	float m_scaleForEye;
	float m_fovScale;
	float m_crnMargin;

};