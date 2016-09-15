#include "StdAfx.h"

#include "Collisions.h"

// czy prostok¹ty siê przecinaj¹
bool Collisions::Collides(  Collisions & box)   {
	if (m_min_x > box.m_max_x || m_max_x < box.m_min_x || m_min_y > box.m_max_y || m_max_y < box.m_min_y) {
		return false;
	}
	return true;
}

// czy this jest powy¿ej box
bool Collisions::IsUnder(  Collisions & box)   {
	return Collides(box) && m_min_y < box.m_max_y && box.m_max_y < m_max_y;
}

// czy this jest poni¿ej box
bool Collisions::IsOver(  Collisions & box)   {
	// czyli czy box jest powy¿ej this
	return box.IsUnder(*this);
}

// czy this jest po lewej stronie box'a
bool Collisions::IsOnRightOf(  Collisions & box)   {
	return Collides(box) && m_min_x < box.m_min_x && box.m_min_x < m_max_x;
}

// czy this jest po prawej stronie box'a
bool Collisions::IsOnLeftOf(  Collisions & box)   {
	return box.IsOnRightOf(*this);
}

std::ostream& operator<<(std::ostream& os,   Collisions& box) {
	os << "[ " << box.GetMinX() << ", " << box.GetMinY() << "; " << box.GetMaxX() << ", " << box.GetMaxY() << " ] ";
	return os;
}
