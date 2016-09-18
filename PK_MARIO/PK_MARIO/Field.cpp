#include "StdAfx.h"
#include "Field.h"


Field::~Field()
{
}


TYPES::FieldType Field::returnType()
{
	return TYPES::FieldType();
}

void Field::setCoord(float x1, float y1)
{
	m_x = x1;
	m_y = y1;
}


bool Field::isExist()
{
	return exist;
}

void Field::SetX(double newx)
{
	 m_x = newx; 
}

void Field::SetY(double newy)
{
	 m_y = newy; 
}

void Field::SetPosition(double x, double y)
{
	 m_x = x; m_y = y; 
}

double Field::GetX()
{
	 return m_x; 
}

double Field::GetY()
{
	return m_y; 
}


void Field::setExist(bool exist1)
{
	exist = exist1;
}
