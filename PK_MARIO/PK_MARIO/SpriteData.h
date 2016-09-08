#pragma once
#include "StdAfx.h"

class SpriteData
{
protected:
	
public:
	unsigned int frame_count; // liczba klatek w animacji
	double frame_duration_time;   // czas trwania klatki
	double left;  // po³o¿enie w poziomie pierwszej klatki animacji w obrazku (w px)
	double bottom;// po³o¿enie w pionie pierwszej klatki animacji w obrazku (w px)
	double width; // szerokoœæ klatki w pikselach
	double height;// wysokoœæ klatki w pikselach
	bool loop;    // czy animacja ma byæ zapêtlona?
	TYPES::DisplayLayer layer;       // warstwa, na którym bêdzie rysowany sprite. Im bli¿ej 0, tym bli¿ej obserwatora

	SpriteData( size_t frame_count,
		double frame_duration, double left, double bottom,
		double width, double height, bool loop, TYPES::DisplayLayer level) :
		 frame_count(frame_count), frame_duration_time(frame_duration),
		left(left), bottom(bottom), width(width), height(height), loop(loop),layer(level) {
	}
	~SpriteData();
};

