#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{
	for (int i = 0; i < 2; ++i)
		delete m_players[i];
}

bool Game::init(SDLWrapper * sdl)
{
	m_sdl = sdl;

	//init rectangles
	m_plAreas[0].x = m_plAreas[1].x = 0;
	m_plAreas[0].y = 0;
	m_plAreas[1].y = width - playerFieldWidth;
	m_plAreas[0].h = m_plAreas[1].h = height;
	m_plAreas[0].x = m_plAreas[1].w = playerFieldWidth;

	//init textures
	SDL_Surface * tmpSur;
	tmpSur = drawCircle(playerRad, 0, 0xff, 0);
	SDL_Texture * texPlayer1 = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(playerRad, 0xff, 0, 0);
	SDL_Texture * texPlayer2 = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(playerEyeRad, 0xff, 0xff, 0xff);
	SDL_Texture * texEye = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(playerRad, 0, 0xff, 0xff);
	m_texBullet = m_sdl->createTex(tmpSur);

	//init players
	m_players[0] = new Player(texPlayer1, texEye, leftStPos, leftStDir, fovLen);
	m_players[1] = new Player(texPlayer2, texEye, rightStPos, rightStDir, fovLen);

	return true;
}

void Game::draw()
{
	m_sdl->clear();
	for (int i = 0; i < 2; ++i)
		m_players[i]->draw(m_sdl);

	m_sdl->drawLine(Vector2(playerFieldWidth, 0.f), Vector2(playerFieldWidth, height), 0xff, 0xff, 0xff);
	m_sdl->drawLine(Vector2(playerFieldWidth + bufferZoneSize, 0.f), Vector2(playerFieldWidth + bufferZoneSize, height), 0xff, 0xff, 0xff);

	m_sdl->update();

}
