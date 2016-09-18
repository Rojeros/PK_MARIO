
#ifndef __TYPES_H__
#define __TYPES_H__


///-------------------------------------------------------------------------------------------------
// namespace: TYPES
//
// summary:	All games types, by enums.
///-------------------------------------------------------------------------------------------------

namespace  TYPES
{

		/// <summary>	Values that represent player animation states. </summary>
		enum PlayerState {
			Stand,
			GoLeft,
			GoRight,
			TurnLeft,   
			TurnRight  
		};
	
	/// <summary>	Values that represent character animation states. </summary>
	enum CharacterState
	{
		Standing,
		GoingLeft,
		GoingRight
	};

	/// <summary>	Values that represent monster animation states. </summary>
	enum MonsterState
	{
		MStanding,
		MGoingLeft,
		MGoingRight
	};

	/// <summary>	Values that represent display layers. </summary>
	enum DisplayLayer
	{
		Foreground = 1,  
		PlayerLayer = 2,     
		Background = 3   
	};

	/// <summary>	Values that represent field types. </summary>
	enum FieldType
	{
		None = 0,
		PlatformLeftEnd = 1,
		PlatformMidPart = 2,
		PlatformRightEnd = 3,
		
		Players = 4,
		Enemy = 5,
		Bonuses = 6,
		NoDestroyAble=7,
		PlayerBullet=8,
		Character=9

	};

	/// <summary>	Values that represent bonus types. </summary>
	enum BonusType
	{
		hp = 0,
		levelEnd = 1
	};
}



/// <summary>	A level entity data, contains level directory info, enemys for level and bonuses </summary>
struct LevelEntityData {
	LevelEntityData()
		: name("[unknown]"), x(-1), y(-1) {   }

	LevelEntityData(const std::string& name, double x, double y)
		: name(name), x(x), y(y) {   }

	bool operator() (const LevelEntityData& a, const LevelEntityData& b) {
		return a.x < b.x;
	}

	/// <summary>	The string with name. </summary>
	std::string name;  
	/// <summary>	The x coordinate on map. </summary>
	double x;          
	/// <summary>	The y coordinate on map. </summary>
	double y;          
};

#endif
