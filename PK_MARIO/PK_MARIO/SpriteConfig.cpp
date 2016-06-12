#include "StdAfx.h"

#include "SpriteConfig.h"
#include "Types.h"
/*
DisplayLayer layer;       // warstwa, na którym bêdzie rysowany sprite. Im bli¿ej 0, tym bli¿ej obserwatora
size_t frame_count;           // liczba klatek w animacji
double frame_duration_time;   // czas trwania klatki
double left;   // po³o¿enie w poziomie pierwszej klatki animacji w obrazku (w px)
double bottom; // po³o¿enie w pionie pierwszej klatki animacji w obrazku (w px)
double width;  // szerokoœæ klatki w pikselach
double height; // wysokoœæ klatki w pikselach
bool loop;     // czy animacja ma byæ zapêtlona?
bool dark;     // czy spirte powinien byæ przyciemniony przy pomocy czarnej blendy?
*/

SpriteConfig::SpriteConfig() {

	Insert("PlatformTopLeft", SpriteConfigData(Foreground, 1, 1, 0 * 32, 1 * 32, 32, 32, false, false));
	Insert("PlatformLeft", SpriteConfigData(Foreground, 1, 1, 1 * 32, 1 * 32, 32, 32, false, false));
	Insert("PlatfromMid", SpriteConfigData(Foreground, 1, 1, 0 * 32, 2 * 32, 32, 32, false, false));
	Insert("PlatformTop", SpriteConfigData(Foreground, 1, 1, 1 * 32, 2 * 32, 32, 32, false, false));
	Insert("PlatformLeftTopRight", SpriteConfigData(Foreground, 1, 1, 2 * 32, 2 * 32, 32, 32, false, false));
	Insert("PlatformLeftRight", SpriteConfigData(Foreground, 1, 1, 3 * 32, 2 * 32, 32, 32, false, false));
	Insert("PlatformTopRight", SpriteConfigData(Foreground, 1, 1, 0 * 32, 3 * 32, 32, 32, false, false));
	Insert("PlatformRight", SpriteConfigData(Foreground, 1, 1, 1 * 32, 3 * 32, 32, 32, false, false));
	Insert("EndOfLevel", SpriteConfigData(Foreground, 4, 0.1, 4 * 32, 2 * 32, 32, 32, true, false));

	Insert("NcPlatformTopLeft", SpriteConfigData(Background, 1, 1, 0 * 32, 1 * 32, 32, 32, false, true));
	Insert("NcPlatformLeft", SpriteConfigData(Background, 1, 1, 1 * 32, 1 * 32, 32, 32, false, true));
	Insert("NcPlatfromMid", SpriteConfigData(Background, 1, 1, 0 * 32, 2 * 32, 32, 32, false, true));
	Insert("NcPlatformTop", SpriteConfigData(Background, 1, 1, 1 * 32, 2 * 32, 32, 32, false, true));
	Insert("NcPlatformLeftTopRight", SpriteConfigData(Background, 1, 1, 2 * 32, 2 * 32, 32, 32, false, true));
	Insert("NcPlatformLeftRight", SpriteConfigData(Background, 1, 1, 3 * 32, 2 * 32, 32, 32, false, true));
	Insert("NcPlatformTopRight", SpriteConfigData(Background, 1, 1, 0 * 32, 3 * 32, 32, 32, false, true));
	Insert("NcPlatformRight", SpriteConfigData(Background, 1, 1, 1 * 32, 3 * 32, 32, 32, false, true));

	Insert("mush_right", SpriteConfigData(Entity, 4, 0.3, 0, 12 * 32, 32, 32, true, false));
	Insert("mush_left", SpriteConfigData(Entity, 4, 0.3, 0, 13 * 32, 32, 32, true, false));
	Insert("mush_stop", SpriteConfigData(Entity, 4, 0.3, 0, 14 * 32, 32, 32, true, false));

	Insert("player_right", SpriteConfigData(Player, 4, 0.1, 0, 4 * 32, 32, 32, true, false));
	Insert("player_left", SpriteConfigData(Player, 4, 0.1, 0, 5 * 32, 32, 32, true, false));
	Insert("player_stop", SpriteConfigData(Player, 8, 0.1, 0, 6 * 32, 32, 32, true, false));
	Insert("player_bullet", SpriteConfigData(Entity, 1, 0.3, 6 * 32, 13 * 32, 32, 32, true, false));
	Insert("twinshot_upgrade", SpriteConfigData(Entity, 4, 0.1, 6 * 32, 15 * 32, 32, 32, true, false));
}

SpriteConfigData SpriteConfig::Get(const std::string& name) const {
	if (Contains(name)) {
		return m_data.find(name)->second;
	}
	std::cerr << "Config not found: " << name << std::endl;
	throw("Config not found: " + name);
}

bool SpriteConfig::Contains(const std::string& name) const {
	return (m_data.find(name) != m_data.end());
}

void SpriteConfig::Insert(const std::string& name, const SpriteConfigData& data) {
	m_data.insert(std::make_pair(name, data));
}

