#ifndef BULLET_H_
#define BULLET_H_

#include "StdAfx.h"
#include "Character.h"


/// <summary>	A bullet. </summary>
class Bullet :
	public Character
{

	/// <summary>	Values that represent default moving system. </summary>
	enum {
		DefaultXVelocity = 6, DefaultYVelocity = 0,
		DefaultXAcceleration = 0, DefaultYAcceleration = 0,
		DefaultTimeToLive = 2   
	};

public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x">			The x coordinate. </param>
	/// <param name="y">			The y coordinate. </param>
	/// <param name="xVelocity">	The x velocity. </param>
	/// <param name="yVelocity">	The y velocity. </param>
	///-------------------------------------------------------------------------------------------------

	Bullet(double x, double y, double xVelocity, double yVelocity) :
		Character(x, y, true, TYPES::PlayerBullet, TYPES::Foreground, 1, 0, 0,	0, 0),m_time_to_live(DefaultTimeToLive) 
	{

		m_vx = xVelocity < 0 ? -DefaultXVelocity : DefaultXVelocity;
		m_vy = DefaultYVelocity;
	}

	/// <summary>	Default constructor. </summary>
	Bullet() :Character(0, 0, 0, TYPES::PlayerBullet, TYPES::Foreground, 0, 0, 0) {}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the field type. </summary>
	///
	/// <returns>	TYPES::PlayerBullet. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType GetType();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets basic aabb collision. </summary>
	///
	/// <returns>	The basic aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetBasicAabb();

	/// <summary>	Sets default movement. </summary>
	void SetDefaultMovement();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates this object. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void Update(double dt, Level* p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collisions with level. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckCollisionsWithLevel(double dt, Level * p_level);

	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	/// <summary>	Draws this object. </summary>
	void Draw();


private:
	/// <summary>	The time to live. </summary>
	double m_time_to_live;  
};

#endif
