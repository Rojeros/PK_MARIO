#ifndef FIELD_H_
#define FIELD_H_
class Level;
#include "StdAfx.h"
#include "SpriteInserter.h"

/// <summary>	A field class. Its a base class for all system </summary>
class Field
{
protected:
	/// <summary>	The type. </summary>
	TYPES::FieldType type;

	/// <summary>	The x coordinate on the sreen. </summary>
	float m_x;	
	/// <summary>	The y coordinate on the sreen.. </summary>
	float m_y;
	/// <summary>	true if field exist and need to draw. </summary>
	bool exist;
	/// <summary>	The live of object. </summary>
	int hp;

	/// <summary>	The layer for draw. </summary>
	TYPES::DisplayLayer layer;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Returns the type of field. </summary>
	///
	/// <returns>	The type. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType returnType();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a coordinate on screen. </summary>
	///
	/// <param name="x1">	The first x value. </param>
	/// <param name="y1">	The first y value. </param>
	///-------------------------------------------------------------------------------------------------

	void setCoord(float x1, float y1);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets an exist. </summary>
	///
	/// <param name="exist1">	true to exist. </param>
	///-------------------------------------------------------------------------------------------------

	void setExist(bool exist1);

public:
/// <summary>	Draws this object. </summary>
virtual	void Draw()=0;

///-------------------------------------------------------------------------------------------------
/// <summary>	Updates this object. </summary>
///
/// <param name="dt">	  	The delta time. </param>
/// <param name="p_level">	[in,out] If non-null, the level. </param>
///-------------------------------------------------------------------------------------------------

virtual void Update(double dt, Level * p_level)=0;
/// <summary>	Sets the sprite to objects. </summary>
virtual void SetSprite()=0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is exist. </summary>
	///
	/// <returns>	true if exist, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool isExist();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets an x coordinate on the sreen.. </summary>
	///
	/// <param name="newx">	The newx. </param>
	///-------------------------------------------------------------------------------------------------

	void SetX(double newx);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a y coordinate on the sreen.. </summary>
	///
	/// <param name="newy">	The newy. </param>
	///-------------------------------------------------------------------------------------------------

	void SetY(double newy);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a position. </summary>
	///
	/// <param name="x">	The x coordinate. </param>
	/// <param name="y">	The y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void SetPosition(double x, double y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get x coordinate on the sreen.. </summary>
	///
	/// <returns>	The x coordinate on the sreen.. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetX();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get y coordinate on the sreen.. </summary>
	///
	/// <returns>	The y coordinate on the sreen.. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetY();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x1">	 	The  x coordinate on the sreen.. </param>
	/// <param name="y1">	 	The  y coordinate on the sreen.. </param>
	/// <param name="exist1">	true if exist and will be displayd on screen. </param>
	/// <param name="type1"> 	The  type of object. </param>
	/// <param name="layer1">	The  layer. </param>
	/// <param name="hp1">   	The  hp. </param>
	///-------------------------------------------------------------------------------------------------

	Field(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1,int hp1) :m_x(x1),m_y(y1), exist(exist1), type(type1), layer(layer1),hp(hp1)
	{
	};
	/// <summary>	Destructor. </summary>
	virtual	~Field();
};

#endif