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
	Monster(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, size_t level_width, double def_velocity_x, double def_velocity_y,
		double def_acceleration_x = 0, double def_acceleration_y = 0) :
		Character(x1, y1, exist1, type1, layer1, hp1, def_velocity_x, def_velocity_y, def_acceleration_x, def_acceleration_y)
	{
		SetDefaultMovement();
	}
	~Monster();

	void Draw();
	void Update(double dt);

};

