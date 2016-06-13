#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "StdAfx.h"
#include "Types.h"

class Level {
public:
	explicit Level();

	void LoadFromFile(const std::string& filename);

	FT::FieldType Field(size_t x, size_t y) const;
	size_t GetWidth() const { return m_width; }
	size_t GetHeight() const { return m_height; }

private:
	size_t m_width;
	size_t m_height;
	std::vector<std::vector<FT::FieldType> > m_data;
};
typedef boost::shared_ptr<Level> LevelPtr;

#endif
