
#ifndef __TYPES_H__
#define __TYPES_H__

namespace  TYPES
{

		enum PlayerState {
			Stand,
			GoLeft,
			GoRight,
			TurnLeft,   // postaæ zwrócona w lewo
			TurnRight   // postaæ zwrócona w prawo
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
		Background = 3   // t³o
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
		PlayerBullet=8

	};
	enum BonusType
	{
		hp = 0,
		speed = 1
	};
}
#endif
