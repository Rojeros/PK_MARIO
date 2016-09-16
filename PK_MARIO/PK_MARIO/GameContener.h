#ifndef GAMECONTENER_H_
#define GAMECONTENER_H_

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
#include "Level.h"
#include <list>
#include <vector>
#include "Bonus.h"
#include "Bullet.h"

class GameContener
{
private:
	
	std::vector<Character*> monsterList;

	Level * p_level;
	Player * m_player;
	Text t;
	/// <summary>	The stored player position x coordinate. </summary>
	double m_stored_player_pos_x;
	int m_stored_player_live;
	
	

public:
	
	GameContener() : 	m_stored_player_pos_x(1.0)
	{
		t.SetTimer(5);
	};

	
	void SetPlayer();
	void DrawScene();
	void UpdateScene(double dt);
	Player * GetPLayer();
	void addEnemy(TYPES::FieldType monster);
	void CheckPlayerEntitiesCollisions(double dt);
	void CheckCollisionOfOnePair(std::vector< Character* >::iterator fst_entity, TYPES::FieldType fst_type, std::vector<Character*>::iterator snd_entity, TYPES::FieldType snd_type,double dt);
	void CheckEntityEntityCollisions(double dt);
	bool GameContener::IsMarkedToDelete(Character * o);
	void addBullet();

	~GameContener() {
		delete m_player;
		delete p_level;
	};
};

#endif