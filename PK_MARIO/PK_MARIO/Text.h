#ifndef __TEXT_H__
#define __TEXT_H__
#include "StdAfx.h"
#include"SpriteRenderer.h"
#include "Sprite.h"

class Text {
public:
	explicit Text(double width = 0.025, double height = 0.025, size_t layer = 0) {
		SetSize(width, height);
		SetLayer(layer);
	}

	void SetSize(double width, double height) {
		m_width = width;
		m_height = height;
	}

	void SetLayer(size_t layer) {
		m_layer = layer;
	}


	void DrawDigit(char ch, double pos_x, double pos_y);
	void DrawLetter(char ch, double pos_x, double pos_y);
	void DrawSpecial(char ch, double pos_x, double pos_y);
	void DrawText( const std::string& text, double pos_x, double pos_y);
	void DrawNumber(size_t number, double pos_x, double pos_y, size_t width = 0);
	std::string IntToStr(int number);
	int StrToInt( const std::string& number);
	void SetTimer(double t);
	void Time(double dt);
	double GetTimer();

private:
	void Draw(double tex_x, double tex_y, double pos_x, double pos_y);

private:
	double m_width;
	double m_height;
	size_t m_layer;
	double timer;
};

#endif /* __TEXT_H__ */
