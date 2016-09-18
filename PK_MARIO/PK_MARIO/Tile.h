#ifndef TILE_H_
#define TILE_H_

#pragma once


#include "SpriteLoader.h"
#include "Field.h"
/// <summary>	A tile class represents single tile on screen </summary>
class Tile :
	public Field,public SpriteLoader
{
private:

	
	/// <summary>	The spriteleft. </summary>
	static Sprite * Spriteleft;
	/// <summary>	The sprite middle. </summary>
	static Sprite *SpriteMid;
	/// <summary>	The sprite right. </summary>
	static Sprite *SpriteRight;
	/// <summary>	The sprite no destruct. </summary>
	static Sprite *SpriteNoDestruct;
	/// <summary>	The spritepoiner. </summary>
	Sprite * Spritepoiner;
public:
	/// <summary>	Default constructor. </summary>
	Tile() :Field::Field(0, 0, false, TYPES::None, TYPES::Background,2)
	{};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="x1">	 	x coord on map. </param>
	/// <param name="y1">	 	y coord on map.</param>
	/// <param name="exist1">	true if exist on map. </param>
	/// <param name="type1"> 	type of field. </param>
	/// <param name="layer1">	layer on screen. </param>
	///-------------------------------------------------------------------------------------------------

	Tile(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :Field::Field(x1, y1, exist1, type1, layer1,2)
	{
	switch(type1){
	case TYPES::PlatformLeftEnd:
		Spritepoiner = Spriteleft;
		break;
	case TYPES::PlatformMidPart:
		Spritepoiner = SpriteMid;
		break;
	case TYPES::PlatformRightEnd:
		Spritepoiner = SpriteRight;
		break;
	case TYPES::NoDestroyAble:
		Spritepoiner = SpriteNoDestruct;
		break;
	case TYPES::None:
		break;
	default:
		throw "Tile constructor error";
		break;
	}
	};
	/// <summary>	Destructor. </summary>
	~Tile();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the type. </summary>
	///
	/// <returns>	The type(left,mid,right). </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType GetType();
	/// <summary>	Draws this object. </summary>
	void Draw();
	/// <summary>	Remove tail from map. </summary>
	void Destroy();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Changes the type of tile. </summary>
	///
	/// <param name="parameter1">	New type. </param>
	///-------------------------------------------------------------------------------------------------

	void Change(TYPES::FieldType type1);
	/// <summary>	Sets the sprite to objects. </summary>
	void SetSprite();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates this object. </summary>
	///
	/// <param name="dt">	  	The delta time. </param>
	/// <param name="p_level">	[in,out] If non-null, the level. </param>
	///-------------------------------------------------------------------------------------------------

	void Update(double dt,Level * p_level);
};

#endif