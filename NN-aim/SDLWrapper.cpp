#include <SDL.h>
#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(const int width, const int height) : m_width(width), m_height(height), m_quit(false),
	m_window(NULL), m_render(NULL)
{
}

SDLWrapper::~SDLWrapper()
{
	for (auto it : m_textures)
		SDL_DestroyTexture(it);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_render);
	SDL_Quit();
}

bool SDLWrapper::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	m_window = SDL_CreateWindow("NN-aim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		SDL_Quit();
		return false;
	}

	m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_render)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	return true;
}

bool SDLWrapper::quit()
{
	return m_quit;
}

void SDLWrapper::checkForEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}
}

void SDLWrapper::drawLine(const Vector2& from, const Vector2& to, const char red, const char green, const char blue)
{
	SDL_SetRenderDrawColor(m_render, red, green, blue, 0);
	SDL_RenderDrawLine(m_render, from.getIntX(), from.getIntY(), to.getIntX(), to.getIntY());
}

SDL_Texture * SDLWrapper::createTex(SDL_Surface * surf)
{
	SDL_Texture * res = SDL_CreateTextureFromSurface(m_render, surf);
	SDL_SetTextureBlendMode(res, SDL_BLENDMODE_ADD);
	if (res)
	{
		SDL_FreeSurface(surf);
		m_textures.push_back(res);
	}
	return res;
}

int SDLWrapper::drawTex(SDL_Texture * tex, const Vector2& center)
{
	SDL_Rect rect;
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	rect.x = center.getIntX() - rect.w/2;
	rect.y = center.getIntY() - rect.h/2;
	return SDL_RenderCopy(m_render, tex, NULL, &rect);
}
