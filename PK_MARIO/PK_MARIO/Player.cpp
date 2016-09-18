#include "StdAfx.h"
#include "Player.h"

TYPES::FieldType Player::GetType()
{
	return TYPES::Players;
}

void Player::GoLeft()
{
	m_vx -= GetDefaultXVelocity(); m_state = TYPES::GoLeft;
}

void Player::GoRight()
{
	m_vx += GetDefaultXVelocity(); m_state = TYPES::GoRight;
}

void Player::StopLeft()
{
	m_vx += GetDefaultXVelocity(); TurnLeft();
}
void Player::StopRight()
{
	m_vx -= GetDefaultXVelocity(); TurnRight();
}
void Player::StopMovement()
{
	m_vx = 0; m_state = TYPES::Stand;
}
void Player::TurnLeft()
{
	m_state = TYPES::TurnLeft;
}
void Player::TurnRight()
{
	m_state = TYPES::TurnRight;
}
void Player::AllowToJump()
{
	m_jump_allowed = true;
}
void Player::ForbidToJump()
{
	m_jump_allowed = false;
}
void Player::Run()
{
	m_running_factor = 2.0;
}
void Player::StopRunning()
{
	m_running_factor = 1.0;
}
double Player::GetRunningFactor()
{
	return m_running_factor;
}
void Player::Jump(double y_velocity)
{
	
	if (m_jump_allowed)
	{
		m_jump_allowed = false;
		m_is_on_ground = false;
		m_vy = y_velocity;           
		m_ay = DefaultYAcceleration; 
	}
}

void Player::SetDefaultMovement()
{
	m_is_on_ground = m_jump_allowed = false;
	m_can_go_right = m_can_go_left = true;
}

void Player::PlayerOnGround()
{
	m_is_on_ground = m_jump_allowed = true;
	SetYVelocity(0);
}

void Player::Update(double dt,Level*p_level)
{
	CheckCollisionsWithLevel(dt, p_level);
	if (!m_is_on_ground) 
	{
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	
	if (m_y < 0.5) 
	{
		LooseLife();
	
	}

	  double immortality_time = 3; 
	if (m_immortal_duration > immortality_time) 
	{
		m_is_immortal = false;
		m_immortal_duration = 0;
	}
	else {
		m_immortal_duration += dt;
	}
	double next_x = GetNextXPosition(dt);
	if (next_x < m_x && m_can_go_left) 
	{
		m_x = next_x;
	}
	else if (next_x > m_x && m_can_go_right) 
	{
		m_x = next_x;
	}

	
	if (m_x < 1)
	{
		m_x = 1; 
	}
	else if (m_x > m_level_width - 2) 
	{
		m_x = m_level_width - 2; 
	}
	
	if (fabs(m_vx) < 0.001 && (m_state != TYPES::TurnLeft || m_state != TYPES::TurnRight)) {
	
	}
	else if (m_vx > 0.0) {
		m_state = TYPES::GoRight;
	}
	else {
		m_state = TYPES::GoLeft;
	}
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
	
		break;
	}
}

void Player::CollisionOnRight(std::vector<Character*>::iterator it) 
{
	LooseLife();
}

void Player::CollisionOnLeft(std::vector<Character*>::iterator it) 
{
	LooseLife();
}

void Player::CollisionOverPlayer(std::vector<Character*>::iterator it) 
{
	LooseLife();
}

void Player::CollisionUnderPlayer(std::vector<Character*>::iterator it) 
{
	AllowToJump();
	Jump(GetDefaultYVelocity() + 6);
	AddScores((*it)->GetScoresWhenKilled() * 2);
	(*it)->KilledByPlayer();
}
void Player::SetSprite()
{
	m_right = SetTypeForSprite(TYPES::Players, TYPES::GoingRight);
	m_left = SetTypeForSprite(TYPES::Players, TYPES::GoingLeft);
	m_stop = SetTypeForSprite(TYPES::Players, TYPES::Standing);
	
}

bool Player::IsImmortal()
{
	return m_is_immortal;
}

bool Player::MoveMap()
{
	  size_t screen_tiles_count = SpriteRenderer().GetHorizontalTilesOnScreenCount();
	  size_t half_screen_tiles_count = screen_tiles_count / 2;

	return((m_x > half_screen_tiles_count - 1) && (m_x < ((m_level_width - 1) - half_screen_tiles_count)));
}



void Player::FireBullet()
{
	bulletShooted = true;
}

bool Player::isBulletFired()
{
	return bulletShooted;
}

void Player::DisableBullet()
{
	bulletShooted = false;
}

TYPES::PlayerState Player::GetState()
{
	return m_state;
}

void Player::Draw()
{
	Text scores_text;
	scores_text.SetSize(0.05, 0.05);
	scores_text.DrawText("Score " + scores_text.IntToStr(GetScores()), .01, .9);
	scores_text.DrawText("Lives " + scores_text.IntToStr(GetLifesCount()), .65, .9);


	if (IsImmortal() && int(m_immortal_duration * 10) % 2 == 1) 
	{
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

int Player::GetLifesCount()
{
	return hp;
}

void Player::LooseLife()
{
	hp--;


	m_is_immortal = true;
	m_immortal_duration = 0;
	setCoord(3, 4);

}

void Player::LevelCompleted(bool status)
{
	m_is_level_completed = status;
}

bool Player::IsLevelCompleted()
{
	return m_is_level_completed;
}

bool Player::HasCompletedCurrentLevel()
{
	return m_is_level_completed;
}


void Player::addLive()
{
	hp++;
}

double Player::GetNextXPosition(double dt)
{
	return GetX() + GetXVelocity() * dt * GetRunningFactor();
}

Collisions Player::GetBasicAabb()
{
	return Collisions(0, 0, .7, .9);
}

void Player::CheckCollisionsWithLevel(double dt, Level * p_level)
{
	if (IsAnyFieldAboveMe(GetX(),GetY(), dt, p_level)) 
	{
		Fall();
	}
	if (IsAnyFieldBelowMe(GetX(),GetY(), dt, p_level)) 
	{
		PlayerOnGround();
	}
	if (IsAnyFieldOnRight(GetX(),GetY(), dt, p_level)) 
	{
		ForbidGoingRight();
	}
	if (IsAnyFieldOnLeft(GetX(), GetY(), dt, p_level)) 
	{
		ForbidGoingLeft();
	}

}

void Player::AddScores(int scores)
{
	m_total_scores += scores;
}

int Player::GetScores()
{
	return m_total_scores;
}
