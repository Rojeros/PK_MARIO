#ifndef SPRITELOADER_H_
#define SPRITELOADER_H_


#pragma once
#include "StdAfx.h"
#include "Sprite.h"
#include <map>
class SpriteLoader
{
public:
	SpriteLoader();
	static Sprite* Get(std::string name);
	static bool Contains(std::string name) ;
	static void Insert(std::string name, Sprite& data);
protected:
	static std::map<std::string, Sprite> m_data;

};

#endif