#include "StdAfx.h"
#include "Bonus.h"



TYPES::BonusType Bonus::getBonusType()
{
	return bonusType;
}

Bonus::~Bonus()
{
}

void Bonus::Update(double dt, Level * p_level)
{
	timer += dt;
	if(timer>0.5){
	changeDirectionX *= -1;
	changeDirectionY *= -1;
	timer = 0;
	}
	m_right->Update(dt);
	SetPosition(GetX(), GetNextYPosition(dt));
}

void Bonus::Draw()
{
	double tile_height = SpriteRenderer::GetTileHeight();
	double tile_width = SpriteRenderer::GetTileWidth();




	if (isExist()) {
		std::string name;
		switch (getBonusType()) {
		case TYPES::hp:
			name = "hpBonus";
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
