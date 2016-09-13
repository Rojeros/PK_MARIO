#ifndef __AABB_H__
#define __AABB_H__
#include "StdAfx.h"


// Axis-Aligned Bounding Box
class Collisions {
public:
	Collisions(double min_x, double min_y, double max_x, double max_y) :
		m_min_x(min_x), m_min_y(min_y), m_max_x(max_x), m_max_y(max_y) {

	}

	bool Collides(const Collisions& box) const;
	bool IsOver(const Collisions& box) const;
	bool IsUnder(const Collisions& box) const;
	bool IsOnLeftOf(const Collisions& box) const;
	bool IsOnRightOf(const Collisions& box) const;

	double GetMinX() const { return m_min_x; }
	double GetMinY() const { return m_min_y; }
	double GetMaxX() const { return m_max_x; }
	double GetMaxY() const { return m_max_y; }

	Collisions Move(double min_x_offset, double min_y_offset, double max_x_offset, double max_y_offset) {
		return Collisions(m_min_x + min_x_offset, m_min_y + min_y_offset, m_max_x + max_x_offset, m_max_y + max_y_offset);
	}

	friend std::ostream& operator<< (std::ostream& os, const Collisions& box);

private:
	// pozycja lewego dolnego naro¿nika
	double m_min_x;
	double m_min_y;

	// pozycja prawego górnego naro¿nika
	double m_max_x;
	double m_max_y;
};


#endif