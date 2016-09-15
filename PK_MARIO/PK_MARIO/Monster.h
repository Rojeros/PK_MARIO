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

	int GetScoresWhenKilled()   { return 100; }

	Collisions GetBasicAabb()   {
		return Collisions(0, 0, .9, .9);
	}
	TYPES::FieldType GetType()  ;

	void setSprite(Sprite & data, std::string name, TYPES::MonsterState state)
	{
		SpriteLoader::Insert(name, data);
		switch (state) {
		case TYPES::GoLeft:
			m_left = SpriteLoader::Get(name);
			break;
		case TYPES::GoRight:
			m_right = SpriteLoader::Get(name);
			break;
		case TYPES::Stand:
			m_stop = SpriteLoader::Get(name);
			break;
		}

	}
	void CheckCollisionsWithLevel(double dt,  Level*level) {
		// ruszaj siê zamiast staæ
		if (GetXVelocity() == 0) {
			GoLeft();
		}

		// czy jednostka koliduje z czymœ od do³u
		if (IsAnyFieldBelowMe(GetX(),GetY(),dt, level)) {
			EntityOnGround();
		}

		// koniec pod³o¿a lub brak przejœcia z lewej strony
		if (DoFieldsEndOnLeft(GetX(), GetY(), dt, level) || IsAnyFieldOnLeft(GetX(), GetY(), dt, level)) {
			StopMovement();
			GoRight();
		}

		// koniec pod³o¿a lub brak przejœcia z prawej strony
		if (DoFieldsEndOnRight(GetX(), GetY(), dt, level) || IsAnyFieldOnRight(GetX(), GetY(), dt, level)) {
			StopMovement();
			GoLeft();
		}
	}
	
};
#endif