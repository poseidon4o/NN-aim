#include <iostream>
#include "Game.h"


int main(int argc, char * argv[])
{
	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}

	Game game;
	game.init(&sdl);

	game.m_players[0]->move(1.f, SDL_Rect{ 0,0,640,480 });
	game.m_players[1]->move(1.f, SDL_Rect{ 0,0,640,480 });

	while (!sdl.quit())
	{
		sdl.checkForEvent();
		game.draw();

		SDL_Delay(5);
	}
	return 0;
}
