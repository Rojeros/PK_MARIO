#ifndef __SCORE_SUBMIT_H__
#define __SCORE_SUBMIT_H__
#include "StdAfx.h"


/// <summary>	A score submit, get info about player after game </summary>
class ScoreSubmit  {
private:
	/// <summary>	An entry. </summary>
	struct Entry {
		std::string name;
		size_t points;
	};

public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="points">	The points. </param>
	///-------------------------------------------------------------------------------------------------

	ScoreSubmit(size_t points);

	/// <summary>	Process the events. </summary>
	void ProcessEvents();
	/// <summary>	Draws this object. </summary>
	void Draw();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates the given dt. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///
	/// <returns>	true if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------

	bool Update(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a score. </summary>
	///
	/// <param name="score">	The score. </param>
	///-------------------------------------------------------------------------------------------------

	void setScore(int score);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is done. </summary>
	///
	/// <returns>	true if done, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsDone();
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Set status to not done. </summary>
	///-------------------------------------------------------------------------------------------------

	void NotDone();

private:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Letter position. </summary>
	///
	/// <param name="ch">	The character. </param>
	///
	/// <returns>	A std::pair&lt;double,double&gt; </returns>
	///-------------------------------------------------------------------------------------------------

	std::pair<double, double> LetterPosition(char ch);
	/// <summary>	Stores in file. </summary>
	void StoreInFile();

private:
	/// <summary>	true if this object is done, go to other window </summary>
	bool m_is_done;
	/// <summary>	The player nickname. </summary>
	std::string m_player_nickname;
	/// <summary>	The next letter. </summary>
	size_t m_next_letter;
	/// <summary>	The points. </summary>
	size_t m_points;
	/// <summary>	The highlighted character. </summary>
	char m_highlighted_char;

};

#endif 
