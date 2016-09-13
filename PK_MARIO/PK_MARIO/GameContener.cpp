#include "StdAfx.h"
#include "GameContener.h"
#include "Tile.h"


bool GameContener::IsAnyFieldAboveMe(double x, double y)
{
	if ((map[(int)x][(int)y + 1].GetType() != TYPES::None) ||
		(map[(int)x - 1][(int)y + 1].GetType() != TYPES::None) ||
		(map[(int)x + 1][(int)y + 1].GetType() != TYPES::None));
	//Collisions box(x, y, x + SpriteRenderer::GetTileWidth(), y + SpriteRenderer::GetTileHeight());
	//box.IsOver()
	return true;
}

void GameContener::LoadLevelFromFile(const std::string & filename)
{
	std::ifstream lvl(filename.c_str());
	if (!lvl)
	{
		std::cerr << "file level error " << filename << "\n";
		return;
	}

	lvl >> m_width >> m_height;
	map.resize(m_width);
	for (size_t y = 0; y < m_width; ++y)
	{
		map[y].resize(m_height);
	}

	int tmp;

	for (int i = m_height-1; i >= 0; i--)//wysokoœæ
	{
		for (int j = 0; j <m_width; ++j)//szerokosc
		{
			lvl >> tmp;
			map[j][i] = Tile(j, i, true,TYPES::FieldType(tmp), TYPES::Background);
		}
	}
	grid_width = SpriteRenderer::GetVerticalTilesOnScreenCount();
	grid_width++;
	grid_height = SpriteRenderer::GetVerticalTilesOnScreenCount();
	m_grid.resize(grid_width);
	for (size_t i = 0; i < grid_width; ++i)
	{
		m_grid[i].resize(grid_height);
	}


}
TYPES::FieldType GameContener::Field(size_t x, size_t y) 
{
	if (x >= m_width || y >= m_height)
	{
		return TYPES::None;
	}
	return map[x][y].GetType();
}

void GameContener::SetLevel( double dx)
{
	int half_grid_width = (m_grid.at(0).size() - 1) / 2;

	for (size_t x = 0; x < m_grid.size(); x++)
	{

		for (size_t y = 0; y < m_grid[x].size(); y++)
		{

			int draw_x = x + static_cast<int>(dx) - half_grid_width ;
			int draw_y = y;
			m_grid[x][y] = &map[draw_x][draw_y];
		}
	}
	}

void GameContener::SetPlayer()
{
	std::string platformleft = "PlatformLeftEnd", platformmid = "PlatformMidPart", platformright = "PlatformRightEnd";
	m_player = new Player(9, 5, true, TYPES::Players, TYPES::PlayerLayer,4, GetWidth());
	m_player->setSprite(Sprite(SpriteData(5, 0.2, 0, 4 * 32, 32, 32, true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_right", TYPES::GoRight);
	m_player->setSprite(Sprite(SpriteData(5, 0.2, 0, 5 * 32, 32, 32, true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_left", TYPES::GoLeft);
	m_player->setSprite(Sprite(SpriteData(1, 0.2, 0, 6 * 32, 32, 32, true, TYPES::PlayerLayer), std::string("data\\tex3.png")), "player_stop", TYPES::Stand);
	m_player->Insert(platformleft, Sprite(SpriteData(1, 1, 0, 1 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));
	m_player->Insert(platformmid, Sprite(SpriteData(1, 1, 0, 2 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));
	m_player->Insert(platformright, Sprite(SpriteData(1, 1, 0, 3 * 32, 32, 32, true, TYPES::Foreground), std::string("data\\tex3.png")));

	m_stored_player_pos_x = m_player->get_x();
	
}

void GameContener::DrawLevel(double dx)
{
	std::string platformleft = "PlatformLeftEnd", platformmid = "PlatformMidPart", platformright = "PlatformRightEnd";

	double tile_height = SpriteRenderer::GetTileHeight();
	double tile_width = SpriteRenderer::GetTileWidth();

	glPushMatrix();

	{
		glTranslatef(dx*tile_width - 0.45, 0, 0);

		double offset = dx - static_cast<int>(dx);
		glTranslatef(-offset * tile_width, 0, 0);
		for (size_t x = 0; x < m_grid.size(); ++x)
		{

			for (size_t y = 0; y < m_grid[x].size(); ++y)
			{

				if (m_grid[x][y]->isExist()) {
					std::string name;
					switch (m_grid[x][y]->GetType()) {
					case TYPES::PlatformLeftEnd:
						name = platformleft;
						break;
					case TYPES::PlatformMidPart:
						name = platformmid;
						break;
					case TYPES::PlatformRightEnd:
						name = platformright;
						break;
					case TYPES::None:
						name = "NULL";
						break;
					}

					if (name != "NULL")
					{
						const double tile_width = m_grid[x][y]->SpriteLoader::Get(name)->m_renderer->GetTileWidth();
						const double tile_height = m_grid[x][y]->SpriteLoader::Get(name)->m_renderer->GetTileWidth();
					
						m_grid[x][y]->SpriteLoader::Get(name)->DrawCurrentFrame((x)* tile_height, y * tile_width, tile_width, tile_height);
					}
				}

			}
		}
	}
	glPopMatrix();
}

void GameContener::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (m_player->MoveMap()) {
		m_stored_player_pos_x = m_player->get_x();
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glTranslatef(-(m_stored_player_pos_x*SpriteRenderer::GetTileWidth() - 0.45), 0, 0);
		glMatrixMode(GL_MODELVIEW);

		SetLevel(m_stored_player_pos_x);
		DrawLevel(m_stored_player_pos_x);
		m_player->Draw();
		t.DrawText("witaj swiecie", 0.3, 0.5);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	SDL_GL_SwapBuffers();
}

void GameContener::UpdateScene(double dt)
{
	m_player->SetDefaultMovement();
	m_player->Update(dt);
}

Player * GameContener::GetPLayer()
{
	return m_player;
}
