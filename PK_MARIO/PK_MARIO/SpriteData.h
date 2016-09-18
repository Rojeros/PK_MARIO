#ifndef SPRITEDATA_H_
#define SPRITEDATA_H_

#pragma once
#include "StdAfx.h"

/// <summary>	A spritedata contains info about Sprites to display on screen. </summary>
class SpriteData
{
protected:
	
public:
	/// <summary>	counts frames in animation. </summary>
	unsigned int frame_count;
	/// <summary>	time of one frames. </summary>
	double frame_duration_time;
	/// <summary>	left position of sprite on texture (in px) </summary>
	double left;
	/// <summary>	right position of sprite on texture (in px) </summary>
	double bottom;
	/// <summary>	width of sprite on texture (in px) </summary>
	double width;
	/// <summary>	height of sprite in texture (in px) </summary>
	double height;
	/// <summary>	is animation is loop </summary>
	bool loop;
	/// <summary>	display layer on screen </summary>
	TYPES::DisplayLayer layer;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="frame_count">   	Number of frames. </param>
	/// <param name="frame_duration">	Duration of the frame. </param>
	/// <param name="left">			 	left position of sprite on texture (in px). </param>
	/// <param name="bottom">		 	right position of sprite on texture (in px). </param>
	/// <param name="width">		 	width of sprite on texture (in px) . </param>
	/// <param name="height">		 	height of sprite in texture (in px). </param>
	/// <param name="loop">			 	true to loop. </param>
	/// <param name="level">		 	display layer on screen . </param>
	///-------------------------------------------------------------------------------------------------

	SpriteData( size_t frame_count,
		double frame_duration, double left, double bottom,
		double width, double height, bool loop, TYPES::DisplayLayer level) :
		 frame_count(frame_count), frame_duration_time(frame_duration),
		left(left), bottom(bottom), width(width), height(height), loop(loop),layer(level) {
	}
	~SpriteData();
};

#endif