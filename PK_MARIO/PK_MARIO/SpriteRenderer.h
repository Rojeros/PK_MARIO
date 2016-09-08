#ifndef RENDERER_H_
#define RENDERER_H_

#include "StdAfx.h"
#include "Types.h"

class SpriteRenderer
{
public:
	SpriteRenderer(std::string patch) :
		m_tile_width(.05), m_tile_height(.05),filename(patch)
	{
	}

	double GetTileWidth() const
	{
		return m_tile_width;
	}
	double GetTileHeight() const
	{
		return m_tile_height;
	}

	size_t GetHorizontalTilesOnScreenCount() const
	{
		return 1.0 / m_tile_width + 0.5;
	}
	size_t GetVerticalTilesOnScreenCount()   const
	{
		return 1.0 / m_tile_height + 0.5;
	}

	void SetTileSize(double width, double height);

	void LoadTexture();
	void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,
		double width, double height, TYPES::DisplayLayer layer);

protected:
	GLuint m_texture;
	double m_tile_width;
	double m_tile_height;
	std::string filename;
};

typedef boost::shared_ptr<SpriteRenderer> RendererPtr;

#endif /* RENDERER_H_ */
