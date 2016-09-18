#include "StdAfx.h"
#include "Tile.h"

Sprite *  Tile::Spriteleft, *Tile::SpriteMid, *Tile::SpriteRight, *Tile::SpriteNoDestruct;
Tile::~Tile()
{
}

TYPES::FieldType Tile::GetType()
{
	return type;
}


	void Tile::Draw()
	{

		double tile_height = SpriteRenderer::GetTileHeight();
		double tile_width = SpriteRenderer::GetTileWidth();

					if (isExist()) {
					
					
							double tile_width = Spritepoiner->m_renderer->GetTileWidth();
							double tile_height = Spritepoiner->m_renderer->GetTileWidth();
							
							Spritepoiner->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_width, tile_height);
			
				}
			
		
}


void Tile::Destroy()
{
	if(GetType() != TYPES::NoDestroyAble)
	hp--;
	Update(0,NULL);
}

void Tile::Change(TYPES::FieldType type1)
{

	type = type1;
}

void Tile::SetSprite()
{
	Spriteleft= SetTypeForSprite(TYPES::PlatformLeftEnd, TYPES::None);
	SpriteMid = SetTypeForSprite(TYPES::PlatformMidPart, TYPES::None);
	SpriteRight = SetTypeForSprite(TYPES::PlatformRightEnd, TYPES::None);
	SpriteNoDestruct= SetTypeForSprite(TYPES::NoDestroyAble, TYPES::None);
}

void Tile::Update(double dt,Level*p_level)
{
	if (this->hp <= 0) {
		exist = false;
		type = TYPES::None;
	}
}

