#ifndef BONUS_H_
#define BONUS_H_
#pragma once
#include "Tile.h"
#include "Character.h"

/// <summary>	A bonus class describe bonuses for player on map. </summary>
class Bonus :
	public Character
{
private:
	/// <summary>	Type of the bonus(hp or end level). </summary>
	TYPES::BonusType bonusType;

	/// <summary>	The change direction x coordinate. </summary>
	int changeDirectionX;
	/// <summary>	The change direction y coordinate. </summary>
	int changeDirectionY;
	/// <summary>	The timer. </summary>
	double timer;

public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x1">	 	x coord on map. </param>
	/// <param name="y1">	 	y coord on map.</param>
	/// <param name="exist1">	true if exist on map. </param>
	/// <param name="type1"> 	type of field. </param>
	/// <param name="layer1">	layer on screen. </param>
	/// <param name="bonus"> 	The bonus type. </param>
	///-------------------------------------------------------------------------------------------------

	Bonus(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1, TYPES::BonusType bonus) :Character::Character(x1, y1, exist1, type1, layer1, 8, 8, 8), bonusType(bonus), changeDirectionX(1), changeDirectionY(-1), timer(0)
	{
		SetDefaultMovement();
	};
	/// <summary>	Default constructor. </summary>
	Bonus() :Character::Character(0, 0, 0, TYPES::Bonuses, TYPES::Background, 0, 0, 0), bonusType(TYPES::hp), changeDirectionX(1), changeDirectionY(-1), timer(0)
	{
	};
	/// <summary>	Destructor. </summary>
	~Bonus();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets bonus type. </summary>
	///
	/// <returns>	The bonus type. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::BonusType getBonusType();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	TYPES::BOnuses. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType GetType();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets basic Collision aabb collision. </summary>
	///
	/// <returns>	The basic aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetBasicAabb();

	/// <summary>	Sets default movement. </summary>
	void SetDefaultMovement();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next x coordinate position. </summary>
	///
	/// <param name="dt">	Change of time from last update. </param>
	///
	/// <returns>	The next x coordinate position. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetNextXPosition(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next y coordinate position. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next y coordinate position. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetNextYPosition(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collisions with level. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckCollisionsWithLevel(double dt, Level * p_level);

	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates this object. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void Update(double dt, Level* p_level);
	/// <summary>	Draws this object. </summary>
	void Draw();
};

#endif