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
	Bonus(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, TYPES::BonusType bonus) :Field::Field(x1, y1, exist1, type1, layer1), bonusType(bonus)
	{
	};
	~Bonus();


	bool draw();
	void Update(double dt);
};

