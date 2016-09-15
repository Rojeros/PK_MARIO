#include "StdAfx.h"
#include "Player.h"

void Player::Jump(double y_velocity)
{
	// wykonaj skok o ile jest taka mo�liwo��
	if (m_jump_allowed)
	{
		m_jump_allowed = false;
		m_is_on_ground = false;
		m_vy = y_velocity;            // pocz�tkowa pr�dko��
		m_ay = DefaultYAcceleration;  // przyspieszenie
	}
}

void Player::Update(double dt,Level*p_level)
{
	CheckCollisionsWithLevel(dt, p_level);
	// wylicz now� pr�dko�� oraz po��enie na osi OY
	if (!m_is_on_ground) {
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	// je�eli poni�ej pierwszego kafla, to odbieramy �ycie.
	if (m_y < 0.5) {
		LooseLife();
	
	}

	// uaktualnij informacje o nie�miertelno�ci
	  double immortality_time = 3; // 3 sekundy
	if (m_immortal_duration > immortality_time) {
		m_is_immortal = false;
		m_immortal_duration = 0;
	}
	else {
		m_immortal_duration += dt;
	}

	// wylicz pozycj� gracza w poziomie (o� OX).
	double next_x = GetNextXPosition(dt);
	if (next_x < m_x && m_can_go_left) {
		m_x = next_x;
	}
	else if (next_x > m_x && m_can_go_right) {
		m_x = next_x;
	}

	// nie mo�na wyj�� poza map�
	if (m_x < 1) {
		m_x = 1; // nie mo�na wyj�� za pocz�tek mapy
	}
	else if (m_x > m_level_width - 2) {
		m_x = m_level_width - 2; // nie mo�na wyj�� za ostatni kafel mapy
	}
	// ustal stan ruchu gracza na podstawie pr�dko�ci
	if (fabs(m_vx) < 0.001 && (m_state != TYPES::TurnLeft || m_state != TYPES::TurnRight)) {
		// nie zmieniamy stanu
	}
	else if (m_vx > 0.0) {
		m_state = TYPES::GoRight;
	}
	else {
		m_state = TYPES::GoLeft;
	} // uaktualnij animacj�
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
		// animacja ma jedn� klatk�, wi�c niczego nie aktualizujemy
		break;
	}
}

void Player::CollisionOnRight(std::vector<Monster>::iterator it) {
	LooseLife();
}

void Player::CollisionOnLeft(std::vector<Monster>::iterator it) {
	LooseLife();
}

void Player::CollisionOverPlayer(std::vector<Monster>::iterator it) {
	LooseLife();
}

void Player::CollisionUnderPlayer(std::vector<Monster>::iterator it) {
	AllowToJump();
	Jump(GetDefaultYVelocity() + 6);
	AddScores(it->GetScoresWhenKilled() * 2);
	it->KilledByPlayer();
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
	  size_t screen_tiles_count = SpriteRenderer().GetHorizontalTilesOnScreenCount();
	  size_t half_screen_tiles_count = screen_tiles_count / 2;

	return((m_x > half_screen_tiles_count - 1) && (m_x < ((m_level_width - 1) - half_screen_tiles_count)));
}



void Player::Draw()
{
	Text scores_text;
	scores_text.SetSize(0.05, 0.05);
	scores_text.DrawText("Score " + scores_text.IntToStr(GetScores()), .01, .9);
	scores_text.DrawText("Lives " + scores_text.IntToStr(GetLifesCount()), .65, .9);

	// je�eli bohater jest nie�miertelny, to miga (rysuj - nie rysuj)
	if (IsImmortal() && int(m_immortal_duration * 10) % 2 == 1) {
		return;
	}
	double height, width;
	height=m_left->m_renderer->GetTileHeight();
	width= m_left->m_renderer->GetTileWidth();

	  double pos_x = m_x * height;
	  double pos_y = m_y * width;

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

void Player::LooseLife()
{
	hp--;

	// nie�miertelno�� przez pewien czas
	m_is_immortal = true;
	m_immortal_duration = 0;
	setCoord(3, 4);
}


void Player::CheckCollisionsWithLevel(double dt, Level * p_level)
{
	if (IsAnyFieldAboveMe(GetX(),GetY(), dt, p_level)) {
		Fall();
	}
	if (IsAnyFieldBelowMe(GetX(),GetY(), dt, p_level)) {
		PlayerOnGround();
	}
	if (IsAnyFieldOnRight(GetX(),GetY(), dt, p_level)) {
		ForbidGoingRight();
	}
	if (IsAnyFieldOnLeft(GetX(), GetY(), dt, p_level)) {
		ForbidGoingLeft();
	}

}