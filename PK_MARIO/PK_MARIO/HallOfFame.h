#ifndef __HALL_OF_FAME_H__
#define __HALL_OF_FAME_H__
#include "StdAfx.h"


/// <summary>	A hall of fame, display list of players with their scores. </summary>
class HallOfFame {
private:
	/// <summary>	An entry. </summary>
	struct Entry {
		std::string name;
		size_t points;
	};

public:
	/// <summary>	Default constructor. </summary>
	explicit HallOfFame();

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
	/// <summary>	Process the events. </summary>
	void ProcessEvents();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if this object is done. </summary>
	///
	/// <returns>	true if done, false if not. </returns>
	///-------------------------------------------------------------------------------------------------

	bool IsDone();


private:
	/// <summary>	Loads from file. </summary>
	void LoadFromFile();

private:
	/// <summary>	true if this object is done, go to other window </summary>
	bool m_is_done;
	/// <summary>	The list of entries objects. </summary>
	std::vector<Entry> m_entries;
};

#endif
