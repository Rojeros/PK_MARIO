#ifndef __TYPES_H__
#define __TYPES_H__
#include "StdAfx.h"

	enum PlayerState {
		Stand,
		GoLeft,
		GoRight,
		TurnLeft,   // postaæ zwrócona w lewo
		TurnRight   // postaæ zwrócona w prawo
	};


	enum DisplayLayer {
		Foreground = 1,  // przedni plan
		Player = 2,      // plan z graczem
		Entity = 2,      // plan z jednostkami
		Background = 3   // t³o
	};

	enum FieldType {
		None = 0,
		EndOfLevel = 1,

		COLLIDING_START = 10000,

		PlatformTopLeft, // 10001
		PlatformLeft, // 10002
		PlatfromMid, // 10003
		PlatformTop, // 10004
		PlatformLeftTopRight, // 10005
		PlatformLeftRight, // 10006
		PlatformTopRight, // 10007
		PlatformRight, // 10008

		COLLIDING_END,

		NON_COLLIDING_START = 20000,

		NcPlatformTopLeft,
		NcPlatformLeft,
		NcPlatfromMid,
		NcPlatformTop,
		NcPlatformLeftTopRight,
		NcPlatformLeftRight,
		NcPlatformTopRight,
		NcPlatformRight,
		NcCandleWithBg,
		NcCandleNoBg,
		NcCrackWithBg,
		NcCrackNoBg,

		NON_COLLIDING_END
	};

// stan jednostki
//	enum EntityState {
//		Stand,
//		GoLeft,
//		GoRight
//	};


// typ jednostki
	enum EntityType {
		Mush,
		PlayerBullet,
		TwinShot
	};


// typ fade effectu
	enum Type {
		UNKNOWN,

		FadeIn,
		FadeOut,
		PinWheelOut,

		COUNT
	};


#endif
