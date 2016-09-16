#ifndef BULLET_H_
#define BULLET_H_

#include "StdAfx.h"
#include "Character.h"
class Bullet :
	public Character
{
	enum {
		DefaultXVelocity = 6, DefaultYVelocity = 0,
		DefaultXAcceleration = 0, DefaultYAcceleration = 0,
		DefaultTimeToLive = 2   // czas �ycia = 2s
	};

public:
	Bullet(double x, double y, double xVelocity, double yVelocity) :
		Character(x, y,true,TYPES::PlayerBullet,TYPES::Foreground,1, 0, 0,
			0, 0),
		m_time_to_live(DefaultTimeToLive) {

		m_vx = xVelocity < 0 ? -DefaultXVelocity : DefaultXVelocity;
		m_vy = DefaultYVelocity;
	}

	 TYPES::FieldType GetType() { return TYPES::PlayerBullet; }
	 Collisions GetBasicAabb()  {
		return Collisions(0, 0, .4, .4);
	}

	void SetDefaultMovement() {
	}

	void Update(double dt, Level* p_level) {
		m_right->Update(dt);

		// usu� obiekt je�eli �yje zbyt d�ugo
		m_time_to_live -= dt;
		if (m_time_to_live < 0) {
			SetIsDead(true);
			return;
		}

		// sprawd� kolizje
		CheckCollisionsWithLevel(dt, p_level);
		SetPosition(GetNextXPosition(dt), GetNextYPosition(dt));
	}

	void CheckCollisionsWithLevel(double dt, Level * p_level) {
		// czy jednostka koliduje z czym� od do�u lub od g�ry
		if (IsAnyFieldBelowMe(m_x,m_y,dt, p_level) || IsAnyFieldAboveMe(m_x, m_y, dt, p_level)) {
			SetIsDead(true);
		}

		// czy jednostka koliduje z czym� po lewej lub prawej stronie
		if (IsAnyFieldOnLeft(m_x, m_y, dt, p_level) || IsAnyFieldOnRight(m_x, m_y, dt, p_level)) {
			SetIsDead(true);
		}
	}
	void setSprite(Sprite & data, std::string name, TYPES::FieldType state)
	{
		SpriteLoader::Insert(name, data);

			m_right = SpriteLoader::Get(name);
			m_state = TYPES::GoingRight;
		}

	

private:
	double m_time_to_live;   // czas, kt�ry pozosta� do samozniszczenia
};

#endif // !BULLET_H_
