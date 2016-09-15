#ifndef __HALL_OF_FAME_H__
#define __HALL_OF_FAME_H__
#include "StdAfx.h"


class HallOfFame {
private:
	struct Entry {
		std::string name;
		size_t points;
	};

public:
	explicit HallOfFame();

	void Draw();
	bool Update(double dt);
	void ProcessEvents();
	bool IsDone()   { return m_is_done; }


private:
	void LoadFromFile();

private:
	bool m_is_done;
	std::vector<Entry> m_entries;
};

#endif /* __HALL_OF_FAME_H__ */
