#ifndef __TYPES_H__
#define __TYPES_H__

namespace PS {
	enum PlayerState {
		Stand,
		GoLeft,
		GoRight
	};
}

namespace DL {
	enum DisplayLayer {
		Foreground = 1,  // przedni plan
		Player = 2,      // plan z graczem
		Background = 3   // t³o
	};
}

namespace FT {
	enum FieldType {
		None = 0,
		PlatformLeftEnd = 1,
		PlatformMidPart = 2,
		PlatformRightEnd = 3,

		COUNT
	};
}

#endif
