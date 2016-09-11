#include "StdAfx.h"
#include "Bonus.h"



TYPES::BonusType Bonus::getBonusType()
{
	return bonusType;
}

Bonus::~Bonus()
{
}

bool Bonus::draw()
{
//	const double tile_width = Sprite::GetRenderer()->GetTileWidth();
//	const double tile_height = SpriteLoader::GetRenderer()->GetTileHeight();
//	Sprite::DrawCurrentFrame();
	return false;
}

void Bonus::Update(double dt)
{
}

