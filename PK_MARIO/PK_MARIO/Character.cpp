#include "StdAfx.h"
#include "Character.h"

void Character::SetSprite()
{
	m_right = SetTypeForSprite(TYPES::Character, TYPES::GoingRight);
	m_left = SetTypeForSprite(TYPES::Character, TYPES::GoingLeft);
	m_stop = SetTypeForSprite(TYPES::Character, TYPES::Standing);


}

bool Character::IsDead()
{
	return m_is_dead;
}

bool Character::IsAlive()
{
	return !m_is_dead;
}

void Character::SetIsDead(bool is_dead)
{
	m_is_dead = is_dead;
}


int Character::GetScoresWhenKilled()
{
	return 0;
}

void Character::Update(double dt, Level * p_level)
{
	SetDefaultMovement();
	CheckCollisionsWithLevel(dt, p_level);

	if (!m_is_on_ground) {
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	if (m_y < .5) {
		IsDead();
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

	if (m_x < 1) {
		m_x = 1;
	}

	if (fabs(m_vx) < 0.00001)
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

	switch (m_state)
	{
	case TYPES::Standing:
		m_stop->Update(dt);
		break;
	case TYPES::GoingRight:
		m_left->Update(dt);
		break;
	case TYPES::GoingLeft:
		m_right->Update(dt);
		break;
	}
}

void Character::Draw()
{

	double height, width;
	height = m_left->m_renderer->GetTileHeight();
	width = m_left->m_renderer->GetTileWidth();

	double pos_x = m_x * height;
	double pos_y = m_y * width;

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

void Character::KilledByPlayer()
{
	hp--;
	if (hp <= 0)
		SetIsDead();

}

void Character::KilledWithBullet()
{
	hp--;
	if (hp <= 0)
		SetIsDead(true);
}

double Character::GetNextXPosition(double dt)
{
	return m_x + GetNextXVelocity(dt) * dt;
}

double Character::GetNextYPosition(double dt)
{
	return m_y + GetNextYVelocity(dt) * dt;
}

double Character::GetXVelocity()
{
	return m_vx;
}

double Character::GetYVelocity()
{
	return m_vy;
}

double Character::GetNextXVelocity(double dt)
{
	return m_vx + m_ax * dt;
}

double Character::GetNextYVelocity(double dt)
{
	return m_vy + m_ay * dt;
}

double Character::GetDefaultXVelocity()
{
	return m_default_velocity_x;
}

double Character::GetDefaultYVelocity()
{
	return m_default_velocity_y;
}

void Character::NegateXVelocity()
{
	m_vx = -m_vx;
}

void Character::NegateYVelocity()
{
	m_vy = -m_vy;
}

void Character::NegateVelocity()
{
	NegateXVelocity();
	NegateYVelocity();
}

void Character::SetXVelocity(double velocity)
{
	m_vx = velocity;
}

void Character::SetYVelocity(double velocity)
{
	m_vy = velocity;
}

void Character::SetVelocity(double vx, double vy)
{
	m_vx = vx; m_vy = vy;
}

double Character::GetXAcceleration()
{
	return m_ax;
}

double Character::GetYAcceleration()
{
	return m_ay;
}

double Character::GetDefaultXAcceleration()
{
	return m_default_acceleration_x;
}

double Character::GetDefaultYAcceleration()
{
	return m_default_acceleration_y;
}

void Character::SetXAcceleration(double accel)
{
	m_ax = accel;
}

void Character::SetYAcceleration(double accel)
{
	m_ay = accel;
}

void Character::GoLeft()
{
	m_vx -= GetDefaultXVelocity(); m_state = TYPES::GoingLeft;
}

void Character::GoRight()
{
	m_vx += GetDefaultXVelocity(); m_state = TYPES::GoingRight;
}

void Character::StopLeft()
{
	m_vx += GetDefaultXVelocity(); m_state = TYPES::Standing;
}

void Character::StopRight()
{
	m_vx -= GetDefaultXVelocity(); m_state = TYPES::Standing;
}

void Character::StopMovement()
{
	m_vx = 0; m_state = TYPES::Standing;
}

void Character::ForbidGoingLeft()
{
	m_can_go_left = false;
}

void Character::ForbidGoingRight()
{
	m_can_go_right = false;
}

void Character::Fall()
{
	m_vy = 0.0; m_is_on_ground = false;
}

void Character::SetDefaultMovement()
{
	m_is_on_ground = false; m_can_go_right = m_can_go_left = true;
}

void Character::CharacterOnGround()
{

	m_is_on_ground = true;
	m_vy = 0;

}

bool Character::IsAnyFieldAboveMe(double x, double y, double dt, Level * p_level)
{
	try {
		for (int i = -1; i < 2; ++i) {
			if (p_level->GetMap()->at((int)x + i).at((int)y + 1).GetType() == TYPES::None)
			{
				continue;
			}
			Collisions box((int)x + i, (int)y + 1, (int)x + i + 1, (int)y + 1 + 1);

			if (GetNextVerticalAabb(dt).IsOver(box)) {
				if (p_level->GetMap()->at((int)x + i).at((int)y + 1).GetType() != TYPES::NoDestroyAble)
					p_level->GetMap()->at((int)x + i).at((int)y + 1).Destroy();
				return true;
			}
		}
	}
	catch (...) {}
	return false;
}

bool Character::IsAnyFieldBelowMe(double x, double y, double dt, Level * p_level)
{
	try {
		{
			for (int i = -1; i < 2; ++i) {
				if (p_level->GetMap()->at((int)x + i).at((int)y - 1).GetType() == TYPES::None)
				{
					continue;
				}
				Collisions box((int)x + i, (int)y - 1, (int)x + i + 1, (int)y - 1 + 1);

				if (GetNextVerticalAabb(dt).IsUnder(box)) {
					return true;
				}
			}
		}
	}
	catch (...) {}
	return false;
}

bool Character::IsAnyFieldOnLeft(double x, double y, double dt, Level * p_level)
{
	try {
		{
			for (int i = -1; i < 2; ++i) {
				if (p_level->GetMap()->at((int)x - 1).at((int)y + i).GetType() == TYPES::None)
				{
					continue;
				}
				Collisions box((int)x - 1, (int)y + i, (int)x - 1 + 1, (int)y + i + 1);

				if (GetNextHorizontalAabb(dt).IsOnLeftOf(box)) {
					return true;
				}
			}
		}
	}
	catch (...)
	{
	}
	return false;
}

bool Character::IsAnyFieldOnRight(double x, double y, double dt, Level * p_level)
{
	try {
		{
			for (int i = -1; i < 2; ++i) {
				if (p_level->GetMap()->at((int)x + 1).at((int)y + i).GetType() == TYPES::None)
				{
					continue;
				}
				Collisions box((int)x + 1, (int)y + i, (int)x + 1 + 1, (int)y + i + 1);

				if (GetNextHorizontalAabb(dt).IsOnRightOf(box)) {
					return true;
				}
			}

		}
	}
	catch (...)
	{
	}
	return false;
}
bool Character::DoFieldsEndOnLeft(double x, double y, double dt, Level * p_level) {
	try {
		if ((p_level->GetMap()->at((int)x - 1).at((int)y - 1).GetType() == TYPES::None)
			|| ((p_level->GetMap()->at((int)x - 1).at((int)y - 1).GetType() == TYPES::None) && (Collisions((int)x - 1, (int)y, (int)x - 1 + 1, (int)y + 1).IsOnLeftOf(GetNextHorizontalAabb(dt)))))
		{


			return true;
		}
	}
	catch (...)
	{
	}
	return false;
}

bool Character::DoFieldsEndOnRight(double x, double y, double dt, Level * p_level)
{
	try {
		if ((p_level->GetMap()->at((int)x + 1).at((int)y - 1).GetType() == TYPES::None)
			|| ((p_level->GetMap()->at((int)x + 1).at((int)y - 1).GetType() == TYPES::None)
				&& (Collisions((int)x + 1, (int)y, (int)x + 1 + 1, (int)y + 1).IsOnRightOf(GetNextHorizontalAabb(dt)))))
		{
			return true;
		}
	}
	catch (...)
	{
	}
	return false;
}

void Character::EntityOnGround()
{

	m_is_on_ground = true;
	m_vy = 0;

}

Collisions Character::GetBasicAabb()
{
	return Collisions(0, 0, 1, 1);
}

Collisions Character::GetAabb()
{
	return GetBasicAabb().Move(m_x, m_y, m_x, m_y);
}

Collisions Character::GetNextHorizontalAabb(double dt)
{
	return GetBasicAabb().Move(GetNextXPosition(dt), m_y, GetNextXPosition(dt), m_y);
}

Collisions Character::GetNextVerticalAabb(double dt)
{
	return GetBasicAabb().Move(m_x, GetNextYPosition(dt), m_x, GetNextYPosition(dt));
}

Collisions Character::GetNextAabb(double dt)
{
	return GetBasicAabb().Move(GetNextXPosition(dt), GetNextYPosition(dt),
		GetNextXPosition(dt), GetNextYPosition(dt));
}