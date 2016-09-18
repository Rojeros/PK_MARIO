#include "StdAfx.h"
#include "Monster.h"

int Monster::GetScoresWhenKilled()
{
	 return 100;
}

Collisions Monster::GetBasicAabb()
{
	return Collisions(0, 0, .9, .9);
}

TYPES::FieldType Monster::GetType()
{
	return TYPES::Enemy;
}

void Monster::SetSprite()
{
	m_right = SetTypeForSprite(TYPES::Enemy, TYPES::GoingRight);
	m_left = SetTypeForSprite(TYPES::Enemy, TYPES::GoingLeft);
	m_stop = SetTypeForSprite(TYPES::Enemy, TYPES::Standing);
}

void Monster::CheckCollisionsWithLevel(double dt, Level * level)
{
	
	if (GetXVelocity() == 0) 
	{
		GoLeft();
	}

	
	if (IsAnyFieldBelowMe(GetX(), GetY(), dt, level)) 
	{
		EntityOnGround();
	}

	
	if (DoFieldsEndOnLeft(GetX(), GetY(), dt, level) || IsAnyFieldOnLeft(GetX(), GetY(), dt, level))
	{
		StopMovement();
		GoRight();
	}

	
	if (DoFieldsEndOnRight(GetX(), GetY(), dt, level) || IsAnyFieldOnRight(GetX(), GetY(), dt, level)) 
	{
		StopMovement();
		GoLeft();
	}
}
