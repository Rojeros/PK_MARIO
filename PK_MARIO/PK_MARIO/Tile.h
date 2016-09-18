#ifndef TILE_H_
#define TILE_H_

#pragma once


#include "SpriteLoader.h"
#include "Field.h"
class Tile :
	public Field,public SpriteLoader
{
private:
	static Sprite * Spriteleft,*SpriteMid,*SpriteRight,*SpriteNoDestruct;
	Sprite * Spritepoiner;
public:
	Tile() :Field::Field(0, 0, false, TYPES::None, TYPES::Background,2)
	{};
	Tile(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :Field::Field(x1, y1, exist1, type1, layer1,2)
	{
	switch(type1){
	case TYPES::PlatformLeftEnd:
		Spritepoiner = Spriteleft;
		break;
	case TYPES::PlatformMidPart:
		Spritepoiner = SpriteMid;
		break;
	case TYPES::PlatformRightEnd:
		Spritepoiner = SpriteRight;
		break;
	case TYPES::NoDestroyAble:
		Spritepoiner = SpriteNoDestruct;
		break;
	case TYPES::None:
		break;
	default:
		throw "Tile constructor error";
		break;
	}
	};
	~Tile();
	TYPES::FieldType GetType();
	void Draw();
	void Destroy();
	void Change(TYPES::FieldType);
	void SetSprite();
	void Update(double dt,Level * p_level);
};

#endif