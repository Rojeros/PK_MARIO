#include "StdAfx.h"
#include "HallOfFame.h"
#include "App.h"

void App::ProcessEvents()
{
	if (is_done)
	{
		return;
	}

	// przyjrzyj zdarzenia
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_VIDEORESIZE)
		{
			Resize(event.resize.w, event.resize.h);
		}
		else if (event.type == SDL_QUIT)
		{
			is_done = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			is_done = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
		{
			game->GetPLayer()->Run();
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d)
		{
			game->GetPLayer()->StopRunning();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
			game->GetPLayer()->FireBullet();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		{
			game->GetPLayer()->Jump();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
		{
			game->GetPLayer()->GoLeft();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
		{
			game->GetPLayer()->GoRight();
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT)
		{
			game->GetPLayer()->StopLeft();
		}
		else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT)
		{
			game->GetPLayer()->StopRight();
		}
	}
}


void App::Run()
{
	// inicjalizacja okna
	SDL_Init(SDL_INIT_VIDEO);
	Resize(m_window_width, m_window_height);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // podwójne buforowanie

												 // inicjalizacja OpenGL
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST); // niewyœwietlanie przezroczystych fragmentów sprite'a
	glAlphaFunc(GL_GEQUAL, 0.1);

	//  std::string atlas_filename = "data/tex.png";
	//Engine& engine = Engine::Get();
//	engine.Load();
	//engine.GetRenderer()->LoadTexture(atlas_filename);
//	m_player->SetSprites(
//		SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_left"))),
//		SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_right"))),
//		SpritePtr(new Sprite(engine.GetSpriteConfig()->Get("player_stop"))));

	// main loop
	HallOfFame hof;
	is_done = false;
	size_t last_ticks = SDL_GetTicks();
	while (!is_done)
	{
		ProcessEvents();

		// time update
		size_t ticks = SDL_GetTicks();
		double delta_time = (ticks - last_ticks) / 1000.0;
		last_ticks = ticks;

		// update & render
		if (delta_time > 0)
		{
			Update(delta_time);
		}
		Draw();
	}
	SDL_Quit();
}

void App::Update(double dt)
{
	game->UpdateScene(dt);
//	m_player->Update(dt);
}

void App::Draw()
{
	game->DrawScene();
}

void App::Resize(size_t width, size_t height)
{
	m_screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_HWSURFACE);
	assert(m_screen && "video error");
	m_window_width = width;
	m_window_height = height;

	SpriteRenderer::SetProjection(width, height);
}
