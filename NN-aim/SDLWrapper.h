#pragma once
#include <SDL.h>
#include "Vec2.h"
#include <vector>

class SDLWrapper
{
public:
	SDLWrapper(const int width, const int height);
	~SDLWrapper();
	bool initSDL();

	inline int getWidth() const
	{
		return m_width;
	}
	inline int getHeight() const
	{
		return m_height;
	}

	bool quit();
	void checkForEvent();

	void update() { SDL_RenderPresent(m_render); }
	void clear() { SDL_SetRenderDrawColor(m_render, 0, 0, 0, 0); SDL_RenderClear(m_render); }

	void drawLine(Vector2& from, Vector2& to, const char red, const char green, const char blue);

	SDL_Texture * createTex(SDL_Surface * surf);
	int drawTex(SDL_Texture * tex, Vector2& topLeft);

private:
	SDL_Window * m_window;
	SDL_Renderer * m_render;
	const int m_width;
	const int m_height;
	std::vector<SDL_Texture *> m_textures;

	//event vars
	bool m_quit;
};