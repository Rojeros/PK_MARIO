#include "StdAfx.h"
#include "SpriteLoader.h"
#include "SpriteData.h"
#include "Types.h"
std::map<std::string, Sprite> SpriteLoader:: m_data;

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

