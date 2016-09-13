#ifndef __SCORE_SUBMIT_H__
#define __SCORE_SUBMIT_H__
#include "StdAfx.h"


class ScoreSubmit  {
private:
	struct Entry {
		std::string name;
		size_t points;
	};

public:
	explicit ScoreSubmit(size_t points);

	void ProcessEvents();
	void Draw();
	bool Update(double dt);

	bool IsDone() const { return m_is_done; }


private:
	std::pair<double, double> LetterPosition(char ch);
	void StoreInFile();

private:
	bool m_is_done;
	std::string m_player_nickname;
	size_t m_next_letter;
	size_t m_points;
	char m_highlighted_char;

};

#endif /* __SCORE_SUBMIT_H__ */
