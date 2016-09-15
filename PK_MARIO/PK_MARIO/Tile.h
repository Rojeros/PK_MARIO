#ifndef TILE_H_
#define TILE_H_

#pragma once


#include "SpriteLoader.h"
#include "Field.h"
class Tile :
	public Field,public SpriteLoader
{
private:
public:
	Tile() :Field::Field(0, 0, false, TYPES::None, TYPES::Background,2)
	{};
	Tile(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :Field::Field(x1, y1, exist1, type1, layer1,2)
	{};
	~Tile();
	TYPES::FieldType GetType();
	void Draw();
	void Destroy();
	
	void Update(double dt,Level * p_level);
};

#endif