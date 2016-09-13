#include "StdAfx.h"
#include "Character.h"

void Character::setSprite(Sprite & data, std::string name, TYPES::CharacterState state)
{
	SpriteLoader::Insert(name, data);
	switch (state) {
	case TYPES::GoingLeft:
		m_left = SpriteLoader::Get(name);
		break;
	case TYPES::GoingRight:
		m_right = SpriteLoader::Get(name);
		break;
	case TYPES::Standing:
		m_stop = SpriteLoader::Get(name);
		break;
	}


}


void Character::Draw() {

	double height, width;
	height = m_left->m_renderer->GetTileHeight();
	width = m_left->m_renderer->GetTileWidth();

	const double pos_x = m_x * height;
	const double pos_y = m_y * width;

	switch (m_state)
	{
	case TYPES::Standing:
		m_stop->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::GoingLeft:
		m_left->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::GoingRight:
		m_right->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	}
}

void Character::KilledByPlayer() {
	SetIsDead(true);
	// std::cout << "[Character] Killed by player" << std::endl;
}

void Character::KilledWithBullet() {
	SetIsDead(true);
	// std::cout << "[Character] Killed by bullet" << std::endl;
}
