#ifndef MONSTER_H_
#define MONSTER_H_
#pragma once
#include "Character.h"

/// <summary>	A monster. </summary>
class Monster :public Character
{
	/// <summary>	Values that represent default moving system. </summary>
	enum {
		DefaultXVelocity = 2, DefaultYVelocity = 0, DefaultXAcceleration = 0, DefaultYAcceleration = -60
	};

public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x">	The x coordinate on screen. </param>
	/// <param name="y">	The y coordinate on screen.  </param>
	///-------------------------------------------------------------------------------------------------

	Monster(double x, double y) :
		Character(x, y, true, TYPES::Enemy, TYPES::Foreground, 1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration) {
	}
	/// <summary>	Default constructor. </summary>
	Monster() :
		Character(0, 0, false, TYPES::Enemy, TYPES::Foreground, 1, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration) {
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets scores when killed. </summary>
	///
	/// <returns>	The scores when killed. </returns>
	///-------------------------------------------------------------------------------------------------

	int GetScoresWhenKilled();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets basic aabb collision. </summary>
	///
	/// <returns>	The basic aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetBasicAabb();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The TYPES::Enemy. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType GetType();

	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collisions with level. </summary>
	///
	/// <param name="dt">   	The delta time. </param>
	/// <param name="level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckCollisionsWithLevel(double dt, Level*level);

};
#endif