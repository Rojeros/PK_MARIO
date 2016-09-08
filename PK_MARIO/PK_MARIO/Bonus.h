#pragma once
#include "Field.h"
#include "SpriteLoader.h"

class Bonus :
	public Field,public SpriteLoader
{
private:
	TYPES::BonusType bonusType;
	TYPES::BonusType getBonusType();
public:
	Bonus(int x1, int y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, TYPES::BonusType bonus) :Field::Field(x1, y1, exist1, type1, layer1), bonusType(bonus)
	{
	};
	~Bonus();


	bool draw();
	bool update();
};

