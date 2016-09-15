#ifndef FIELD_H_
#define FIELD_H_
class Level;
#include "StdAfx.h"
class Field
{
protected:
	TYPES::FieldType type;

	float m_x;	
	float m_y;
	bool exist;
	int hp;

	TYPES::DisplayLayer layer;

	TYPES::FieldType returnType();
	void setCoord(float x1, float y1);
	
	void setExist(bool exist1);

public:
virtual	void Draw()=0;
virtual void Update(double dt, Level * p_level)=0;
	bool isExist();
	void SetX(double newx) { m_x = newx; }
	void SetY(double newy) { m_y = newy; }
	void SetPosition(double x, double y) { m_x = x; m_y = y; }
	double GetX()   { return m_x; }
	double GetY()   { return m_y; }
	Field(float x1, float y1, bool exist1, TYPES::FieldType type1, TYPES::DisplayLayer layer1,int hp1) :m_x(x1),m_y(y1), exist(exist1), type(type1), layer(layer1),hp(hp1)
	{};
virtual	~Field();
};

#endif