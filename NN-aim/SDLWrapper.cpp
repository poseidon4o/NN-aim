#include <SDL.h>
#include "SDLWrapper.h"

SDLWrapper::SDLWrapper(const int width, const int height) : m_width(width), m_height(height), m_quit(false),
	m_window(NULL), m_surface(NULL)
{
}

SDLWrapper::~SDLWrapper()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool SDLWrapper::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	m_window = SDL_CreateWindow("Graphics HW1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_OPENGL);
	if (!m_window)
		return false;
	m_surface = SDL_GetWindowSurface(m_window);

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

void SDLWrapper::setPixelColor(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
{
	if (x >= m_width || y >= m_height)
		return;
	Uint32 * pixels = static_cast<Uint32*>(m_surface->pixels);
	pixels[x + m_width * y] = SDL_MapRGB(m_surface->format, red, green, blue);
}

void SDLWrapper::setPixelsColor(const int x, const int y, const int size, const unsigned char red, const unsigned char green, const unsigned char blue)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			setPixelColor(x + i, y + j, red, green, blue);
		}
	}

}
