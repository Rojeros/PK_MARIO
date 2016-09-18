#ifndef SPRITELOADER_H_
#define SPRITELOADER_H_


#pragma once
#include "StdAfx.h"
#include "Sprite.h"
#include <map>
/// <summary>	A sprite loader, get all Sprite info for objects. </summary>
class SpriteLoader
{
public:
	/// <summary>	Default constructor. </summary>
	SpriteLoader() {
		Sprite::setRenderer();
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets a sprite* using the given name. </summary>
	///
	/// <param name="name">	The name to get. </param>
	///
	/// <returns>	null if it fails, else a pointer to a Sprite. </returns>
	///-------------------------------------------------------------------------------------------------

	static Sprite* Get(std::string name);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object contains the given name. </summary>
	///
	/// <param name="name">	The std::string to test for containment. </param>
	///
	/// <returns>	true if the object is in this collection, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	static bool Contains(std::string name) ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Inserts. </summary>
	///
	/// <param name="name">	Insert a new Sprite. </param>
	/// <param name="data">	[in,out] The data. </param>
	///-------------------------------------------------------------------------------------------------

	static void Insert(std::string name, Sprite& data);
protected:
	/// <summary>	map contener, contains all sprites info. </summary>
	static std::map<std::string, Sprite> m_data;

};

#endif