#ifndef BONUS_H_
#define BONUS_H_
#pragma once
#include "Tile.h"
#include "Character.h"

class Bonus :
	public Character
{
private:
	TYPES::BonusType bonusType;
	int changeDirectionX, changeDirectionY;
	double timer;
	
public:
	Bonus(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, TYPES::BonusType bonus) :Character::Character(x1, y1, exist1, type1, layer1,8,8,8), bonusType(bonus),changeDirectionX(1), changeDirectionY(-1),timer(0)
	{
		SetDefaultMovement();
	};
	Bonus() :Character::Character(0, 0, 0, TYPES::Bonuses, TYPES::Background, 0, 0, 0), bonusType(TYPES::hp), changeDirectionX(1), changeDirectionY(-1), timer(0)
	{
	};
	~Bonus();
	TYPES::BonusType getBonusType();
	TYPES::FieldType GetType() { return TYPES::Bonuses; }
	Collisions GetBasicAabb() {
		return Collisions(0, 0, .4, .4);
	}

	void SetDefaultMovement() {
		SetXVelocity(1);
		SetYVelocity(1);

	}
 double GetNextXPosition(double dt)
 { 
	 double x= m_x + changeDirectionX*GetNextXVelocity(dt) * dt;
	 return x;
 }
double GetNextYPosition(double dt)
{ 
	double y = m_y + changeDirectionY*GetNextYVelocity(dt) * dt;
	return y; }

	void CheckCollisionsWithLevel(double dt, Level * p_level) {
		// czy jednostka koliduje z czymœ od do³u lub od góry
		if (IsAnyFieldBelowMe(m_x, m_y, dt, p_level) || IsAnyFieldAboveMe(m_x, m_y, dt, p_level)) {
			SetIsDead(true);
		}
		// czy jednostka koliduje z czymœ po lewej lub prawej stronie
		if (IsAnyFieldOnLeft(m_x, m_y, dt, p_level) || IsAnyFieldOnRight(m_x, m_y, dt, p_level)) {
			SetIsDead(true);
		}
	}

	void SetSprite()
	{
		m_right = SetTypeForSprite(TYPES::Bonuses, TYPES::hp);
		m_left = SetTypeForSprite(TYPES::Bonuses, TYPES::levelEnd);

	}
	void Update(double dt, Level* p_level);
	void Draw();
};

#endif