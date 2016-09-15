#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "SpriteLoader.h"
#include "Collisions.h"
#include "Level.h"

class Character :
	public Field,public SpriteLoader
{
public:
	Character(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, double def_velocity_x, double def_velocity_y,
		double def_acceleration_x = 0, double def_acceleration_y = 0) :
		Field::Field(x1, y1, exist1, type1, layer1,hp1),
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
		m_can_go_right(true),
		hp(hp1)
	{
		SetDefaultMovement();
	}
	virtual TYPES::FieldType GetType()   = 0;
	virtual int GetScoresWhenKilled()   { return 0; }
	 void Update(double dt,Level * p_level);
	void Draw();
	void setSprite(Sprite & data, std::string name, TYPES::CharacterState state);
	bool IsDead()   { return m_is_dead; }
	bool IsAlive()   { return !m_is_dead; }
	void SetIsDead(bool is_dead = true) { m_is_dead = is_dead; }
	void KilledByPlayer();
	void KilledWithBullet();

	// zarz¹dzanie po³o¿eniem 

	virtual double GetNextXPosition(double dt)   { return m_x + GetNextXVelocity(dt) * dt; }
	virtual double GetNextYPosition(double dt)   { return m_y + GetNextYVelocity(dt) * dt; }
	

	// zarz¹dzanie prêdkoœci¹
	double GetXVelocity()   { return m_vx; }
	double GetYVelocity()   { return m_vy; }
	double GetNextXVelocity(double dt)   { return m_vx + m_ax * dt; }
	double GetNextYVelocity(double dt)   { return m_vy + m_ay * dt; }
	double GetDefaultXVelocity()   { return m_default_velocity_x; }
	double GetDefaultYVelocity()   { return m_default_velocity_y; }
	void  NegateXVelocity() { m_vx = -m_vx; }
	void  NegateYVelocity() { m_vy = -m_vy; }
	void  NegateVelocity() { NegateXVelocity(); NegateYVelocity(); }
	void  SetXVelocity(double velocity) { m_vx = velocity; }
	void  SetYVelocity(double velocity) { m_vy = velocity; }
	void  SetVelocity(double vx, double vy) { m_vx = vx; m_vy = vy; }

	// zarz¹dzanie przyspieszeniem
	double GetXAcceleration()   { return m_ax; }
	double GetYAcceleration()   { return m_ay; }
	double GetDefaultXAcceleration()   { return m_default_acceleration_x; }
	double GetDefaultYAcceleration()   { return m_default_acceleration_y; }
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
	virtual void CheckCollisionsWithLevel(double dt, Level * p_level) = 0;
	bool IsAnyFieldAboveMe(double x, double y, double dt, Level * p_level);
	bool IsAnyFieldBelowMe(double x, double y, double dt, Level * p_level);
	bool IsAnyFieldOnLeft(double x, double y, double dt, Level * p_level);
	bool IsAnyFieldOnRight(double x, double y, double dt, Level * p_level);
	bool DoFieldsEndOnLeft(double x, double y, double dt, Level * p_level);
	bool DoFieldsEndOnRight(double x, double y, double dt, Level * p_level);

	void EntityOnGround() {
		m_is_on_ground = true;
		m_vy = 0;
	}

	// prostok¹t otaczaj¹cy jednostkê bez uwzglêdniania pozycji jednostki
	virtual Collisions GetBasicAabb()   { return Collisions(0, 0, 1, 1); }

	Collisions GetAabb()   { return GetBasicAabb().Move(m_x, m_y, m_x, m_y); }

	Collisions GetNextHorizontalAabb(double dt)   {
		return GetBasicAabb().Move(GetNextXPosition(dt), m_y, GetNextXPosition(dt), m_y);
	}

	Collisions GetNextVerticalAabb(double dt)   {
		return GetBasicAabb().Move(m_x, GetNextYPosition(dt), m_x, GetNextYPosition(dt));
	}

	Collisions GetNextAabb(double dt)   {
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

#endif