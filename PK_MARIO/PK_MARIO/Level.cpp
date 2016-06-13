#include "StdAfx.h"

#include "Engine.h"
#include "Level.h"


Level::Level()
	: m_width(0),
	m_height(0) {
}

void Level::LoadFromFile(const std::string& filename) {
	std::ifstream lvl(filename.c_str());
	if (!lvl) {
		std::cerr << "Nie uda³o siê za³adowaæ pliku " << filename << "\n";
		return;
	}

	lvl >> m_width >> m_height;
	m_data.resize(m_height);
	for (size_t y = 0; y < m_height; ++y) {
		m_data.at(y).resize(m_width);
	}

	int tmp;
	for (size_t y = 0; y < m_height; ++y) {
		for (size_t x = 0; x < m_width; ++x) {
			lvl >> tmp;
			m_data.at(y).at(x) = FT::FieldType(tmp);
		}
	}
}

FT::FieldType Level::Field(size_t x, size_t y) const {
	if (x >= m_width || y >= m_height) {
		return FT::None;
	}
	return m_data.at(y).at(x);
}
