#include <SDL.h>
#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(const int width, const int height) : m_width(width), m_height(height), m_quit(false),
	m_window(NULL), m_render(NULL)
{
}

SDLWrapper::~SDLWrapper()
{
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

	m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void SDLWrapper::drawLine(Vector2& from, Vector2& to, const char red, const char green, const char blue)
{
	SDL_SetRenderDrawColor(m_render, red, green, blue, 0);
	SDL_RenderDrawLine(m_render, from.getIntX(), from.getIntY(), to.getIntX(), to.getIntY());
}

