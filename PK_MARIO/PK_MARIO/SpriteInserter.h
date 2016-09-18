#ifndef SPRITEINSERTER_H_
#define SPRITEINSERTER_H_


#include "StdAfx.h"
#include "SpriteData.h"
#include "SpriteLoader.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Sets type for sprite. </summary>
///
/// <typeparam name="putType1">	Type from template, describe additional data. </typeparam>
/// <param name="type1">	FielType of tail. </param>
/// <param name="type"> 	describe additional data. </param>
///
/// <returns>	null if it fails, else a pointer to a Sprite. </returns>
///-------------------------------------------------------------------------------------------------

template<class inputType1>
inline 	Sprite * SetTypeForSprite(TYPES::FieldType type1, inputType1 type )
{
	Sprite * ptr;
	switch (type1)
	{
	case TYPES::None:
		break;



	case TYPES::PlatformLeftEnd:
		SpriteLoader::Insert("PlatformLeftEnd", Sprite(SpriteData(1, 0.2, 0, 1 * 32, 32, 32, true, TYPES::PlayerLayer)));
		ptr = SpriteLoader::Get("PlatformLeftEnd");
		break;



	case TYPES::PlatformMidPart:
		SpriteLoader::Insert("PlatformMidPart", Sprite(SpriteData(1, 0.2, 0, 2 * 32, 32, 32, true, TYPES::PlayerLayer)));
		ptr = SpriteLoader::Get("PlatformMidPart");
		break;



	case TYPES::PlatformRightEnd:
		SpriteLoader::Insert("PlatformRightEnd", Sprite(SpriteData(1, 0.2, 0, 3 * 32, 32, 32, true, TYPES::PlayerLayer)));
		ptr = SpriteLoader::Get("PlatformRightEnd");
		break;

	case TYPES::NoDestroyAble:
		SpriteLoader::Insert("NoDestroyAble", Sprite(SpriteData(1, 0.2, 32, 1 * 32, 32, 32, true, TYPES::PlayerLayer)));
		ptr = SpriteLoader::Get("NoDestroyAble");
		break;
	

	case TYPES::Players:
		if (type == TYPES::GoRight) {
			SpriteLoader::Insert("player_right", Sprite(SpriteData(8, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("player_right");
		}
		else if (type == TYPES::GoLeft)
		{
			SpriteLoader::Insert("player_left", Sprite(SpriteData(8, 0.2, 0, 5 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("player_left");
		}
		else if (type == TYPES::Stand)
		{
			SpriteLoader::Insert("player_stop", Sprite(SpriteData(2, 0.2, 0, 6 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("player_stop");
		}
		else
		{
			throw("Types undefined");
		}
		break;



	case TYPES::Enemy:
		if (type == TYPES::GoingRight) {
			SpriteLoader::Insert("monster_right", Sprite(SpriteData(4, 0.2, 0, 12 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("monster_right");
		}
		else if (type == TYPES::GoingLeft)
		{
			SpriteLoader::Insert("monster_left", Sprite(SpriteData(4, 0.2, 0, 13 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("monster_left");
		}
		else if (type == TYPES::Standing)
		{
			SpriteLoader::Insert("monster_stop", Sprite(SpriteData(3, 0.2, 0, 14 * 32, 32, 32, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("player_stop");
		}
		else
		{
			throw("Types undefined");
		}
		break;



	case TYPES::Bonuses:
		if (type == TYPES::hp) {
			SpriteLoader::Insert("hp", Sprite(SpriteData(9, 0.2, 0, 15 * 32, 32, 32, true, TYPES::Foreground)));
			ptr = SpriteLoader::Get("hp");
		}
		else if (type == TYPES::levelEnd)
		{
			SpriteLoader::Insert("level_end", Sprite(SpriteData(5, 0.2, 32, 3 * 32, 64, 64, true, TYPES::PlayerLayer)));
			ptr = SpriteLoader::Get("level_end");
		}
		else
		{
			throw("Types undefined");
		}
		break;



	case TYPES::PlayerBullet:
		SpriteLoader::Insert("Bullet", Sprite(SpriteData(4, 0.2, 0, 11 * 32, 32, 32, true, TYPES::Foreground)));
		ptr = SpriteLoader::Get("Bullet");
		break;



	default:
		throw("Types undefined");
		break;
	}

}

#endif 
