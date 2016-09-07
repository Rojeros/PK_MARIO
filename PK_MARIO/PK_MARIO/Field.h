#pragma once
#include "StdAfx.h"

class Field
{
protected:
	TYPES::FieldType type;
	int x;
	int y;
	bool exist;
	TYPES::DisplayLayer layer;
	//powinna byæ jeszcze tekstura

	TYPES::FieldType returnType();
	void setCoord(int x1, int y1);
	int get_x();
	int get_y();
	void setExist(bool exist1);

public:
virtual	bool draw()=0;
virtual bool update()=0;
	bool isExist();

	Field(int x1, int y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :x(x1), y(y1), exist(exist1), type(type1), layer(layer1)
	{};
virtual	~Field();
};

