#pragma once
#include "Character.h"
class Player :
	public Character
{
private:
	enum
	{
		DefaultYVelocity = 20, DefaultYAcceleration = -60
	};

	/// <summary>	The state of annimation. </summary>
	TYPES::PlayerState m_state;
	/// <summary>	The left state. </summary>
	Sprite *  m_left;

	/// <summary>	The right state. </summary>
	Sprite *   m_right;

	/// <summary>	The stop state. </summary>
	Sprite * m_stop;


	/// <summary>	The x speed of player. </summary>
	double m_vx;


	/// <summary>	The y speed of player. </summary>
	double m_vy;

	/// <summary>	The accelerate of player. </summary>
	double m_ay;

	/// <summary>	The running factor. </summary>
	double m_running_factor;

	/// <summary>	true to allow, false to deny jump. </summary>
	bool m_jump_allowed;

	/// <summary>	Width of the level. </summary>
	size_t m_level_width;

	/// <summary>	true if this object is on ground. </summary>
	bool m_is_on_ground;

	/// <summary>	true if this object can go left. </summary>
	bool m_can_go_left;

	/// <summary>	true if this object can go right. </summary>
	bool m_can_go_right;
	bool move(int direction);
	bool jump();
	bool fire();
	double m_max_x_pos;
public:
	Player(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, double speed1, size_t level_width) :
		Character::Character(x1, y1, exist1, type1, layer1, hp1, speed1), m_state(TYPES::Standing),
		m_vx(0.0),
		m_vy(0),
		m_ay(DefaultYAcceleration),
		m_running_factor(1.0),
		m_jump_allowed(true),
		m_level_width(level_width),
		m_is_on_ground(true),
		m_can_go_left(true),
		m_can_go_right(true),
		m_max_x_pos(x)
	{
		SetDefaultMoving();
	};
	double GetDefaultYVelocity()     const
	{
		return DefaultYVelocity;
	}

	/// <summary>	Gets default y coordinate acceleration. </summary>
	///
	/// <returns>	The default y coordinate acceleration. </returns>
	double GetDefaultYAcceleration() const
	{
		return DefaultYAcceleration;
	}


	/// <summary>	Runing of object </summary>
	void Run()
	{
		m_running_factor = 2.0;
	}

	/// <summary>	Stops a running. </summary>
	void StopRunning()
	{
		m_running_factor = 1.0;
	}

	/// <summary>	Go left. </summary>
	void GoLeft()
	{
		m_vx -= 4.0; m_state = TYPES::GoingLeft;
	}

	/// <summary>	Go right. </summary>
	void GoRight()
	{
		m_vx += 4.0; m_state = TYPES::GoingRight;
	}

	/// <summary>	Stops a left. </summary>
	void StopLeft()
	{
		m_vx += 4.0; m_state = TYPES::Standing;
	}


	/// <summary>	Stops a right. </summary>
	void StopRight()
	{
		m_vx -= 4.0; m_state = TYPES::Standing;
	}


	/// <summary>	Forbid going left. </summary>
	void ForbidGoingLeft()
	{
		m_can_go_left = false;
	}

	/// <summary>	Forbid going right. </summary>
	void ForbidGoingRight()
	{
		m_can_go_right = false;
	}

	/// <summary>	Falls this object. </summary>
	void Fall()
	{
		m_vy = 0.0; m_is_on_ground = false;
	}

	/// <summary>	Jumps the given y coordinate velocity. </summary>
	///
	/// <param name="y_velocity">	(Optional) the velocity. </param>

	void Jump(double y_velocity = DefaultYVelocity);

	/// <summary>	Allow to jump. </summary>
	void AllowToJump()
	{
		m_jump_allowed = true;
	}

	/// <summary>	Forbid to jump. </summary>
	void ForbidToJump()
	{
		m_jump_allowed = false;
	}

	/// <summary>	Sets default moving. </summary>
	void SetDefaultMoving()
	{
		m_is_on_ground = false; m_can_go_right = m_can_go_left = true;
	}

	/// <summary>	Player on ground. </summary>
	void PlayerOnGround()
	{
		m_is_on_ground = m_jump_allowed = true;
		m_vy = 0;
	}

	/// <summary>	Gets the next x coordinate position. </summary>
	///
	/// <param name="dt">	The dt. </param>
	///
	/// <returns>	The next x coordinate position. </returns>

	double GetNextXPosition(double dt) const
	{
		return x + m_vx * dt * m_running_factor;
	}

	/// <summary>	Gets the next y coordinate position. </summary>
	///
	/// <param name="dt">	The dt. </param>
	///
	/// <returns>	The next y coordinate position. </returns>
	double GetNextYPosition(double dt) const
	{
		return y + (m_vy + m_ay * dt) * dt;
	}


	bool Player::MoveMap() {
		const size_t screen_tiles_count =SpriteRenderer().GetHorizontalTilesOnScreenCount();
		const size_t half_screen_tiles_count = screen_tiles_count / 2;
		
		return( (x > half_screen_tiles_count-1) && (x < ((m_level_width-1) - half_screen_tiles_count)));
	}

	~Player();
	void setSprite(Sprite & data, std::string name,TYPES::PlayerState state);
	bool draw();
	void Update(double dt);

};

