#include "Player.h"

void Player::draw(SDLWrapper * sdl)
{
	Vector2 aim = m_pos + m_dir * m_fovScale;
	Vector2 offset = (m_pos - aim).perp();

	//find perpendiculiar
	offset *= m_crnMargin;

	sdl->drawLine(m_pos, offset + aim, 0, 0xff, 0xff);
	offset *= -1;
	sdl->drawLine(m_pos, offset + aim, 0, 0xff, 0xff);

	sdl->drawTex(m_body, m_pos);
	sdl->drawTex(m_eye, m_pos + m_dir * m_scaleForEye);
}

void Player::move(float stepSize)
{
	m_pos += (m_dir * stepSize);

	//TODO:calc in the proper way
	m_crnMargin /= 1.005;
}
