#ifndef SPRITE_H_
#define SPRITE_H_
#include "StdAfx.h"
#include "SpriteData.h"
#include "SpriteRenderer.h"
class Sprite
{
protected:

	/// <summary>	The renderer. </summary>
	
	std::string path;
	size_t m_current_frame;           // numer aktualnej klatki
	double m_current_frame_duration;  // czas trwania aktualnej klatki

public:
	SpriteRenderer m_renderer;
	SpriteData m_data;
	Sprite(SpriteData&data,std::string path1);

	void Update(double dt);
	void SetCurrentFrame(size_t frame_num);
	void DrawCurrentFrame(double x, double y, double width, double height);
	void Load(std::string path)
	{
	//	m_renderer.reset(new SpriteRenderer(path));
	}


	/// <summary>	Gets the renderer. </summary>
	///
	/// <returns>	The renderer. </returns>

	SpriteRenderer * GetRenderer()
	{
		return &m_renderer;
	}

};

typedef boost::shared_ptr<Sprite> SpritePtr;

#endif /* SPRITE_H_ */
