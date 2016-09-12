#ifndef RENDERER_H_
#define RENDERER_H_

#include "StdAfx.h"
#include "Types.h"
class SpriteRenderer
{
public:
	SpriteRenderer() 
	{
	}

	void setFilename(std::string path);
	static double GetTileWidth();
	static double GetTileHeight();

	static size_t GetHorizontalTilesOnScreenCount();
	static size_t GetVerticalTilesOnScreenCount();

	void SetTileSize(double width, double height);

	void LoadTexture();
	void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,double width, double height, TYPES::DisplayLayer layer);


protected:
	static GLuint  m_texture;
	static std::string filename;
	static double m_tile_width;
	static double m_tile_height;


};


#endif /* RENDERER_H_ */
