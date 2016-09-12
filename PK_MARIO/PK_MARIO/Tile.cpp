#include "StdAfx.h"
#include "Tile.h"


Tile::~Tile()
{
}

TYPES::FieldType Tile::GetType()
{
	return type;
}

bool Tile::draw()
{
	return true;
}

void Tile::Update(double dt)
{
}

