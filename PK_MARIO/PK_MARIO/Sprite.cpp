#include "StdAfx.h"
#include "Sprite.h"
SpriteRenderer * Sprite::m_renderer;
void Sprite::SetCurrentFrame(size_t frame_num)
{
	m_current_frame = frame_num;
	m_current_frame_duration = 0.0;

}

void Sprite::setRenderer()
{

}

void Sprite::Update(double dt)
{
	m_current_frame_duration += dt;

	if (m_current_frame_duration >= m_data.frame_duration_time)
	{
		m_current_frame++;
		m_current_frame_duration -= m_data.frame_duration_time;
	}
	if (m_current_frame >= m_data.frame_count)
	{
		if (m_data.loop)
		{
			m_current_frame = 0;
		}
		else
		{
			m_current_frame = m_data.frame_count - 1;
		}
	}
}

void Sprite::DrawCurrentFrame(double x, double y, double width, double height)
{

	m_renderer->DrawSprite(
		m_data.left + m_data.width * m_current_frame, m_data.bottom,
		m_data.width, m_data.height, x, y, width, height, m_data.layer);
}

