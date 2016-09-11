#ifndef RENDERER_H_
#define RENDERER_H_

#include "StdAfx.h"
#include "Types.h"
class SpriteRenderer
{
public:
	SpriteRenderer() :m_tile_width(.05), m_tile_height(.05)
	{
	}

	void setFilename(std::string path);
	double GetTileWidth();
	double GetTileHeight();

	size_t GetHorizontalTilesOnScreenCount();
	size_t GetVerticalTilesOnScreenCount();

	void SetTileSize(double width, double height);

	void LoadTexture();
	void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,double width, double height, TYPES::DisplayLayer layer);


protected:
	static GLuint  m_texture;
	static std::string filename;
	double m_tile_width;
	double m_tile_height;


};


#endif /* RENDERER_H_ */
