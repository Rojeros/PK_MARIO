#include "StdAfx.h"
#include "Player.h"


bool Player::move(int direction)
{
	return false;
}

bool Player::jump()
{
	return false;
}

bool Player::fire()
{
	return false;
}

Player::~Player()
{
}

void Player::setSprite(Sprite & data, std::string name)
{
	SpriteLoader::Insert(name, data);
	SpriteLoader::Get(name)->m_renderer.LoadTexture();
}

bool Player::draw()
{
	SpriteLoader::Get("lewo")->DrawCurrentFrame(0.5, 0.5, 0.2, 02);
	return false;
}

bool Player::update()
{
	return false;
}
