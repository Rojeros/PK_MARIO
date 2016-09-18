#include "StdAfx.h"

#include "Collisions.h"

bool Collisions::Collides(  Collisions & box)   
{
	if (m_min_x > box.m_max_x || m_max_x < box.m_min_x || m_min_y > box.m_max_y || m_max_y < box.m_min_y) 
	{
		return false;
	}
	return true;
}

bool Collisions::IsUnder(  Collisions & box)   
{
	return Collides(box) && m_min_y < box.m_max_y && box.m_max_y < m_max_y;
}

bool Collisions::IsOver(  Collisions & box)  
{
	return box.IsUnder(*this);
}

bool Collisions::IsOnRightOf(  Collisions & box)  
{
	return Collides(box) && m_min_x < box.m_min_x && box.m_min_x < m_max_x;
}

double Collisions::GetMinX()
{
	return m_min_x;
}

double Collisions::GetMinY()
{
	return m_min_y;
}
double Collisions::GetMaxX()
{
	return m_max_x;
}
double Collisions::GetMaxY()
{
	return m_max_y;
}
Collisions Collisions::Move(double min_x_offset, double min_y_offset, double max_x_offset, double max_y_offset)
{
	return Collisions(m_min_x + min_x_offset, m_min_y + min_y_offset, m_max_x + max_x_offset, m_max_y + max_y_offset);
}
bool Collisions::IsOnLeftOf(  Collisions & box)   
{
	return box.IsOnRightOf(*this);
}

std::ostream& operator<<(std::ostream& os,   Collisions& box) 
{
	os << "[ " << box.GetMinX() << ", " << box.GetMinY() << "; " << box.GetMaxX() << ", " << box.GetMaxY() << " ] ";
	return os;
}
