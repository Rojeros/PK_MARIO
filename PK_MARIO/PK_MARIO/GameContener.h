#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "Tile.h"
#include "Bonus.h"
#include "Character.h"
#include "Monster.h"
#include "Player.h"
#include "Text.h"
#include "Collisions.h"

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

	Player * m_player;
	Text t;
	/// <summary>	The stored player position x coordinate. </summary>
	double m_stored_player_pos_x;

	bool IsAnyFieldAboveMe(double x, double y,double dt) ;
	bool IsAnyFieldBelowMe(double x, double y, double dt);
	bool IsAnyFieldOnLeft(double x, double y, double dt) ;
	bool IsAnyFieldOnRight(double x, double y, double dt) ;
	bool DoFieldsEndOnLeft(double x, double y, double dt) ;
	bool DoFieldsEndOnRight(double x, double y, double dt) ;
	void CheckCollisionsWithLevel(double dt);

public:
	
	GameContener() : m_width(0),m_height(0) ,	m_stored_player_pos_x(1.0)
	{
	};

	void LoadLevelFromFile(const std::string& filename);
	TYPES::FieldType Field(size_t x, size_t y);
	void SetLevel(double dx);
	void SetPlayer();
	void DrawLevel(double dx);
	void DrawScene();
	void UpdateScene(double dt);
	Player * GetPLayer();
	size_t GetWidth() const { return m_width; }
	size_t GetHeight() const { return m_height; }

	~GameContener() {
		delete m_player;
	};
};

