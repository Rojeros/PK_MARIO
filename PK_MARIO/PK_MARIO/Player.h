#pragma once
#include "Character.h"
class Player :
	public Character
{
private:
	bool move(int direction);
	bool jump();
	bool fire();
public:
	Player(int x1, int y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, double speed1) :
		Character::Character(x1, y1, exist1, type1, layer1, hp1, speed1)
	{
	};
	~Player();
	void setSprite(Sprite&data, std::string name);
	bool draw();
	bool update();

};

