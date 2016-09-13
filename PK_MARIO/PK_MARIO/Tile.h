#pragma once
#include "Field.h"
#include "SpriteLoader.h"
class Tile :
	public Field,public SpriteLoader
{
private:
public:
	Tile() :Field::Field(0, 0, false, TYPES::None, TYPES::Background)
	{};
	Tile(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :Field::Field(x1, y1, exist1, type1, layer1)
	{};
	~Tile();
	TYPES::FieldType GetType();
	void Draw();
	
	void Update(double dt);
};

