#ifndef LEVEL_H_
#define LEVEL_H_

#include "StdAfx.h"
#include "Tile.h"


/// <summary>	A level class, contains map of level costruct bz Tiles </summary>
class Level
{
private:
	/// <summary>	The width. </summary>
	size_t m_width;
	/// <summary>	The height. </summary>
	size_t m_height;
	/// <summary>	Width of the grid. </summary>
	size_t grid_width;
	/// <summary>	Height of the grid. </summary>
	size_t grid_height;


	/// <summary>	The map container for tiles. </summary>
	std::vector<std::vector<Tile> > map;
	/// <summary>	The grid, moves map with player,have size of screen . </summary>
	std::vector< std::vector< Tile *> > m_grid;
	
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the grid. </summary>
	///
	/// <returns>	null if it fails, else the grid. </returns>
	///-------------------------------------------------------------------------------------------------

	std::vector< std::vector< Tile *> >* GetGrid();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the map. </summary>
	///
	/// <returns>	null if it fails, else the map. </returns>
	///-------------------------------------------------------------------------------------------------

	std::vector<std::vector<Tile> > * GetMap();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Loads level from file. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///-------------------------------------------------------------------------------------------------

	void LoadLevelFromFile(const std::string& filename);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get types of fild on x,y coords. </summary>
	///
	/// <param name="x">	x coord. </param>
	/// <param name="y">	y coors. </param>
	///
	/// <returns>	A TYPES::FieldType. </returns>
	///-------------------------------------------------------------------------------------------------

	TYPES::FieldType Field(size_t x, size_t y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a grid from map. </summary>
	///
	/// <param name="dx">	The dx. </param>
	///-------------------------------------------------------------------------------------------------

	void SetLevel(double dx);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw level. </summary>
	///
	/// <param name="dx">	The dx. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawLevel(double dx);
	

	/// <summary>	Deletes the level. </summary>
	void deleteLevel();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the width. </summary>
	///
	/// <returns>	The width. </returns>
	///-------------------------------------------------------------------------------------------------

	size_t GetWidth();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the height. </summary>
	///
	/// <returns>	The height. </returns>
	///-------------------------------------------------------------------------------------------------

	size_t GetHeight();

	/// <summary>	Default constructor. </summary>
	Level() :m_width(0), m_height(0) 
	{
	
	};
	/// <summary>	Destructor. </summary>
	~Level() 
	{ 
		
		deleteLevel();
	};
};

#endif