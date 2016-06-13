#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "StdAfx.h"
#include "Sprite.h"
#include "Types.h"
#include "Engine.h"


class Player {
public:
	explicit Player(double x, double y, size_t level_width);

	void SetSprites(SpritePtr left, SpritePtr right, SpritePtr stop);
	void Update(double dt);
	void Draw() const;

	double GetX() const { return m_x; }
	double GetY() const { return m_y; }
	double GetDefaultYVelocity()     const { return DefaultYVelocity; }
	double GetDefaultYAcceleration() const { return DefaultYAcceleration; }

	void Run() { m_running_factor = 2.0; }
	void StopRunning() { m_running_factor = 1.0; }
	void GoLeft() { m_vx -= 4.0; m_state = PS::GoLeft; }
	void GoRight() { m_vx += 4.0; m_state = PS::GoRight; }
	void StopLeft() { m_vx += 4.0; m_state = PS::Stand; }
	void StopRight() { m_vx -= 4.0; m_state = PS::Stand; }
	void ForbidGoingLeft() { m_can_go_left = false; }
	void ForbidGoingRight() { m_can_go_right = false; }
	void Fall() { m_vy = 0.0; m_is_on_ground = false; }
	void Jump(double y_velocity = DefaultYVelocity);
	void AllowToJump() { m_jump_allowed = true; }
	void ForbidToJump() { m_jump_allowed = false; }
	void SetDefaultMoving() { m_is_on_ground = false; m_can_go_right = m_can_go_left = true; }
	void PlayerOnGround() {
		m_is_on_ground = m_jump_allowed = true;
		m_vy = 0;
	}

	double GetNextXPosition(double dt) const { return m_x + m_vx * dt * m_running_factor; }
	double GetNextYPosition(double dt) const { return m_y + (m_vy + m_ay * dt) * dt; }

	bool MoveMap() {
		const size_t screen_tiles_count = Engine::Get().GetRenderer()->GetHorizontalTilesOnScreenCount();
		const size_t half_screen_tiles_count = screen_tiles_count / 2;
		return true;
	}


private:
	enum { DefaultYVelocity = 20, DefaultYAcceleration = -60 };

	PS::PlayerState m_state;  // stan, w kt�rym znajduje si� posta�
	SpritePtr m_left;         // animacja, kiedy posta� idzie w lewo
	SpritePtr m_right;        // animacja, kiedy posta� idzie w prawo
	SpritePtr m_stop;         // animacja, kiedy posta� stoi
	double m_x;               // po�o�enie postaci na osi odci�tych
	double m_y;               // po�o�enie postaci na osi rz�dnych
	double m_vx;              // pr�dko�� na osi OX
	double m_vy;              // pr�dko�� gracza w pionie
	double m_ay;              // przyspieszenie gracza w pionie
	double m_running_factor;  // wsp�czynnik biegania. >1.0 => biegnie, <1.0 => spowolnienie
	bool m_jump_allowed;      // czy gracz mo�e skaka� (np. jest na pod�o�u)
	size_t m_level_width;     // szeroko�� poziomu (w kaflach)
	bool m_is_on_ground;      // czy posta� jest na pod�o�u
	bool m_can_go_left;       // czy posta� mo�e i�� w lewo
	bool m_can_go_right;      // czy posta� mo�e i�� w prawo

};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif
