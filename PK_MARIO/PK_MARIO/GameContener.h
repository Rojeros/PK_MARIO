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
	std::vector<std::vector<TYPES::FieldType> > map;

public:
	GameContener();
	~GameContener();
};

