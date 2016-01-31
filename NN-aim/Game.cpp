#include "Game.h"

Game::Game()
{
	m_score[0] = m_score[1] = m_frameCnt = m_bulletsCnt[0] = m_bulletsCnt[1] = 0;
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
	m_plAreas[0].x = 0;
	m_plAreas[1].x = width - playerFieldWidth;
	m_plAreas[0].y = m_plAreas[1].y = 0;
	m_plAreas[0].h = m_plAreas[1].h = height;
	m_plAreas[0].w = m_plAreas[1].w = playerFieldWidth;

	//init textures
	SDL_Surface * tmpSur;
	tmpSur = drawCircle(playerRad, 0, 0xff, 0);
	SDL_Texture * texPlayer1 = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(playerRad, 0xff, 0, 0);
	SDL_Texture * texPlayer2 = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(playerEyeRad, 0xff, 0xff, 0xff);
	SDL_Texture * texEye = m_sdl->createTex(tmpSur);

	tmpSur = drawCircle(bulletRad, 0, 0xff, 0xff);
	m_texBullet = m_sdl->createTex(tmpSur);

	//init players
	m_players[0] = new Player(texPlayer1, texEye, leftStPos, leftStDir, fovLen);
	m_players[1] = new Player(texPlayer2, texEye, rightStPos, rightStDir, fovLen);

	return true;
}

bool Game::end()
{
	//TODO: uncomment
	return m_frameCnt > maxGameFrames/* || m_score[0] >= 3 || m_score[1] >= 3*/;
}

void Game::getNNRaitng(float& left, float& right)
{
	left = 1000.f + m_score[0] * 50.f - m_score[1] * 25.f - m_bulletsCnt[0];
	right = 1000.f + m_score[1] * 50.f - m_score[0] * 25.f - m_bulletsCnt[1];
	if (m_score[0] > m_score[1])
	{
		left += 300.f;
		right += -100.f;
	}
	else if (m_score[0] == m_score[1])
	{
		left += 50.f;
		right += 50.f;
	}
	else
	{
		left += -100.f;
		right += 300.f;
	}
}

void Game::reset()
{
	for (int i = 0; i < 2; ++i)
		m_bullets[i].active = false;
	for (int i = 0; i < 2; ++i)
		m_players[i]->m_crnMargin = 0.1f;
	m_players[0]->m_pos = leftStPos;
	m_players[1]->m_pos = rightStPos;
	m_players[0]->m_dir = leftStDir;
	m_players[1]->m_dir = rightStDir;

	for (int i = 0; i < 2; ++i)
		m_score[i] = 0;
	for (int i = 0; i < 2; ++i)
		m_bulletsCnt[i] = 0;

	m_frameCnt = 0;
}

void Game::drawScore()
{
	for (int i = 0; i < m_score[0]; ++i)
	{
		const Vector2 pos(i * bulletRad * 2 + bulletRad, bulletRad);
		m_sdl->drawTex(m_texBullet, pos);
	}
	for (int i = 0; i < m_score[1]; ++i)
	{
		const Vector2 pos(width - i * bulletRad * 2 - bulletRad, bulletRad);
		m_sdl->drawTex(m_texBullet, pos);
	}
}

void Game::move()
{
	//this hack fix player fov and rotation
	for (int i = 0; i < 2; ++i)
		m_players[i]->move(0.f, m_plAreas[i]);

	//move all bulets too
	for (int i = 0; i < 2; ++i)
	{
		if (m_bullets[i].active)
		{
			m_bullets[i].pos += m_bullets[i].dir * bulletSpeed;
		}
	}
	remInactiveBullets();
	checkForHit();
	m_frameCnt++;
}

void Game::draw()
{
	m_sdl->clear();
	for (int i = 0; i < 2; ++i)
		m_players[i]->draw(m_sdl);
	for (int i = 0; i < 2; ++i)
	{
		if (m_bullets[i].active)
			m_sdl->drawTex(m_texBullet, m_bullets[i].pos);
	}
	m_sdl->drawLine(Vector2(playerFieldWidth, 0.f), Vector2(playerFieldWidth, height), 0xff, 0xff, 0xff);
	m_sdl->drawLine(Vector2(playerFieldWidth + bufferZoneSize, 0.f), Vector2(playerFieldWidth + bufferZoneSize, height), 0xff, 0xff, 0xff);

	drawScore();
	m_sdl->update();
}

//players setters
void Game::makeMove(const int player, const Move& mv)
{
	if(mv.advanceStraight)
		move(player);
	if (mv.shoot)
		shoot(player);
	if (mv.turnLeft)
		turnLeft(player);
	if (mv.turnRight)
		turnRight(player);
	changeFov(player, mv.fovMult);

}

void Game::move(int player)
{
	m_players[player]->move(playerSpeed, m_plAreas[player]);
}

void Game::turnLeft(int player)
{
	const float x = m_players[player]->m_dir.x;
	const float y = m_players[player]->m_dir.y;
	m_players[player]->m_dir.x = x * cos(rotStep) - y * sin(rotStep);
	m_players[player]->m_dir.y = x * sin(rotStep) + y * cos(rotStep);
}

void Game::turnRight(int player)
{
	const float x = m_players[player]->m_dir.x;
	const float y = m_players[player]->m_dir.y;
	m_players[player]->m_dir.x = x * cos(-rotStep) - y * sin(-rotStep);
	m_players[player]->m_dir.y = x * sin(-rotStep) + y * cos(-rotStep);
}

void Game::changeFov(int player, float mult)
{
	//TODO: enable fov change
	//m_players[player]->m_crnMargin *= mult;
}

void Game::shoot(int player)
{
	if (canShoot(player))
	{
		m_bullets[player].pos = m_players[player]->m_pos;
		m_bullets[player].dir = m_players[player]->m_dir;
		m_bullets[player].active = true;
		m_bulletsCnt[player]++;
	}
}

//players read input
bool Game::playerInFov(int player)
{
	return m_players[player]->isInFov(m_players[(player + 1) %2]->m_pos, playerRad);
}

bool Game::bulletInFov(int player)
{
	return m_players[player]->isInFov(m_bullets[(player + 1) % 2].pos, bulletRad);
}

float Game::currentFov(int player)
{
	return m_players[player]->m_crnMargin;
}

bool Game::canShoot(int player)
{
	return !m_bullets[player].active;
}


//private methods
void Game::checkForHit()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_bullets[i].active)
		{
			if (checkForColision(m_bullets[i].pos, m_players[(i + 1) % 2]->m_pos, bulletRad, playerRad))
			{
				m_score[i]++;
				m_bullets[i].active = false;
			}
		}
	}
}

void Game::remInactiveBullets()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_bullets[i].active)
			if (m_bullets[i].pos.x > width || m_bullets[i].pos.x < 0
				|| m_bullets[i].pos.y > height || m_bullets[i].pos.y < 0)
				m_bullets[i].active = false;
	}
}

bool Game::checkForColision(const Vector2& lPos, const Vector2& rPos, const float lRad, const float rRad)
{
	const float xDif = lPos.x - rPos.x;
	const float yDif = lPos.y - rPos.y;
	const float sumRad = lRad + rRad;
	return xDif * xDif + yDif * yDif <= sumRad * sumRad;
}
