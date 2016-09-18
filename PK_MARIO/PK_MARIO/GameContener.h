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

/// <summary>	A game contener, control all game procces. </summary>
class GameContener
{
private:
	
	/// <summary>	List of extra objects. </summary>
	std::vector<Character*> monsterList;
	/// <summary>	Number of current  level. </summary>
	int numberOfLevel;
	/// <summary>	The max level in game. </summary>
	int levels;
	/// <summary>	The pointer to level. </summary>
	Level * p_level;
	/// <summary>	The pointer to player. </summary>
	Player * m_player;
	/// <summary>	The Text objects, to display text. </summary>
	Text t;
	/// <summary>	The stored player position x coordinate, uses to set grid of level. </summary>
	double m_stored_player_pos_x;
	/// <summary>	The stored player live to check  when he dies. </summary>
	int m_stored_player_live;
	/// <summary>	The entities to create on level. </summary>
	std::vector< std::vector<LevelEntityData>>  m_entities_to_create;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Loads entities from file. </summary>
	///
	/// <param name="filename">	Filename of the file. </param>
	///-------------------------------------------------------------------------------------------------

	void LoadEntitiesFromFile(const std::string& filename);

	/// <summary>	Deletes the list. </summary>
	void deleteList();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Adds an enemy to list. </summary>
	///
	/// <param name="x">	The x coordinate. </param>
	/// <param name="y">	The y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void addEnemy(double x, double y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check player entities collisions. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckPlayerEntitiesCollisions(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check collision of one pair. </summary>
	///
	/// <param name="fst_entity">	[in,out] If non-null, the fst entity. </param>
	/// <param name="fst_type">  	Type of the fst. </param>
	/// <param name="snd_entity">	[in,out] If non-null, the sound entity. </param>
	/// <param name="snd_type">  	Type of the sound. </param>
	/// <param name="dt">		 	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckCollisionOfOnePair(std::vector< Character* >::iterator fst_entity, TYPES::FieldType fst_type, std::vector<Character*>::iterator snd_entity, TYPES::FieldType snd_type, double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Check entity collisions. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void CheckEntityEntityCollisions(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if 'o' is marked to delete. </summary>
	///
	/// <param name="o">	[in,out] If non-null, the Character to process. </param>
	///
	/// <returns>	true if marked to delete, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsMarkedToDelete(Character * o);
	/// <summary>	Adds bullet. </summary>
	void addBullet();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Adds the bonus. </summary>
	///
	/// <param name="x">		The x coordinate. </param>
	/// <param name="y">		The y coordinate. </param>
	/// <param name="type1">	The first type. </param>
	///-------------------------------------------------------------------------------------------------

	void addBonus(double x, double y, TYPES::BonusType type1);
	/// <summary>	Sets the level. </summary>
	void SetLevel();

public:
	/// <summary>	Default constructor. </summary>
	GameContener() : m_stored_player_pos_x(1.0)
	{
		t.SetTimer(5);
		LoadEntitiesFromFile("data\\init");
	};

	/// <summary>	Destructor. </summary>
	~GameContener() {
		delete m_player;
		delete p_level;
		for (int i = 0; i < monsterList.size(); i++)
			delete monsterList[i];
	};
	/// <summary>	Sets the player. </summary>
	void SetPlayer();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets pointer to player. </summary>
	///
	/// <returns>	null if it fails, else the pointer to player. </returns>
	///-------------------------------------------------------------------------------------------------

	Player * GetPLayer();
	/// <summary>	Draw scene. </summary>
	void DrawScene();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates the scene described by dt. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void UpdateScene(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is levelcomplete. </summary>
	///
	/// <returns>	true if levelcomplete, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool isLevelcomplete();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is level faild. </summary>
	///
	/// <returns>	true if level faild, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool isLevelFaild();
	/// <summary>	Resets this object. </summary>
	void Reset();

};

#endif