#include "StdAfx.h"
#include "Field.h"


Field::~Field()
{
}


TYPES::FieldType Field::returnType()
{
	return TYPES::FieldType();
}

void Field::setCoord(int x1,int y1)
{
	x = x1;
	y = y1;
}

int Field::get_x()
{
	return x;
}

int Field::get_y()
{
	return y;
}

bool Field::isExist()
{
	return exist;
}


void Field::setExist(bool exist1)
{
	exist = exist1;
}
