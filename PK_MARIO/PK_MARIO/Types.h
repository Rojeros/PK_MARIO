
#ifndef __TYPES_H__
#define __TYPES_H__

namespace  TYPES
{

		enum PlayerState {
			Stand,
			GoLeft,
			GoRight,
			TurnLeft,   // posta� zwr�cona w lewo
			TurnRight   // posta� zwr�cona w prawo
		};
	
	enum CharacterState
	{
		Standing,
		GoingLeft,
		GoingRight
	};

	enum MonsterState
	{
		MStanding,
		MGoingLeft,
		MGoingRight
	};

	enum DisplayLayer
	{
		Foreground = 1,  // przedni plan
		PlayerLayer = 2,      // plan z graczem
		Background = 3   // t�o
	};

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
	enum BonusType
	{
		hp = 0,
		levelEnd = 1
	};
}



struct LevelEntityData {
	LevelEntityData()
		: name("[unknown]"), x(-1), y(-1) {   }

	LevelEntityData(const std::string& name, double x, double y)
		: name(name), x(x), y(y) {   }

	bool operator() (const LevelEntityData& a, const LevelEntityData& b) {
		return a.x < b.x;
	}

	std::string name;  // nazwa jednostki
	double x;          // po�o�enie na osi odci�tych
	double y;          // po�o�enie na osi rz�dnych
};

#endif
