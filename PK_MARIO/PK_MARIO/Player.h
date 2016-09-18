#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "Character.h"
#include "Monster.h"
/// <summary>	A player class represents player on screen. </summary>
class Player :
	public Character
{
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x1">	 	x coord on map. </param>
	/// <param name="y1">	 	y coord on map.</param>
	/// <param name="exist1">	true if exist on map. </param>
	/// <param name="type1"> 	type of field. </param>
	/// <param name="layer1">	layer on screen. </param>
	/// <param name="hp1">		  	The  hp. </param>
	/// <param name="level_width">	Width of the level. </param>
	///-------------------------------------------------------------------------------------------------

	Player(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, int hp1, size_t level_width) :
		Character(x1, y1, exist1, type1, layer1, hp1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration),
		m_state(TYPES::Stand),
		m_running_factor(1.0),
		m_jump_allowed(true),
		m_level_width(level_width),
		m_total_scores(0),
		m_is_immortal(false),
		m_is_level_completed(false),
		bulletShooted(false)
	 {
		SetDefaultMovement();
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The TYPES::Players;. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType GetType();
	 /// <summary>	Go left. </summary>
	 void GoLeft();
	 /// <summary>	Go right. </summary>
	 void GoRight();
	 /// <summary>	Stops a left. </summary>
	 void StopLeft();
	 /// <summary>	Stops a right. </summary>
	 void StopRight();
	 /// <summary>	Stops a movement. </summary>
	 void StopMovement();
	 /// <summary>	Turn left. </summary>
	 void TurnLeft();
	 /// <summary>	Turn right. </summary>
	 void TurnRight();
	 /// <summary>	Allow to jump. </summary>
	 void AllowToJump();
	 /// <summary>	Forbid to jump. </summary>
	 void ForbidToJump();
	 /// <summary>	Runs this object. </summary>
	 void Run();
	 /// <summary>	Stops a running. </summary>
	 void StopRunning();

	 ///-------------------------------------------------------------------------------------------------
	 /// <summary>	Gets running factor. </summary>
	 ///
	 /// <returns>	The running factor. </returns>
	 ///-------------------------------------------------------------------------------------------------

	 double GetRunningFactor();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Jumps the given y coordinate velocity. </summary>
	///
	/// <param name="y_velocity">	(Optional) The velocity. </param>
	///-------------------------------------------------------------------------------------------------

	void Jump(double y_velocity = DefaultYVelocity);
	/// <summary>	Sets default movement. </summary>
	void SetDefaultMovement();
	/// <summary>	Player on ground. </summary>
	void PlayerOnGround();
	/// <summary>	Adds live. </summary>
	void addLive();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next x coordinate position on screen. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next x coordinate position on screen. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetNextXPosition(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets basic aabb collision. </summary>
	///
	/// <returns>	The basic aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetBasicAabb();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collisions with level. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckCollisionsWithLevel(double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Adds the scores. </summary>
	///
	/// <param name="scores">	The scores. </param>
	///-------------------------------------------------------------------------------------------------

	void AddScores(int scores);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the scores. </summary>
	///
	/// <returns>	The scores. </returns>
	///-------------------------------------------------------------------------------------------------

	int  GetScores();

	
	/// <summary>	Fire bullet. </summary>
	void FireBullet();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is bullet fired. </summary>
	///
	/// <returns>	true if bullet fired, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool isBulletFired();
	/// <summary>	Disables the bullet. </summary>
	void DisableBullet();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the state of animation. </summary>
	///
	/// <returns>	The state of animation. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::PlayerState GetState();
	/// <summary>	Draws this object. </summary>
	void Draw();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets lifes count. </summary>
	///
	/// <returns>	The lifes count. </returns>
	///-------------------------------------------------------------------------------------------------

	int GetLifesCount();

	/// <summary>	Loose life. </summary>
	void LooseLife();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Level completed. </summary>
	///
	/// <param name="status">	Sets the level status </param>
	///-------------------------------------------------------------------------------------------------

	void LevelCompleted(bool status);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is level completed. </summary>
	///
	/// <returns>	true if level completed, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsLevelCompleted();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object has completed current level. </summary>
	///
	/// <returns>	true if completed current level, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool HasCompletedCurrentLevel();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Collision right. </summary>
	///
	/// <param name="it">	[in,out] If non-null, the iterator. </param>
	///-------------------------------------------------------------------------------------------------

	void CollisionOnRight(std::vector<Character*>::iterator it);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Collision left. </summary>
	///
	/// <param name="it">	[in,out] If non-null, the iterator. </param>
	///-------------------------------------------------------------------------------------------------

	void CollisionOnLeft(std::vector<Character*>::iterator it);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Collision over player. </summary>
	///
	/// <param name="it">	[in,out] If non-null, the iterator. </param>
	///-------------------------------------------------------------------------------------------------

	void CollisionOverPlayer(std::vector<Character*>::iterator it);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Collision under player. </summary>
	///
	/// <param name="it">	[in,out] If non-null, the iterator. </param>
	///-------------------------------------------------------------------------------------------------

	void CollisionUnderPlayer(std::vector<Character*>::iterator it);


	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is immortal. </summary>
	///
	/// <returns>	true if immortal, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsImmortal();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Determines if we can move map. </summary>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------

	bool Player::MoveMap();

	/// <summary>	Destructor. </summary>
	~Player() {};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates this object. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void Update(double dt,Level*p_level);

private:
	/// <summary>	Values that represent default moving system. </summary>

	enum {
		DefaultXVelocity = 4, DefaultYVelocity = 20,
		DefaultXAcceleration = 0, DefaultYAcceleration = -60,
		DefaultLifesCount = 3
	};

	/// <summary>	The state of annimation. </summary>
	TYPES::PlayerState m_state;  
	/// <summary>	The running factor. </summary>
	double m_running_factor;  
	/// <summary>	true to allow, false to deny jump. </summary>
	bool m_jump_allowed;      
	/// <summary>	Width of the level. </summary>
	size_t m_level_width;     

	/// <summary>	The total scores. </summary>
	int m_total_scores;       
	/// <summary>	true if this object is immortal. </summary>
	bool m_is_immortal;       
	/// <summary>	Duration of the immortal. </summary>
	double m_immortal_duration;  
	/// <summary>	true if bullet shooted. </summary>
	bool bulletShooted;
	/// <summary>	true if this object is level completed. </summary>
	bool m_is_level_completed;   


};

#endif