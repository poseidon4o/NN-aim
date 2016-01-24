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
		m_crnMargin(0.5f)
	{
		int w;
		SDL_QueryTexture(body, NULL, NULL, &w, NULL);
		m_size = w / 2;
		m_fovScale *= w;
	}

	void draw(SDLWrapper * sdl);
	void move(float speed, const SDL_Rect& area);
	bool isInFov(const Vector2& pos, float radius);

	Vector2 m_pos;
	Vector2 m_dir;
private:
	SDL_Texture * m_body;
	SDL_Texture * m_eye;

	int m_size;
	float m_fovScale;
	float m_crnMargin;

	Vector2 m_leftAim;
	Vector2 m_rightAim;
};