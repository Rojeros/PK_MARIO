#ifndef MONSTER_H_
#define MONSTER_H_
#pragma once
#include "Character.h"

class Monster :public Character 
{
enum {
	DefaultXVelocity = 2, DefaultYVelocity = 0, DefaultXAcceleration = 0, DefaultYAcceleration = -60
};

public:
	Monster(double x, double y) :
		Character(x, y,true,TYPES::Enemy,TYPES::Foreground,1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration) {
	}
	Monster() :
		Character(0, 0, false, TYPES::Enemy, TYPES::Foreground, 1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration) {
	}

	int GetScoresWhenKilled()   { return 100; }

	Collisions GetBasicAabb()   {
		return Collisions(0, 0, .9, .9);
	}
	TYPES::FieldType GetType()  ;

	void SetSprite()
	{
		m_right = SetTypeForSprite(TYPES::Enemy, TYPES::GoingRight);
		m_left = SetTypeForSprite(TYPES::Enemy, TYPES::GoingLeft);
		m_stop = SetTypeForSprite(TYPES::Enemy, TYPES::Standing);
	}
	void CheckCollisionsWithLevel(double dt,  Level*level) {
		// ruszaj si� zamiast sta�
		if (GetXVelocity() == 0) {
			GoLeft();
		}

		// czy jednostka koliduje z czym� od do�u
		if (IsAnyFieldBelowMe(GetX(),GetY(),dt, level)) {
			EntityOnGround();
		}

		// koniec pod�o�a lub brak przej�cia z lewej strony
		if (DoFieldsEndOnLeft(GetX(), GetY(), dt, level) || IsAnyFieldOnLeft(GetX(), GetY(), dt, level)) {
			StopMovement();
			GoRight();
		}

		// koniec pod�o�a lub brak przej�cia z prawej strony
		if (DoFieldsEndOnRight(GetX(), GetY(), dt, level) || IsAnyFieldOnRight(GetX(), GetY(), dt, level)) {
			StopMovement();
			GoLeft();
		}
	}
	
};
#endif