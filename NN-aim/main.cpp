#include <iostream>
#include "SDL.h"


int main(int argc, char * argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * m_window = SDL_CreateWindow("initialtest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

	SDL_Delay(5000);
	return 0;
}