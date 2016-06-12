#ifndef SPRITECONFIG_H_
#define SPRITECONFIG_H_
#include "StdAfx.h"

#include "Types.h"


struct SpriteConfigData {
	/**
	* frame_duration - czas trwania klatki (w sekundach)
	* left, bottom, width oraz height s¹ wspó³rzêdnymi klatki w pikselach (na obrazku) oraz jej rozmiarami.
	* layer - poziom, na którym bêdzie wyœwietlony sprite
	*/
	SpriteConfigData(DisplayLayer layer, size_t frame_count, double frame_duration, double left,
		double bottom, double width, double height, bool loop, bool dark) :
		layer(layer), frame_count(frame_count), frame_duration_time(frame_duration),
		left(left), bottom(bottom), width(width), height(height), loop(loop), dark(dark) {
	}

	DisplayLayer layer;       // warstwa, na którym bêdzie rysowany sprite. Im bli¿ej 0, tym bli¿ej obserwatora
	size_t frame_count;           // liczba klatek w animacji
	double frame_duration_time;   // czas trwania klatki
	double left;   // po³o¿enie w poziomie pierwszej klatki animacji w obrazku (w px)
	double bottom; // po³o¿enie w pionie pierwszej klatki animacji w obrazku (w px)
	double width;  // szerokoœæ klatki w pikselach
	double height; // wysokoœæ klatki w pikselach
	bool loop;     // czy animacja ma byæ zapêtlona?
	bool dark;     // czy spirte powinien byæ przyciemniony przy pomocy czarnej blendy?
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
