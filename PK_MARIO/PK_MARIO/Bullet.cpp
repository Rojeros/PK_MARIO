#include "StdAfx.h"
#include "Bullet.h"

TYPES::FieldType Bullet::GetType()
{
	return TYPES::PlayerBullet;
}

Collisions Bullet::GetBasicAabb()
{
	return Collisions(0, 0, .4, .4);
}

void Bullet::SetDefaultMovement()
{
}

void Bullet::Update(double dt, Level * p_level)
{

	m_right->Update(dt);

	
	m_time_to_live -= dt;
	if (m_time_to_live < 0) {
		SetIsDead(true);
		return;
	}

	CheckCollisionsWithLevel(dt, p_level);
	SetPosition(GetNextXPosition(dt), GetNextYPosition(dt));
}

void Bullet::CheckCollisionsWithLevel(double dt, Level * p_level)
{

	
	if (IsAnyFieldBelowMe(m_x, m_y, dt, p_level) || IsAnyFieldAboveMe(m_x, m_y, dt, p_level)) {
		SetIsDead(true);
	}


	if (IsAnyFieldOnLeft(m_x, m_y, dt, p_level) || IsAnyFieldOnRight(m_x, m_y, dt, p_level)) {
		SetIsDead(true);
	}
}

void Bullet::SetSprite()
{
	m_right = SetTypeForSprite(TYPES::PlayerBullet, TYPES::None);
}

void Bullet::Draw()
{

	double height, width;
	height = m_left->m_renderer->GetTileHeight();
	width = m_left->m_renderer->GetTileWidth();

	double pos_x = m_x * height;
	double pos_y = m_y * width;

	m_right->DrawCurrentFrame(pos_x, pos_y, width, height);
}
