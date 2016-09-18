#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "StdAfx.h"
#include "Types.h"
class SpriteRenderer
{
public:
	SpriteRenderer() 
	{
	}

	static void setFilename(std::string path);
	static double GetTileWidth();
	static double GetTileHeight();

	static size_t GetHorizontalTilesOnScreenCount();
	static size_t GetVerticalTilesOnScreenCount();

	static void SetProjection(size_t width, size_t height);
	static void ResetProjection();

	static void DrawQuad(double min_x, double min_y, double max_x, double max_y,	double r, double g, double b, double a) ;

	static void SetTileSize(double width, double height);
	static void resetTexture();
	static void LoadTexture();
	static void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,double width, double height, TYPES::DisplayLayer layer);


protected:
	static GLuint  m_texture;
	static std::string filename;
	static double m_tile_width;
	static double m_tile_height;


};


#endif /* RENDERER_H_ */
