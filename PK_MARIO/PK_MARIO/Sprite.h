#ifndef SPRITE_H_
#define SPRITE_H_
#include "StdAfx.h"
#include "SpriteData.h"
#include "SpriteRenderer.h"
#include "Text.h"
/// <summary>	A sprite, get info about sprite, change frames </summary>
class Sprite
{
protected:


	/// <summary>	The current frame. </summary>
	size_t m_current_frame;          
	/// <summary>	The current frame duration. </summary>
	double m_current_frame_duration;  

public:
	/// <summary>	The renderer. </summary>
	static SpriteRenderer * m_renderer;
	/// <summary>	The data about sprite </summary>
	SpriteData m_data;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="data">	[in,out] The data about sprite. </param>
	///-------------------------------------------------------------------------------------------------

	Sprite(SpriteData&data) :
		m_data(data), m_current_frame(0), m_current_frame_duration(0.0)
	{
		
	}

	/// <summary>	Sets the renderer. </summary>
	static void setRenderer();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Updates the given dt. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void Update(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets current frame. </summary>
	///
	/// <param name="frame_num">	The frame number. </param>
	///-------------------------------------------------------------------------------------------------

	void SetCurrentFrame(size_t frame_num);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw current frame. </summary>
	///
	/// <param name="x">	 	The x coordinate. </param>
	/// <param name="y">	 	The y coordinate. </param>
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawCurrentFrame(double x, double y, double width, double height);


	/// <summary>	Destructor. </summary>
	Sprite::~Sprite() 
	{
	}
};


#endif 