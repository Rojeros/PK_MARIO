#ifndef __TEXT_H__
#define __TEXT_H__
#include "StdAfx.h"
#include"SpriteRenderer.h"
#include "Sprite.h"

/// <summary>	A text class, Displaying character from texture. </summary>
class Text {
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <param name="width"> 	(Optional) The width. </param>
	/// <param name="height">	(Optional) The height. </param>
	/// <param name="layer"> 	(Optional) The layer. </param>
	///-------------------------------------------------------------------------------------------------

	Text(double width = 0.025, double height = 0.025, size_t layer = 0) {
		SetSize(width, height);
		SetLayer(layer);
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a size. </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>
	///-------------------------------------------------------------------------------------------------

	void SetSize(double width, double height);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a layer. </summary>
	///
	/// <param name="layer">	The layer. </param>
	///-------------------------------------------------------------------------------------------------

	void SetLayer(size_t layer);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw digit. </summary>
	///
	/// <param name="ch">   	The ch. </param>
	/// <param name="pos_x">	The position x coordinate. </param>
	/// <param name="pos_y">	The position y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawDigit(char ch, double pos_x, double pos_y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw letter. </summary>
	///
	/// <param name="ch">   	The ch. </param>
	/// <param name="pos_x">	The position x coordinate. </param>
	/// <param name="pos_y">	The position y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawLetter(char ch, double pos_x, double pos_y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw special. </summary>
	///
	/// <param name="ch">   	The ch. </param>
	/// <param name="pos_x">	The position x coordinate. </param>
	/// <param name="pos_y">	The position y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawSpecial(char ch, double pos_x, double pos_y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw text. </summary>
	///
	/// <param name="text"> 	The text. </param>
	/// <param name="pos_x">	The position x coordinate. </param>
	/// <param name="pos_y">	The position y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawText( const std::string& text, double pos_x, double pos_y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw number. </summary>
	///
	/// <param name="number">	Number of. </param>
	/// <param name="pos_x"> 	The position x coordinate. </param>
	/// <param name="pos_y"> 	The position y coordinate. </param>
	/// <param name="width"> 	(Optional) The width. </param>
	///-------------------------------------------------------------------------------------------------

	void DrawNumber(size_t number, double pos_x, double pos_y, size_t width = 0);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Converts Int to string. </summary>
	///
	/// <param name="number">	Number of. </param>
	///
	/// <returns>	A std::string. </returns>
	///-------------------------------------------------------------------------------------------------

	std::string IntToStr(int number);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Converts a number to an int. </summary>
	///
	/// <param name="number">	Number of. </param>
	///
	/// <returns>	number as an int. </returns>
	///-------------------------------------------------------------------------------------------------

	int StrToInt( const std::string& number);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets a timer. </summary>
	///
	/// <param name="t">	Time to process. </param>
	///-------------------------------------------------------------------------------------------------

	void SetTimer(double t);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Counts times. </summary>
	///
	/// <param name="dt">	The delta time. </param>
	///-------------------------------------------------------------------------------------------------

	void Time(double dt);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the timer. </summary>
	///
	/// <returns>	The timer. </returns>
	///-------------------------------------------------------------------------------------------------

	double GetTimer();

private:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draws. </summary>
	///
	/// <param name="tex_x">	The tex x coordinate. </param>
	/// <param name="tex_y">	The tex y coordinate. </param>
	/// <param name="pos_x">	The position x coordinate. </param>
	/// <param name="pos_y">	The position y coordinate. </param>
	///-------------------------------------------------------------------------------------------------

	void Draw(double tex_x, double tex_y, double pos_x, double pos_y);

private:
	/// <summary>	The width. </summary>
	double m_width;
	/// <summary>	The height. </summary>
	double m_height;
	/// <summary>	The layer. </summary>
	size_t m_layer;
	/// <summary>	The timer. </summary>
	double timer;
};

#endif /* __TEXT_H__ */
