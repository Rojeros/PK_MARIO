#ifndef BONUS_H_
#define BONUS_H_
#pragma once
#include "Tile.h"
#include "SpriteLoader.h"

class Bonus :
	public Tile,public SpriteLoader
{
private:
	TYPES::BonusType bonusType;
	
public:
	Bonus(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, TYPES::BonusType bonus) :Tile::Tile(x1, y1, exist1, type1, layer1), bonusType(bonus)
	{
	};
	~Bonus();
	TYPES::BonusType getBonusType();


	void Update(double dt, Level* p_level);
	void Draw();
};

#endif