#pragma once
#include "StdAfx.h"
#include "Sprite.h"
#include <map>
class SpriteLoader
{
public:
	SpriteLoader();
	Sprite* Get(std::string name);
	bool Contains(std::string name) ;
	void Insert(std::string name, Sprite& data);
protected:
	std::map<std::string, Sprite> m_data;

};
typedef boost::shared_ptr<SpriteLoader> SpriteLoaderPtr;

