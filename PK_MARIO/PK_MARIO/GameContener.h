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
	int numberOfLevel;
	int levels;
	Level * p_level;
	Player * m_player;
	Text t;
	/// <summary>	The stored player position x coordinate. </summary>
	double m_stored_player_pos_x;
	int m_stored_player_live;
	std::vector< std::vector<LevelEntityData>>  m_entities_to_create;
	void LoadEntitiesFromFile(const std::string& filename);


public:
	
	GameContener() : 	m_stored_player_pos_x(1.0)
	{
		t.SetTimer(5);
		LoadEntitiesFromFile("data\\init");
	};

	void deleteList();
	void SetPlayer();
	void DrawScene();
	void UpdateScene(double dt);
	Player * GetPLayer();
	void addEnemy(double x, double y);
	void CheckPlayerEntitiesCollisions(double dt);
	void CheckCollisionOfOnePair(std::vector< Character* >::iterator fst_entity, TYPES::FieldType fst_type, std::vector<Character*>::iterator snd_entity, TYPES::FieldType snd_type,double dt);
	void CheckEntityEntityCollisions(double dt);
	bool IsMarkedToDelete(Character * o);
	void addBullet();
	void addBonus(double x, double y, TYPES::BonusType type1);
	bool isLevelcomplete();
	bool isLevelFaild();
	void Reset();
	void SetLevel();
	~GameContener() {
		delete m_player;
		delete p_level;
	};
};

#endif