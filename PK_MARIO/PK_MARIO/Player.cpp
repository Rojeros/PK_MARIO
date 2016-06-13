#include "StdAfx.h"
#include "Player.h"
#include "Engine.h"

Player::Player(double x, double y, size_t level_width)
	: m_state(PS::Stand),
	m_x(x),
	m_y(y),
	m_vx(0.0),
	m_vy(0),
	m_ay(DefaultYAcceleration),
	m_running_factor(1.0),
	m_jump_allowed(true),
	m_level_width(level_width),
	m_is_on_ground(true),
	m_can_go_left(true),
	m_can_go_right(true) {
	SetDefaultMoving();
}

void Player::SetSprites(SpritePtr left, SpritePtr right, SpritePtr stop) {
	m_left = left;
	m_right = right;
	m_stop = stop;
}

void Player::Jump(double y_velocity) {
	// wykonaj skok o ile jest taka mo¿liwoœæ
	if (m_jump_allowed) {
		m_jump_allowed = false;
		m_is_on_ground = false;
		m_vy = y_velocity;            // pocz¹tkowa prêdkoœæ
		m_ay = DefaultYAcceleration;  // przyspieszenie
	}
}

void Player::Update(double dt) {
	// wylicz now¹ prêdkoœæ oraz po³ó¿enie na osi OY
	if (!m_is_on_ground) {
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	// je¿eli poni¿ej pierwszego kafla, to nie spadaj ni¿ej.
	// Na razie ustalamy poziom na y=1, aby postaæ nie ucieka³a za ekran
	if (m_y < 1) {
		m_y = 1;
		PlayerOnGround();
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
	if (fabs(m_vx) < 0.01) {
		m_state = PS::Stand;
		m_vx = 0;
	}
	else if (m_vx > 0.0) {
		m_state = PS::GoRight;
	}
	else {
		m_state = PS::GoLeft;
	}

	// uaktualnij animacjê
	switch (m_state) {
	case PS::Stand:
		m_stop->Update(dt);
		break;
	case PS::GoLeft:
		m_left->Update(dt);
		break;
	case PS::GoRight:
		m_right->Update(dt);
		break;
	}
}

void Player::Draw() const {
	const double tile_width = Engine::Get().GetRenderer()->GetTileWidth();
	const double tile_height = Engine::Get().GetRenderer()->GetTileHeight();

	// wylicz pozycjê gracza na ekranie
	const double pos_x = m_x * tile_width;
	const double pos_y = m_y * tile_height;

	switch (m_state) {
	case PS::Stand:
		m_stop->DrawCurrentFrame(pos_x, pos_y, tile_width, tile_height);
		break;
	case PS::GoLeft:
		m_left->DrawCurrentFrame(pos_x, pos_y, tile_width, tile_height);
		break;
	case PS::GoRight:
		m_right->DrawCurrentFrame(pos_x, pos_y, tile_width, tile_height);
		break;
	}
}
