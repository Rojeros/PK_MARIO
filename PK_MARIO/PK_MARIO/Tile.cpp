#include "StdAfx.h"
#include "Tile.h"


Tile::~Tile()
{
}

TYPES::FieldType Tile::GetType()
{
	return type;
}

void Tile::Draw()
{
	
}

void Tile::Destroy()
{
	hp--;
	Update(0,NULL);
}

void Tile::Update(double dt,Level*p_level)
{
	if (this->hp <= 0) {
		exist = false;
		type = TYPES::None;
	}
}

