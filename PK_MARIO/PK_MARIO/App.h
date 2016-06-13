#include "StdAfx.h"
#include "Player.h"
#include "Level.h"
#include "SpriteGrid.h"
#include "Engine.h"

class App {
public:
	explicit App(size_t win_width, size_t win_height, bool fullscreen_mode) :
		m_window_width(win_width),
		m_window_height(win_height),
		m_fullscreen(fullscreen_mode),
		m_stored_player_pos_x(1.0) {

		m_level_view.StoreSprite(FT::PlatformLeftEnd, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_left"))));
		m_level_view.StoreSprite(FT::PlatformMidPart, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_mid"))));
		m_level_view.StoreSprite(FT::PlatformRightEnd, SpritePtr(new Sprite(Engine::Get().GetSpriteConfig()->Get("platform_right"))));

		m_level.reset(new Level());
		m_level->LoadFromFile("data/1.lvl");
		m_player.reset(new Player(9, 5, m_level->GetWidth()));
	}

	void Run();

private:
	void Draw();
	void Update(double dt);
	void Resize(size_t width, size_t height);
	void ProcessEvents();

private:
	size_t m_window_width;   // szerokoœæ okna
	size_t m_window_height;  // wysokoœæ okna
	bool m_fullscreen;       // tryb pe³noekranowy
	bool is_done;
	SDL_Surface* m_screen;

	PlayerPtr m_player;

	LevelPtr m_level;
	SpriteGrid m_level_view;

	double m_stored_player_pos_x;
};

