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


void Character::Update(double dt, Level * p_level)
{
	// ustaw domyœlny ruch i sprawdŸ czy co w œwiecie piszczy
	SetDefaultMovement();
	CheckCollisionsWithLevel(dt, p_level);

	// wylicz now¹ prêdkoœæ oraz po³ó¿enie na osi OY
	if (!m_is_on_ground) {
		m_y = GetNextYPosition(dt);
		m_vy += m_ay * dt;
	}

	// je¿eli poni¿ej pierwszego kafla, to nie spadaj ni¿ej.
	// Na razie ustalamy poziom na y=1, aby jednostka nie ucieka³a za ekran
	if (m_y < .5) {
		IsDead();
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
	if (m_x < 1) {
		m_x = 1; // nie mo¿na wyjœæ za pocz¹tek mapy
	}

	// ustal stan ruchu gracza na podstawie prêdkoœci
	if (fabs(m_vx) < 0.00001) {
		m_state = TYPES::Standing;
		m_vx = 0;
	}
	else if (m_vx > 0.0) {
		m_state = TYPES::GoingRight;
	}
	else {
		m_state = TYPES::GoingLeft;
	}

	// uaktualnij animacjê
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
	}
}

void Character::Draw() {

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

void Character::KilledByPlayer() {
	hp--;
	if(hp<=0)
	SetIsDead();

}

void Character::KilledWithBullet() {
	hp--;
	if (hp<=0)
	SetIsDead(true);
}

bool Character::IsAnyFieldAboveMe(double x, double y, double dt, Level * p_level)
{

	for (int i = -1; i < 2; ++i) {
		if (p_level->GetMap()->at((int)x + i).at((int)y + 1).GetType() == TYPES::None) {
			continue;
		}
		Collisions box((int)x + i, (int)y + 1, (int)x + i + 1, (int)y + 1 + 1);

		if (GetNextVerticalAabb(dt).IsOver(box)) {
			if (p_level->GetMap()->at((int)x + i).at((int)y + 1).GetType() != TYPES::NoDestroyAble)
				p_level->GetMap()->at((int)x + i).at((int)y + 1).Destroy();
			return true;
		}
	}
	return false;
}

bool Character::IsAnyFieldBelowMe(double x, double y, double dt, Level * p_level)
{
	if (y >= 1) {
		for (int i = -1; i < 2; ++i) {
			if (p_level->GetMap()->at((int)x + i).at((int)y - 1).GetType() == TYPES::None) {
				continue;
			}
			Collisions box((int)x + i, (int)y - 1, (int)x + i + 1, (int)y - 1 + 1);

			if (GetNextVerticalAabb(dt).IsUnder(box)) {
				return true;
			}
		}
	}
	return false;
}

bool Character::IsAnyFieldOnLeft(double x, double y, double dt, Level * p_level)
{
	if (y >= 1) {
		for (int i = -1; i < 2; ++i) {
			if (p_level->GetMap()->at((int)x - 1).at((int)y + i).GetType() == TYPES::None) {
				continue;
			}
			Collisions box((int)x - 1, (int)y + i, (int)x - 1 + 1, (int)y + i + 1);

			if (GetNextHorizontalAabb(dt).IsOnLeftOf(box)) {
				return true;
			}
		}
	}
	return false;
}

bool Character::IsAnyFieldOnRight(double x, double y, double dt, Level * p_level)
{
	if (y >= 1) {
		for (int i = -1; i < 2; ++i) {
			if (p_level->GetMap()->at((int)x + 1).at((int)y + i).GetType() == TYPES::None) {
				continue;
			}
			Collisions box((int)x + 1, (int)y + i, (int)x + 1 + 1, (int)y + i + 1);

			if (GetNextHorizontalAabb(dt).IsOnRightOf(box)) {
				return true;
			}
		}
	}
	return false;
}
bool Character::DoFieldsEndOnLeft(double x, double y, double dt, Level * p_level){
	try{
		if ((p_level->GetMap()->at((int)x - 1).at((int)y - 1).GetType() == TYPES::None)
			|| ((p_level->GetMap()->at((int)x - 1).at((int)y - 1).GetType() == TYPES::None) && (Collisions((int)x - 1, (int)y, (int)x - 1 + 1, (int)y + 1).IsOnLeftOf(GetNextHorizontalAabb(dt))))) {
		

	// czy pole o jeden w lewo i w do³ jest puste (None)
	// oraz czy jednostka jest przy krawêdzi (IsOnLeftOf)...
		
			return true;
		}
	}
	catch (...) {}
	return false;
}

bool Character::DoFieldsEndOnRight(double x, double y, double dt, Level * p_level) {
	try {
	if ((p_level->GetMap()->at((int)x + 1).at((int)y - 1).GetType() == TYPES::None)
		||( (p_level->GetMap()->at((int)x + 1).at((int)y - 1).GetType() == TYPES::None)&& (Collisions((int)x + 1, (int)y, (int)x + 1 + 1, (int)y + 1).IsOnRightOf(GetNextHorizontalAabb(dt))))) {
		return true;
	}
	}
	catch (...) {}
	return false;
}
