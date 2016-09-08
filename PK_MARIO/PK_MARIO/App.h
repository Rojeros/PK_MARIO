#include "StdAfx.h"
#include "Field.h"
#include "Player.h"
#include "Sprite.h"
//#include "Level.h"
//#include "SpriteGrid.h"
//#include "Engine.h"

/// <summary>	Main window of Application </summary>
class App
{
public:
	Player * gracz;
	/// <summary>	Constructor. </summary>
	///
	/// <param name="win_width">	  	Width of the window. </param>
	/// <param name="win_height">	  	Height of the window. </param>
	/// <param name="fullscreen_mode">	true to enable fullscreen mode, false to disable it. </param>

	App(size_t win_width, size_t win_height, bool fullscreen_mode) :
		m_window_width(win_width),
		m_window_height(win_height),
		m_fullscreen(fullscreen_mode),
		m_stored_player_pos_x(1.0)
	{
		gracz=new Player(8, 0, true, TYPES::Players, TYPES::Background, 10, 1);
		SpriteData* cosik = new SpriteData(5, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer);
		Sprite * cos = new Sprite(*cosik, std::string("data\\tex.bmp"));
		gracz->setSprite(*cos, "lewo");
		//gracz = &osoba;
	}

	/// <summary>	Runs window. </summary>
	void Run();

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

private:


	/// <summary>	Width of the window. </summary>
	size_t m_window_width;
	/// <summary>	Height of the window. </summary>
	size_t m_window_height;
	/// <summary>	true to fullscreen. </summary>
	bool m_fullscreen;
	/// <summary>	true if this object is done. </summary>
	bool is_done;

	/// <summary>	The screen. </summary>
	SDL_Surface* m_screen;

	/// <summary>	The stored player position x coordinate. </summary>
	double m_stored_player_pos_x;
};

