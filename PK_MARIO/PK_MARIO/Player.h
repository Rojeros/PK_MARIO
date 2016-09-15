#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "Character.h"
#include "Monster.h"
class Player :
	public Character
{
public:
	Player(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, size_t level_width) :
		Character(x1, y1, exist1, type1, layer1, hp1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration),
		m_state(TYPES::Stand),
		m_running_factor(1.0),
		m_jump_allowed(true),
		m_level_width(level_width),
		m_total_scores(0),
		m_is_immortal(false),
		m_lifes(4),
		m_twin_shot_enabled(false),
		m_is_level_completed(false),
		m_max_x_pos(50) {
		SetDefaultMovement();
	}
		
	TYPES::FieldType GetType()   {
		throw std::logic_error("Gracz nie jest jednostk¹");
	}
	virtual void GoLeft() { m_vx -= GetDefaultXVelocity(); m_state = TYPES::GoLeft; }
	virtual void GoRight() { m_vx += GetDefaultXVelocity(); m_state = TYPES::GoRight; }
	virtual void StopLeft() { m_vx += GetDefaultXVelocity(); TurnLeft(); }
	virtual void StopRight() { m_vx -= GetDefaultXVelocity(); TurnRight(); }
	virtual void StopMovement() { m_vx = 0; m_state = TYPES::Stand; }
	void TurnLeft() { m_state = TYPES::TurnLeft; }
	void TurnRight() { m_state = TYPES::TurnRight; }
	void AllowToJump() { m_jump_allowed = true; }
	void ForbidToJump() { m_jump_allowed = false; }
	void Run() { m_running_factor = 2.0; }
	void StopRunning() { m_running_factor = 1.0; }
	double GetRunningFactor()   { return m_running_factor; }
	void Jump(double y_velocity = DefaultYVelocity);
	void SetDefaultMovement() {
		m_is_on_ground = m_jump_allowed = false;
		m_can_go_right = m_can_go_left = true;
	}
	void PlayerOnGround() {
		m_is_on_ground = m_jump_allowed = true;
		SetYVelocity(0);
	}

	double GetNextXPosition(double dt)   { return GetX() + GetXVelocity() * dt * GetRunningFactor(); }

	// prostok¹t otaczaj¹cy jednostkê bez uwzglêdniania jej pozycji
	Collisions GetBasicAabb()   { return Collisions(0, 0, .7, .9); }
	void CheckCollisionsWithLevel(double dt, Level * p_level);

	void AddScores(int scores) { m_total_scores += scores; }
	int  GetScores()   { return m_total_scores; }

	// wystrzel pocisk
	void FireBullet();
	void Draw();
	// zwraca liczbê ¿yæ bohatera
	int GetLifesCount()   { return hp; }

	// gracz straci³ ¿ycie - reakcja na zdarzenie
	void LooseLife();

	// akcja wywo³ywana. kiedy gracz zakoñczy poziom
	// (np. odegranie fanfarów, wyœwietlenia napisu, ...
	void LevelCompleted();

	bool HasCompletedCurrentLevel()   {
		return m_is_level_completed;
	}
	// obs³uga kolizji z ka¿dej strony
	void CollisionOnRight(std::vector<Monster>::iterator it);
	void CollisionOnLeft(std::vector<Monster>::iterator it);
	void CollisionOverPlayer(std::vector<Monster>::iterator it);
	void CollisionUnderPlayer(std::vector<Monster>::iterator it);


	void setSprite(Sprite & data, std::string name, TYPES::PlayerState state);
	bool IsImmortal()   { return m_is_immortal; }

	void EnableTwinShot() { m_twin_shot_enabled = true; }
	void DisableTwinShot() { m_twin_shot_enabled = false; }
	bool IsTwinShotEnabled()   { return m_twin_shot_enabled; }
	bool Player::MoveMap();

	~Player() {};
	void Update(double dt,Level*p_level);

private:
	enum {
		DefaultXVelocity = 4, DefaultYVelocity = 20,
		DefaultXAcceleration = 0, DefaultYAcceleration = -60,
		DefaultLifesCount = 3
	};

	TYPES::PlayerState m_state;  // stan, w którym znajduje siê postaæ
	double m_running_factor;  // wspó³czynnik biegania. >1.0 => biegnie, <1.0 => spowolnienie
	bool m_jump_allowed;      // czy gracz mo¿e skakaæ (np. jest na pod³o¿u)
	size_t m_level_width;     // szerokoœæ poziomu (w kaflach)

	int m_total_scores;       // ³¹czne zdobyte punkty
	bool m_is_immortal;       // czy jest nieœmiertelny
	double m_immortal_duration;  // czas przez który postaæ ju¿ jest nieœmiertelna
	int m_lifes;                 // liczba ¿yæ posiadanych przez postaæ

	bool m_twin_shot_enabled;    // czy upgrade twin shot jest dostêpny

	bool m_is_level_completed;   // czy aktualny poziom zosta³ zakoñczony

	double m_max_x_pos;
};

#endif