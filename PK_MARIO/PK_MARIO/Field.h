#pragma once
#include "StdAfx.h"

class Field
{
protected:
	TYPES::FieldType type;

	float m_x;	
	float m_y;
	bool exist;

	TYPES::DisplayLayer layer;

	TYPES::FieldType returnType();
	void setCoord(float x1, float y1);
	
	void setExist(bool exist1);

public:
virtual	void Draw()=0;
virtual void Update(double dt)=0;
	bool isExist();
	float get_x();
	float get_y();
	Field(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1) :m_x(x1),m_y(y1), exist(exist1), type(type1), layer(layer1)
	{};
virtual	~Field();
};

