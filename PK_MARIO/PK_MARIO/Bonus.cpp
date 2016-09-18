#include "StdAfx.h"
#include "Bonus.h"



TYPES::BonusType Bonus::getBonusType()
{
	return bonusType;
}

TYPES::FieldType Bonus::GetType()
{
	return TYPES::Bonuses;
}

Collisions Bonus::GetBasicAabb()
{
	if (bonusType == TYPES::levelEnd)
	{
		return Collisions(0, 0, 1.2, 1.2);
	}
	else
	{
		return Collisions(0, 0, .4, .4);
	}
}

void Bonus::SetDefaultMovement()
{
	SetXVelocity(1);
	SetYVelocity(1);
}

double Bonus::GetNextXPosition(double dt)
{
	double x = m_x + changeDirectionX*GetNextXVelocity(dt) * dt;
	return x;
}

double Bonus::GetNextYPosition(double dt)
{
	double y = m_y + changeDirectionY*GetNextYVelocity(dt) * dt;
	return y;
}

void Bonus::CheckCollisionsWithLevel(double dt, Level * p_level)
{

	// Collision from up and down
	if (IsAnyFieldBelowMe(m_x, m_y, dt, p_level) || IsAnyFieldAboveMe(m_x, m_y, dt, p_level)) {
		SetIsDead(true);
	}
	// Collision from left and right
	if (IsAnyFieldOnLeft(m_x, m_y, dt, p_level) || IsAnyFieldOnRight(m_x, m_y, dt, p_level)) {
		SetIsDead(true);
	}
}

void Bonus::SetSprite()
{
	m_right = SetTypeForSprite(TYPES::Bonuses, TYPES::hp);
	m_left = SetTypeForSprite(TYPES::Bonuses, TYPES::levelEnd);
}

Bonus::~Bonus()
{
}

void Bonus::Update(double dt, Level * p_level)
{
	timer += dt;
	if(timer>0.5){
	changeDirectionX *= -1;
	changeDirectionY *= -1;
	timer = 0;
	}
	m_right->Update(dt);
	SetPosition(GetX(), GetNextYPosition(dt));
}

void Bonus::Draw()
{
	double tile_height = SpriteRenderer::GetTileHeight();
	double tile_width = SpriteRenderer::GetTileWidth();

	double tile_w ;
	double tile_h ;

	if (isExist()) {

		switch (getBonusType()) 
		{
		case TYPES::hp:
			 
			m_right->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_height, tile_width);
			break;
		case TYPES::levelEnd:
			
			m_left->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_height*2, tile_width*2);
			break;
		}

	}

}
