#ifndef APP_H_
#define APP_H_
#include "StdAfx.h"
#include "Field.h"
#include "Player.h"
#include "Sprite.h"
#include "GameContener.h"
#include "HallOfFame.h"
#include "ScoreSubmit.h"

/// <summary>	Main window of Application </summary>
class App
{
public:
	
	/// <summary>	 Consructor. </summary>
	///
	/// <param name="win_width">	  	Width of the window. </param>
	/// <param name="win_height">	  	Height of the window. </param>
	/// <param name="fullscreen_mode">	true to enable fullscreen mode, false to disable it. </param>

	App(size_t win_width, size_t win_height, bool fullscreen_mode) :
		m_window_width(win_width),
		m_window_height(win_height),
		m_fullscreen(fullscreen_mode),
		state(0),scoreSubmit(0),hallOfFame()
	
	{
		game = new GameContener();
		game->SetPlayer();
	}

	/// <summary>	Runs window. </summary>
	void Run();
	/// <summary>	Destructor. </summary>
	App::~App() {
		
		delete game;
	}

private:

	/// <summary>	Draws widow </summary>
	void Draw();

	/// <summary>	Updates the widnow </summary>
	///
	/// <param name="dt">	The delta. </param>

	void Update(double dt);

	/// <summary>	Resizes the window </summary>
	///
	/// <param name="width"> 	The width. </param>
	/// <param name="height">	The height. </param>

	void Resize(size_t width, size_t height);


	/// <summary>	Process the events. </summary>
	void ProcessEvents();

	/// <summary>	Width of the window. </summary>
	size_t m_window_width;
	/// <summary>	Height of the window. </summary>
	size_t m_window_height;
	/// <summary>	true to fullscreen. </summary>
	bool m_fullscreen;
	/// <summary>	true if this object is done. </summary>
	bool is_done;

	/// <summary>	Pointer to screen object. </summary>
	SDL_Surface* m_screen;
	/// <summary>	Pointer to game contener object. </summary>
	GameContener * game;
	/// <summary>	Windows state status, 0 -game, 1 - score submit,2-hall of fame, 3- reset game . </summary>
	int state;
	/// <summary>	The score submit object. </summary>
	ScoreSubmit scoreSubmit;
	/// <summary>	The hall of fame object. </summary>
	HallOfFame hallOfFame;
};


#endif