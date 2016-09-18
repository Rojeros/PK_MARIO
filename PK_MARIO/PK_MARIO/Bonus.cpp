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

	double tile_w ;
	double tile_h ;

	if (isExist()) {

		switch (getBonusType()) {
		case TYPES::hp:
			 
			m_right->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_height, tile_width);
			break;
		case TYPES::levelEnd:
			
			m_left->DrawCurrentFrame((m_x)* tile_height, m_y * tile_width, tile_height, tile_width);
			break;
		}

	}

}
