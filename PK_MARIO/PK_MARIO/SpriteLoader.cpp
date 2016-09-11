#include "StdAfx.h"
#include "SpriteLoader.h"
#include "SpriteData.h"
#include "Types.h"
std::map<std::string, Sprite> SpriteLoader:: m_data;


SpriteLoader::SpriteLoader()
{
	/*
	Insert("player_right", SpriteData(5, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer));
	Insert("player_left", SpriteData( 5, 0.2, 0, 5 * 32, 32, 32, true, TYPES::PlayerLayer));
	Insert("player_stop", SpriteData( 1, 0.2, 0, 6 * 32, 32, 32, true, TYPES::PlayerLayer));

	Insert("platform_left", SpriteData(1, 1, 0, 1 * 32, 32, 32, true, TYPES::PlayerLayer));
	Insert("platform_mid", SpriteData(1, 1, 0, 2 * 32, 32, 32, true, TYPES::PlayerLayer));
	Insert("platform_right", SpriteData(1, 1, 0, 3 * 32, 32, 32, true, TYPES::PlayerLayer));
	*/
}

Sprite* SpriteLoader::Get(std::string name) 
{
	if (Contains(name))
	{
		return &m_data.find(name)->second;
	}
	std::cerr << "Config not found: " << name << std::endl;
	throw("Config not found: " + name);
}

bool SpriteLoader::Contains( std::string name) 
{
	return (m_data.find(name) != m_data.end());
}

void SpriteLoader::Insert(std::string name,Sprite& data)
{
	m_data.insert(std::make_pair(name, data));
}

