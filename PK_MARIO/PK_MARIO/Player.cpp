#include "StdAfx.h"
#include "Player.h"

void Player::Jump(double y_velocity)
{
	// wykonaj skok o ile jest taka mo¿liwoœæ
	if (m_jump_allowed)
	{
		m_jump_allowed = false;
		m_is_on_ground = false;
		m_vy = y_velocity;            // pocz¹tkowa prêdkoœæ
		m_ay = DefaultYAcceleration;  // przyspieszenie
	}
}

void Player::Update(double dt)
{
	// wylicz now¹ prêdkoœæ oraz po³ó¿enie na osi OY
	if (!m_is_on_ground)
	{
		y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	// je¿eli poni¿ej pierwszego kafla, to nie spadaj ni¿ej.
	// Na razie ustalamy poziom na y=1, aby postaæ nie ucieka³a za ekran
	if (y < 1)
	{
		y = 1;
		PlayerOnGround();
	}

	// wylicz pozycjê gracza w poziomie (oœ OX).
	double next_x = GetNextXPosition(dt);
	if (next_x < x && m_can_go_left)
	{
		x = next_x;
	}
	else if (next_x > x && m_can_go_right)
	{
		x = next_x;
	}

	// nie mo¿na wyjœæ poza mapê
	if (x < 0)
	{
		x = 0; // nie mo¿na wyjœæ za pocz¹tek mapy
	}
	else if (x > m_level_width - 1)
	{
		x = m_level_width - 1; // nie mo¿na wyjœæ za ostatni kafel mapy
	}



	// ustal stan ruchu gracza na podstawie prêdkoœci
	if (fabs(m_vx) < 0.01)
	{
		m_state = TYPES::Standing;
		m_vx = 0;
	}
	else if (m_vx > 0.0)
	{
		m_state = TYPES::GoingRight;
	}
	else
	{
		m_state = TYPES::GoingLeft;
	}

	// uaktualnij animacjê
	switch (m_state)
	{
	case TYPES::Standing:
		m_stop->Update(dt);
		break;
	case TYPES::GoingLeft:
		m_left->Update(dt);
		break;
	case TYPES::GoingRight:
		m_right->Update(dt);
		break;
	}
}

Player::~Player()
{
}

void Player::setSprite(Sprite & data, std::string name, TYPES::PlayerState state)
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
//	::LoadTexture("data/fireball.png");
	//this->Get(name)->m_renderer.setTexture(this->Get(name)->m_renderer.LoadTexture());


}

bool Player::draw()
{
	double height, width;
	height=m_left->m_renderer->GetTileHeight();
	width= m_left->m_renderer->GetTileWidth();

	const double pos_x = x * height;
	const double pos_y = y * width;

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
	return false;
}

