#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_

#include "StdAfx.h"
#include "Types.h"
/// <summary>	A sprite renderer, collects all info about that, what happends on screen </summary>
class SpriteRenderer
{
public:
	/// <summary>	Default constructor. </summary>
	SpriteRenderer() 
	{
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a filename to texture. </summary>
	///
	/// <param name="path">	Full pathname of the file to texture. </param>
	///-------------------------------------------------------------------------------------------------

	static void setFilename(std::string path);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets tile width. </summary>
	///
	/// <returns>	The tile width. </returns>
	///-------------------------------------------------------------------------------------------------

	static double GetTileWidth();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets tile height. </summary>
	///
	/// <returns>	The tile height. </returns>
	///-------------------------------------------------------------------------------------------------

	static double GetTileHeight();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets horizontal tiles on screen count. </summary>
	///
	/// <returns>	The horizontal tiles on screen count. </returns>
	///-------------------------------------------------------------------------------------------------

	static size_t GetHorizontalTilesOnScreenCount();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets vertical tiles on screen count. </summary>
	///
	/// <returns>	The vertical tiles on screen count. </returns>
	///-------------------------------------------------------------------------------------------------

	static size_t GetVerticalTilesOnScreenCount();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a projection. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	///-------------------------------------------------------------------------------------------------

	static void SetProjection(size_t width, size_t height);
	/// <summary>	Resets the projection. </summary>
	static void ResetProjection();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw quad. </summary>
	///
	/// <param name="min_x">	The minimum x coordinate. </param>
	/// <param name="min_y">	The minimum y coordinate. </param>
	/// <param name="max_x">	The maximum x coordinate. </param>
	/// <param name="max_y">	The maximum y coordinate. </param>
	/// <param name="r">		The R of RGB to process. </param>
	/// <param name="g">		The G of RGB to process. </param>
	/// <param name="b">		The B of RGB to process. </param>
	/// <param name="a">		The alpha canal to process. </param>
	///-------------------------------------------------------------------------------------------------

	static void DrawQuad(double min_x, double min_y, double max_x, double max_y,	double r, double g, double b, double a) ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets tile size. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	///-------------------------------------------------------------------------------------------------

	static void SetTileSize(double width, double height);
	/// <summary>	Resets the texture. </summary>
	static void resetTexture();
	/// <summary>	Loads the texture. </summary>
	static void LoadTexture();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw sprite. </summary>
	///
	/// <param name="tex_x"> 	The texrures x coordinate for sprite. </param>
	/// <param name="tex_y"> 	The texrures y coordinatef or sprite. </param>
	/// <param name="tex_w"> 	The texrures width for sprite. </param>
	/// <param name="tex_h"> 	The texrures height for sprite. </param>
	/// <param name="pos_x"> 	The position x coordinate on screen. </param>
	/// <param name="pos_y"> 	The position y coordinateon screen. </param>
	/// <param name="width"> 	The width on screen.. </param>
	/// <param name="height">	The height on screen.. </param>
	/// <param name="layer"> 	The layer to display on screen. </param>
	///-------------------------------------------------------------------------------------------------

	static void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,double width, double height, TYPES::DisplayLayer layer);


protected:
	/// <summary>	The texture for render. </summary>
	static GLuint  m_texture;
	/// <summary>	Filename of the file with texture. </summary>
	static std::string filename;
	/// <summary>	Width of the tile. </summary>
	static double m_tile_width;
	/// <summary>	Height of the tile. </summary>
	static double m_tile_height;


};


#endif 
