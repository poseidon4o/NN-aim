#include "Player.h"

#include "utils.h"

void Player::draw(SDLWrapper * sdl)
{
	sdl->drawLine(m_pos, m_leftAim, 0, 0xff, 0xff);
	sdl->drawLine(m_pos, m_rightAim, 0, 0xff, 0xff);

	sdl->drawTex(m_body, m_pos);
	sdl->drawTex(m_eye, m_pos + m_dir * m_scaleForEye);
}

void Player::move(float stepSize)
{
	m_pos += (m_dir * stepSize);

	Vector2 aim = m_pos + m_dir * m_fovScale;
	Vector2 offset = (m_pos - aim).perp();
	offset *= m_crnMargin;
	m_leftAim = aim + offset;
	m_rightAim = aim - offset;

	//TODO:calc in the proper way
	m_crnMargin /= 1.005;
}

bool Player::isInFov(const Vector2& pos, float radius)
{
	Vector2 tri[3] = {m_pos, m_leftAim, m_rightAim};
	bool res = intersectCircleTriangle(pos,radius, tri);
	if (res)
		m_dir *= -1;
	return res;
}

