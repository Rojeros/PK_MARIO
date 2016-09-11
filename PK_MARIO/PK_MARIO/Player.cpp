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
//	::LoadTexture("data/fireball.png");
	//this->Get(name)->m_renderer.setTexture(this->Get(name)->m_renderer.LoadTexture());


}

bool Player::draw()
{
	SpriteLoader::Get("lewo")->DrawCurrentFrame(0, 0, 1, 1);
	return false;
}

bool Player::update(double dt)
{
	SpriteLoader::Get("lewo")->Update(dt);
	return false;
}
