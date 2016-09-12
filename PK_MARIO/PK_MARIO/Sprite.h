#ifndef SPRITE_H_
#define SPRITE_H_
#include "StdAfx.h"
#include "SpriteData.h"
#include "SpriteRenderer.h"
class Sprite
{
protected:

	/// <summary>	The renderer. </summary>

	size_t m_current_frame;           // numer aktualnej klatki
	double m_current_frame_duration;  // czas trwania aktualnej klatki

public:
	SpriteRenderer * m_renderer;
	SpriteData m_data;

	Sprite(SpriteData&data, std::string path1) :
		m_data(data), m_current_frame(0), m_current_frame_duration(0.0)
	{
		m_renderer=new SpriteRenderer();
		m_renderer->setFilename(path1);
	}


	void Update(double dt);
	void SetCurrentFrame(size_t frame_num);
	void DrawCurrentFrame(double x, double y, double width, double height);
	void Load(std::string path)
	{
		m_renderer->setFilename(path);
	}


	/// <summary>	Gets the renderer. </summary>
	///
	/// <returns>	The renderer. </returns>

	Sprite::~Sprite() {
	}
};


#endif /* SPRITE_H_ */
