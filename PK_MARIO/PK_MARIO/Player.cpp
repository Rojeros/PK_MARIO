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
	if (!m_is_on_ground) {
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	// je¿eli poni¿ej pierwszego kafla, to odbieramy ¿ycie.
	if (m_y < 1) {
	//	LooseLife();
		m_y = 1;
		PlayerOnGround();
	}

	// uaktualnij informacje o nieœmiertelnoœci
	const double immortality_time = 3; // 3 sekundy
	if (m_immortal_duration > immortality_time) {
		m_is_immortal = false;
		m_immortal_duration = 0;
	}
	else {
		m_immortal_duration += dt;
	}

	// wylicz pozycjê gracza w poziomie (oœ OX).
	double next_x = GetNextXPosition(dt);
	if (next_x < m_x && m_can_go_left) {
		m_x = next_x;
	}
	else if (next_x > m_x && m_can_go_right) {
		m_x = next_x;
	}

	// nie mo¿na wyjœæ poza mapê
	if (m_x < 0) {
		m_x = 0; // nie mo¿na wyjœæ za pocz¹tek mapy
	}
	else if (m_x > m_level_width - 1) {
		m_x = m_level_width - 1; // nie mo¿na wyjœæ za ostatni kafel mapy
	}
	// ustal stan ruchu gracza na podstawie prêdkoœci
	if (fabs(m_vx) < 0.001 && (m_state != TYPES::TurnLeft || m_state != TYPES::TurnRight)) {
		// nie zmieniamy stanu
	}
	else if (m_vx > 0.0) {
		m_state = TYPES::GoRight;
	}
	else {
		m_state = TYPES::GoLeft;
	} // uaktualnij animacjê
	switch (m_state) {
	case TYPES::Stand:
		m_stop->Update(dt);
		break;
	case TYPES::GoLeft:
		m_left->Update(dt);
		break;
	case TYPES::GoRight:
		m_right->Update(dt);
		break;
	case TYPES::TurnLeft:
	case TYPES::TurnRight:
		// animacja ma jedn¹ klatkê, wiêc niczego nie aktualizujemy
		break;
	}
}

void Player::setSprite(Sprite & data, std::string name, TYPES::PlayerState state)
{
	SpriteLoader::Insert(name, data);
	switch (state) {
	case TYPES::GoLeft:
		m_left = SpriteLoader::Get(name);
		break;
	case TYPES::GoRight:
		m_right = SpriteLoader::Get(name);
		break;
	case TYPES::Stand:
		m_stop = SpriteLoader::Get(name);
		break;
	}

}

bool Player::MoveMap()
{
	const size_t screen_tiles_count = SpriteRenderer().GetHorizontalTilesOnScreenCount();
	const size_t half_screen_tiles_count = screen_tiles_count / 2;

	return((m_x > half_screen_tiles_count - 1) && (m_x < ((m_level_width - 1) - half_screen_tiles_count)));
}



void Player::Draw()
{
	double height, width;
	height=m_left->m_renderer->GetTileHeight();
	width= m_left->m_renderer->GetTileWidth();

	const double pos_x = m_x * height;
	const double pos_y = m_y * width;

	switch (m_state)
	{
	case TYPES::Stand:
		m_stop->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::GoLeft:
		m_left->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::GoRight:
		m_right->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::TurnLeft:
		m_left->SetCurrentFrame(0);
		m_left->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	case TYPES::TurnRight:
		m_right->SetCurrentFrame(0);
		m_right->DrawCurrentFrame(pos_x, pos_y, width, height);
		break;
	}
}

