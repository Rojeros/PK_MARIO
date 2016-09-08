#pragma once
#include "StdAfx.h"
#include "Field.h"
#include "SpriteLoader.h"

class Character :
	public Field,public SpriteLoader
{
protected:
	int hp;
	double speed;
	
	virtual bool move(int direction) = 0;
	virtual bool jump()=0;
	virtual bool fire()=0;

public:
	Character(int x1, int y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1,int hp1,double speed1) :
		Field::Field(x1,y1,exist1, type1, layer1),hp(hp1),speed(speed1)
	{
	};
	bool draw();
	bool update();
	~Character();
};

