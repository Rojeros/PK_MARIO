#include "StdAfx.h"
#include "Level.h"


std::vector<std::vector<Tile*>>* Level::GetGrid()
{
	return &m_grid;
}

std::vector<std::vector<Tile>>* Level::GetMap()
{
	return &map;
}

void Level::LoadLevelFromFile(const std::string & filename)
{
	bool exist;
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

	for (int i = m_height - 1; i >= 0; i--)
	{
		for (int j = 0; j < m_width; ++j)
		{
			lvl >> tmp;
			if (TYPES::FieldType(tmp) == TYPES::None)
			{
				exist = false;
			}
			else
				exist = true;
			map[j][i] = Tile(j, i, exist, TYPES::FieldType(tmp), TYPES::Background);
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
TYPES::FieldType Level::Field(size_t x, size_t y)
{
	if (x >= m_width || y >= m_height)
	{
		return TYPES::None;
	}
	return map[x][y].GetType();
}

void Level::SetLevel(double dx)
{
	int half_grid_width = (m_grid.at(0).size() - 1) / 2;

	for (size_t x = 0; x < m_grid.size(); x++)
	{

		for (size_t y = 0; y < m_grid[x].size(); y++)
		{

			int draw_x = x + static_cast<int>(dx) - half_grid_width;
			int draw_y = y;
			m_grid[x][y] = &map[draw_x][draw_y];

		}
	}
}

void Level::DrawLevel(double dx)
{

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

				if (m_grid[x][y]->isExist())
				{

					m_grid[x][y]->SetPosition(x, y);
					m_grid[x][y]->Draw();
					//m_grid[x][y]->SpriteLoader::Get(name)->DrawCurrentFrame((x)* tile_height, y * tile_width, tile_width, tile_height);
				}


			}
		}
	}
	glPopMatrix();
}

void Level::deleteLevel()
{
	map.clear();
	m_grid.clear();
}

size_t Level::GetWidth()
{
	return m_width;
}

size_t Level::GetHeight()
{
	return m_height;
}
