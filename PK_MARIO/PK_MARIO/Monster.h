#pragma once
#include "Character.h"
class Monster :
	public Character
{
private:
	bool move(int direction);
	bool jump();
	bool fire();
public:
	Monster(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, double speed1) :
		Character::Character(x1, y1, exist1, type1, layer1, hp1, speed1)
	{
	};
	~Monster();

	bool draw();
	void Update(double dt);

};

