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

float Field::get_x()
{
	return m_x;
}

float Field::get_y()
{
	return m_y;
}

bool Field::isExist()
{
	return exist;
}


void Field::setExist(bool exist1)
{
	exist = exist1;
}
