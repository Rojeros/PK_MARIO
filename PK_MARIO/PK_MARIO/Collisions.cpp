#include "StdAfx.h"

#include "Collisions.h"

// czy prostok¹ty siê przecinaj¹
bool Collisions::Collides(const Collisions & box) const {
	if (m_min_x > box.m_max_x || m_max_x < box.m_min_x || m_min_y > box.m_max_y || m_max_y < box.m_min_y) {
		return false;
	}
	return true;
}

// czy this jest powy¿ej box
bool Collisions::IsOver(const Collisions & box) const {
	return Collides(box) && m_min_y < box.m_max_y && box.m_max_y < m_max_y;
}

// czy this jest poni¿ej box
bool Collisions::IsUnder(const Collisions & box) const {
	// czyli czy box jest powy¿ej this
	return box.IsOver(*this);
}

// czy this jest po lewej stronie box'a
bool Collisions::IsOnLeftOf(const Collisions & box) const {
	return Collides(box) && m_min_x < box.m_min_x && box.m_min_x < m_max_x;
}

// czy this jest po prawej stronie box'a
bool Collisions::IsOnRightOf(const Collisions & box) const {
	return box.IsOnLeftOf(*this);
}

std::ostream& operator<<(std::ostream& os, const Collisions& box) {
	os << "[ " << box.GetMinX() << ", " << box.GetMinY() << "; " << box.GetMaxX() << ", " << box.GetMaxY() << " ] ";
	return os;
}
