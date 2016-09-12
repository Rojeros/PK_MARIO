#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "Tile.h"
#include "Bonus.h"
#include "Character.h"
#include "Monster.h"
#include "Player.h"

#include <list>
#include <vector>

class GameContener
{
private:
	std::vector<std::vector<Tile> > map;
	std::vector< std::vector< Tile *> > m_grid;
	size_t m_width;
	size_t m_height;
	size_t grid_width;
	size_t grid_height;

public:
	
	GameContener() : m_width(0),m_height(0) 
	{
	};

	void LoadLevelFromFile(const std::string& filename);
	TYPES::FieldType Field(size_t x, size_t y);
	void SetLevel(double dx);
	void DrawLevel(double dx);

	size_t GetWidth() const { return m_width; }
	size_t GetHeight() const { return m_height; }
	~GameContener();
};

