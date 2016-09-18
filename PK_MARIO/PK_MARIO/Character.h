#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "SpriteLoader.h"
#include "Collisions.h"
#include "Level.h"

/// <summary>	A abstract class character. </summary>
class Character :
	public Field,public SpriteLoader
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
	/// <param name="hp1">				 	The  hp. </param>
	/// <param name="def_velocity_x">	 	The definition velocity x coordinate. </param>
	/// <param name="def_velocity_y">	 	The definition velocity y coordinate. </param>
	/// <param name="def_acceleration_x">	(Optional) The definition acceleration x coordinate. </param>
	/// <param name="def_acceleration_y">	(Optional) The definition acceleration y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

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

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The type. </returns>
	///-------------------------------------------------------------------------------------------------

	virtual TYPES::FieldType GetType()   = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets scores when killed. </summary>
	///
	/// <returns>	The scores when killed. </returns>
	///-------------------------------------------------------------------------------------------------

	virtual int GetScoresWhenKilled();

	 ///-------------------------------------------------------------------------------------------------
	 /// <summary>	Updates this object. </summary>
	 ///
	 /// <param name="dt">	   	The delta time. </param>
	 /// <param name="p_level">	[in,out] If non-null, the level. </param>
	 ///-------------------------------------------------------------------------------------------------

	 void Update(double dt,Level * p_level);
	/// <summary>	Draws this object. </summary>
	void Draw();
	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is dead. </summary>
	///
	/// <returns>	true if dead, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsDead();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is alive. </summary>
	///
	/// <returns>	true if alive, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsAlive();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets is dead. </summary>
	///
	/// <param name="is_dead">	(Optional) True if this object is dead. </param>
	///-------------------------------------------------------------------------------------------------

	void SetIsDead(bool is_dead = true);
	/// <summary>	Killed by player. </summary>
	void KilledByPlayer();
	/// <summary>	Killed with bullet. </summary>
	void KilledWithBullet();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next x coordinate position. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next x coordinate position. </returns>
	///-------------------------------------------------------------------------------------------------

	virtual double GetNextXPosition(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next y coordinate position. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next y coordinate position. </returns>
	///-------------------------------------------------------------------------------------------------

	virtual double GetNextYPosition(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get x coordinate velocity. </summary>
	///
	/// <returns>	The x coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetXVelocity();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get y coordinate velocity. </summary>
	///
	/// <returns>	The y coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetYVelocity();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next x coordinate velocity. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next x coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetNextXVelocity(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next y coordinate velocity. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next y coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetNextYVelocity(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets default x coordinate velocity. </summary>
	///
	/// <returns>	The default x coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetDefaultXVelocity();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets default y coordinate velocity. </summary>
	///
	/// <returns>	The default y coordinate velocity. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetDefaultYVelocity();
	/// <summary>	Negate x coordinate velocity. </summary>
	void  NegateXVelocity();
	/// <summary>	Negate y coordinate velocity. </summary>
	void  NegateYVelocity();
	/// <summary>	Negate velocity. </summary>
	void  NegateVelocity();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets x coordinate velocity. </summary>
	///
	/// <param name="velocity">	The velocity. </param>
	///-------------------------------------------------------------------------------------------------

	void  SetXVelocity(double velocity);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets y coordinate velocity. </summary>
	///
	/// <param name="velocity">	The velocity. </param>
	///-------------------------------------------------------------------------------------------------

	void  SetYVelocity(double velocity);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a velocity. </summary>
	///
	/// <param name="vx">	The vx. </param>
	/// <param name="vy">	The vy. </param>
	///-------------------------------------------------------------------------------------------------

	void  SetVelocity(double vx, double vy);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get x coordinate acceleration. </summary>
	///
	/// <returns>	The x coordinate acceleration. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetXAcceleration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get y coordinate acceleration. </summary>
	///
	/// <returns>	The y coordinate acceleration. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetYAcceleration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets default x coordinate acceleration. </summary>
	///
	/// <returns>	The default x coordinate acceleration. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetDefaultXAcceleration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets default y coordinate acceleration. </summary>
	///
	/// <returns>	The default y coordinate acceleration. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetDefaultYAcceleration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets x coordinate acceleration. </summary>
	///
	/// <param name="accel">	The acceleration. </param>
	///-------------------------------------------------------------------------------------------------

	void  SetXAcceleration(double accel);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets y coordinate acceleration. </summary>
	///
	/// <param name="accel">	The acceleration. </param>
	///-------------------------------------------------------------------------------------------------

	void  SetYAcceleration(double accel);

	
	/// <summary>	Go left. </summary>
	virtual void GoLeft();
	/// <summary>	Go right. </summary>
	virtual void GoRight();
	/// <summary>	Stops a left. </summary>
	virtual void StopLeft();
	/// <summary>	Stops a right. </summary>
	virtual void StopRight();
	/// <summary>	Stops a movement. </summary>
	virtual void StopMovement();
	/// <summary>	Forbid going left. </summary>
	void ForbidGoingLeft();
	/// <summary>	Forbid going right. </summary>
	void ForbidGoingRight();
	/// <summary>	Falls this object. </summary>
	void Fall();
	/// <summary>	Sets default movement. </summary>
	virtual void SetDefaultMovement();
	/// <summary>	Character on ground. </summary>
	void CharacterOnGround();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collisions with level. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	virtual void CheckCollisionsWithLevel(double dt, Level * p_level) = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is any field above me. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if any field above me, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsAnyFieldAboveMe(double x, double y, double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is any field below me. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if any field below me, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsAnyFieldBelowMe(double x, double y, double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is any field on left. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if any field on left, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsAnyFieldOnLeft(double x, double y, double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is any field on right. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if any field on right, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsAnyFieldOnRight(double x, double y, double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes the fields end on left operation. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------

	bool DoFieldsEndOnLeft(double x, double y, double dt, Level * p_level);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes the fields end on right operation. </summary>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="y">	  	The y coordinate. </param>
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------

	bool DoFieldsEndOnRight(double x, double y, double dt, Level * p_level);

	/// <summary>	Entity on ground. </summary>
	void EntityOnGround();

	// prostok¹t otaczaj¹cy jednostkê bez uwzglêdniania pozycji jednostki
	virtual Collisions GetBasicAabb();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the aabb collision. </summary>
	///
	/// <returns>	The aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetAabb();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next horizontal aabb collision. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next horizontal aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetNextHorizontalAabb(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next vertical aabb collision. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next vertical aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetNextVerticalAabb(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the next aabb collision. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	The next aabb collision. </returns>
	///-------------------------------------------------------------------------------------------------

	Collisions GetNextAabb(double dt);


protected:
	/// <summary>	The default velocity of x coordinat.. </summary>
	double m_default_velocity_x;
	/// <summary>	The default velocity of y coordinate. </summary>
	double m_default_velocity_y;
	/// <summary>	The default acceleration of x coordinate. </summary>
	double m_default_acceleration_x;
	/// <summary>	The default acceleration of y coordinate. </summary>
	double m_default_acceleration_y;

	/// <summary>	true if this object is dead. </summary>
	bool m_is_dead;         
	/// <summary>	The state. </summary>
	TYPES::CharacterState m_state;  
	/// <summary>	The left. </summary>
	Sprite * m_left;         
	/// <summary>	The right. </summary>
	Sprite * m_right;        
	/// <summary>	The stop. </summary>
	Sprite * m_stop;         

	/// <summary>	The hp of character. </summary>
	int hp;
	/// <summary>	velocity of x coordinate. </summary>
	double m_vx;              
	/// <summary>	velocity of z coordinate. </summary>
	double m_vy;             
	/// <summary>	acceleration of x coordinate. </summary>
	double m_ax;             
	/// <summary>	acceleration of y coordinate. </summary>
	double m_ay;             
	/// <summary>	true if this object is on ground. </summary>
	bool m_is_on_ground;      
	/// <summary>	true if this object can go left. </summary>
	bool m_can_go_left;     
	/// <summary>	true if this object can go right. </summary>
	bool m_can_go_right;     
};

#endif