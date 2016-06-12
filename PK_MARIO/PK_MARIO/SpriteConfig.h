#ifndef SPRITECONFIG_H_
#define SPRITECONFIG_H_
#include "StdAfx.h"

#include "Types.h"


struct SpriteConfigData {
	/**
	* frame_duration - czas trwania klatki (w sekundach)
	* left, bottom, width oraz height s� wsp�rz�dnymi klatki w pikselach (na obrazku) oraz jej rozmiarami.
	* layer - poziom, na kt�rym b�dzie wy�wietlony sprite
	*/
	SpriteConfigData(DisplayLayer layer, size_t frame_count, double frame_duration, double left,
		double bottom, double width, double height, bool loop, bool dark) :
		layer(layer), frame_count(frame_count), frame_duration_time(frame_duration),
		left(left), bottom(bottom), width(width), height(height), loop(loop), dark(dark) {
	}

	DisplayLayer layer;       // warstwa, na kt�rym b�dzie rysowany sprite. Im bli�ej 0, tym bli�ej obserwatora
	size_t frame_count;           // liczba klatek w animacji
	double frame_duration_time;   // czas trwania klatki
	double left;   // po�o�enie w poziomie pierwszej klatki animacji w obrazku (w px)
	double bottom; // po�o�enie w pionie pierwszej klatki animacji w obrazku (w px)
	double width;  // szeroko�� klatki w pikselach
	double height; // wysoko�� klatki w pikselach
	bool loop;     // czy animacja ma by� zap�tlona?
	bool dark;     // czy spirte powinien by� przyciemniony przy pomocy czarnej blendy?
};

class SpriteConfig {
public:
	SpriteConfig();
	SpriteConfigData Get(const std::string& name) const;
	bool Contains(const std::string& name) const;

private:
	std::map<std::string, SpriteConfigData> m_data;
	void Insert(const std::string& name, const SpriteConfigData& data);
};

typedef boost::shared_ptr<SpriteConfig> SpriteConfigPtr;

#endif /* SPRITECONFIG_H_ */
