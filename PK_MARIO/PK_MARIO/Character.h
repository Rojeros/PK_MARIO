#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "SpriteLoader.h"
#include "Collisions.h"

class Character :
	public Field,public SpriteLoader
{
public:
	Character(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, double def_velocity_x, double def_velocity_y,
		double def_acceleration_x = 0, double def_acceleration_y = 0) :
		Field::Field(x1, y1, exist1, type1, layer1), hp(hp1),
		 m_default_velocity_x(def_velocity_x),
		m_default_velocity_y(def_velocity_y),
		m_default_acceleration_x(def_acceleration_x),
		m_default_acceleration_y(def_acceleration_y),
		m_is_dead(false),
		m_state(TYPES::Standing),
		m_vx(0.0),
		m_vy(0),
		m_ax(def_acceleration_x),
		m_ay(def_acceleration_y),
		m_is_on_ground(true),
		m_can_go_left(true),
		m_can_go_right(true)
	{
		SetDefaultMovement();
	}
	virtual TYPES::CharacterState GetType() const = 0;
	virtual int GetScoresWhenKilled() const { return 0; }
	virtual void Update(double dt)=0;
	virtual void Draw();
	void setSprite(Sprite & data, std::string name, TYPES::CharacterState state);
	bool IsDead() const { return m_is_dead; }
	bool IsAlive() const { return !m_is_dead; }
	void SetIsDead(bool is_dead = true) { m_is_dead = is_dead; }
	void KilledByPlayer();
	void KilledWithBullet();

	// zarz¹dzanie po³o¿eniem 
	double GetX() const { return m_x; }
	double GetY() const { return m_y; }
	virtual double GetNextXPosition(double dt) const { return m_x + GetNextXVelocity(dt) * dt; }
	virtual double GetNextYPosition(double dt) const { return m_y + GetNextYVelocity(dt) * dt; }
	void SetX(double newx) { m_x = newx; }
	void SetY(double newy) { m_y = newy; }
	void SetPosition(double x, double y) { m_x = x; m_y = y; }

	// zarz¹dzanie prêdkoœci¹
	double GetXVelocity() const { return m_vx; }
	double GetYVelocity() const { return m_vy; }
	double GetNextXVelocity(double dt) const { return m_vx + m_ax * dt; }
	double GetNextYVelocity(double dt) const { return m_vy + m_ay * dt; }
	double GetDefaultXVelocity() const { return m_default_velocity_x; }
	double GetDefaultYVelocity() const { return m_default_velocity_y; }
	void  NegateXVelocity() { m_vx = -m_vx; }
	void  NegateYVelocity() { m_vy = -m_vy; }
	void  NegateVelocity() { NegateXVelocity(); NegateYVelocity(); }
	void  SetXVelocity(double velocity) { m_vx = velocity; }
	void  SetYVelocity(double velocity) { m_vy = velocity; }
	void  SetVelocity(double vx, double vy) { m_vx = vx; m_vy = vy; }

	// zarz¹dzanie przyspieszeniem
	double GetXAcceleration() const { return m_ax; }
	double GetYAcceleration() const { return m_ay; }
	double GetDefaultXAcceleration() const { return m_default_acceleration_x; }
	double GetDefaultYAcceleration() const { return m_default_acceleration_y; }
	void  SetXAcceleration(double accel) { m_ax = accel; }
	void  SetYAcceleration(double accel) { m_ay = accel; }

	// podstawowa zmiana stanu ruchu jednostki
	virtual void GoLeft() { m_vx -= GetDefaultXVelocity(); m_state = TYPES::GoingLeft; }
	virtual void GoRight() { m_vx += GetDefaultXVelocity(); m_state = TYPES::GoingRight; }
	virtual void StopLeft() { m_vx += GetDefaultXVelocity(); m_state = TYPES::Standing; }
	virtual void StopRight() { m_vx -= GetDefaultXVelocity(); m_state = TYPES::Standing; }
	virtual void StopMovement() { m_vx = 0; m_state = TYPES::Standing; }
	void ForbidGoingLeft() { m_can_go_left = false; }
	void ForbidGoingRight() { m_can_go_right = false; }
	void Fall() { m_vy = 0.0; m_is_on_ground = false; }
	virtual void SetDefaultMovement() { m_is_on_ground = false; m_can_go_right = m_can_go_left = true; }
	void CharacterOnGround() {
		m_is_on_ground = true;
		m_vy = 0;
	}


	// pod argumenty x, y zapisuje numer aktualnego kafla
	void GetCurrentTile(size_t *x, size_t *y) const {
		const size_t v_tiles_count = SpriteRenderer::GetVerticalTilesOnScreenCount();
		*y = (size_t)(v_tiles_count - (GetAabb().GetMinY() + GetAabb().GetMaxY()) / 2);
		*x = (size_t)(GetX() + GetBasicAabb().GetMaxX() / 2);
	}

	// prostok¹t otaczaj¹cy jednostkê bez uwzglêdniania pozycji jednostki
	virtual Collisions GetBasicAabb() const { return Collisions(0, 0, 1, 1); }

	Collisions GetAabb() const { return GetBasicAabb().Move(m_x, m_y, m_x, m_y); }

	Collisions GetNextHorizontalAabb(double dt) const {
		return GetBasicAabb().Move(GetNextXPosition(dt), m_y, GetNextXPosition(dt), m_y);
	}

	Collisions GetNextVerticalAabb(double dt) const {
		return GetBasicAabb().Move(m_x, GetNextYPosition(dt), m_x, GetNextYPosition(dt));
	}

	Collisions GetNextAabb(double dt) const {
		return GetBasicAabb().Move(GetNextXPosition(dt), GetNextYPosition(dt),
			GetNextXPosition(dt), GetNextYPosition(dt));
	}

private:
	double m_default_velocity_x;      // domyœlna prêdkoœæ
	double m_default_velocity_y;
	double m_default_acceleration_x;  // domyœlne przyspieszenie
	double m_default_acceleration_y;

	bool m_is_dead;           // czy jednostka jest martwa

protected:
	TYPES::CharacterState m_state;  // stan, w którym znajduje siê jednostka
	Sprite * m_left;         // animacja, kiedy jednostka idzie w lewo
	Sprite * m_right;        // animacja, kiedy jednostka idzie w prawo
	Sprite * m_stop;         // animacja, kiedy jednostka stoi

	int hp;
	double m_vx;              // prêdkoœæ w poziomie
	double m_vy;              // prêdkoœæ w pionie
	double m_ax;              // przyspieszenie w poziomie
	double m_ay;              // przyspieszenie w pionie
	bool m_is_on_ground;      // czy postaæ jest na pod³o¿u
	bool m_can_go_left;       // czy postaæ mo¿e iœæ w lewo
	bool m_can_go_right;      // czy postaæ mo¿e iœæ w prawo
};

