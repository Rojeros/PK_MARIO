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
		std::string platformleft = "PlatformLeftEnd", platformmid = "PlatformMidPart", platformright = "PlatformRightEnd";

		double tile_height = SpriteRenderer::GetTileHeight();
		double tile_width = SpriteRenderer::GetTileWidth();

		
			
			
					if (isExist()) {
						std::string name;
						switch (GetType()) {
						case TYPES::PlatformLeftEnd:
							name = platformleft;
							break;
						case TYPES::PlatformMidPart:
							name = platformmid;
							break;
						case TYPES::PlatformRightEnd:
							name = platformright;
							break;
						case TYPES::None:
							name = "NULL";
							break;
						}

						if (name != "NULL")
						{
							double tile_width = SpriteLoader::Get(name)->m_renderer->GetTileWidth();
							double tile_height = SpriteLoader::Get(name)->m_renderer->GetTileWidth();

							SpriteLoader::Get(name)->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_width, tile_height);
			
				}
			}
		
}


void Tile::Destroy()
{
	hp--;
	Update(0,NULL);
}

void Tile::Change(TYPES::FieldType type1)
{

	type = type1;
}

void Tile::Update(double dt,Level*p_level)
{
	if (this->hp <= 0) {
		exist = false;
		type = TYPES::None;
	}
}

