#include "StdAfx.h"
#include "Field.h"
#include "Player.h"
#include "Sprite.h"
#include "GameContener.h"
//#include "Level.h"
//#include "SpriteGrid.h"
//#include "Engine.h"

/// <summary>	Main window of Application </summary>
class App
{
public:
	
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
		std::string platformleft = "PlatformLeftEnd", platformmid = "PlatformMidPart", platformright = "PlatformRightEnd";
		
		game = new GameContener();
		game->LoadLevelFromFile("data\\1.lvl");
		
		m_player =new Player(9, 5, true, TYPES::Players, TYPES::PlayerLayer, 10, 1,game->GetWidth());
		m_player->setSprite(Sprite( SpriteData(5, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_right",TYPES::GoingRight);
		m_player->setSprite(Sprite(SpriteData(5, 0.2, 0, 5 * 32, 32, 32,true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_left", TYPES::GoingLeft);
		m_player->setSprite(Sprite(SpriteData(1, 0.2, 0, 6 * 32, 32, 32, true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_stop", TYPES::Standing);
		m_player->Insert(platformleft,Sprite(SpriteData(1, 1, 0, 1 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));
		m_player->Insert(platformmid, Sprite(SpriteData(1, 1, 0, 2 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));
		m_player->Insert(platformright, Sprite(SpriteData(1, 1, 0, 3 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));
		
		m_stored_player_pos_x = m_player->get_x();
	}

	/// <summary>	Runs window. </summary>
	void Run();
	App::~App() {
		delete m_player;
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

	/// <summary>	The screen. </summary>
	SDL_Surface* m_screen;
	Player * m_player;
	GameContener * game;
	/// <summary>	The stored player position x coordinate. </summary>
	double m_stored_player_pos_x;
};

