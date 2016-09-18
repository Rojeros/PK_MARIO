#ifndef LEVEL_H_
#define LEVEL_H_

#include "StdAfx.h"
#include "Tile.h"


class Level
{
private:
	size_t m_width;
	size_t m_height;
	size_t grid_width;
	size_t grid_height;

	std::vector<std::vector<Tile> > map;
	std::vector< std::vector< Tile *> > m_grid;
	
public:
	std::vector< std::vector< Tile *> >* GetGrid();
	std::vector<std::vector<Tile> > * GetMap();
	void LoadLevelFromFile(const std::string& filename);
	
	TYPES::FieldType Field(size_t x, size_t y);
	void SetLevel(double dx);
	void DrawLevel(double dx);
	
	void deleteLevel();
	size_t GetWidth()   { return m_width; }
	size_t GetHeight()   { return m_height; }

	Level() :m_width(0), m_height(0) 
	{
	
	};
	~Level() 
	{ 
		
		deleteLevel();
	};
};

#endif