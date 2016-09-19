#include "StdAfx.h"

#include "HallOfFame.h"
#include "Text.h"


HallOfFame::HallOfFame()
	: m_is_done(false) 
{
	LoadFromFile();
}

void HallOfFame::Draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Text t(0.08, 0.08);
	t.DrawText("Hall Of Fame", 0.01, 0.9);

	t.SetSize(0.035, 0.035);
	double y = 0.7;
	double x = 0.15;
	for (size_t i = 0; i < m_entries.size(); ++i) 
	{
		t.DrawText(m_entries.at(i).name, x, y);
		t.DrawNumber(m_entries.at(i).points, x + 0.4, y, 8);
		y -= 0.07;
	}

	SDL_GL_SwapBuffers();
}

bool HallOfFame::Update(double /* dt */) 
{
	return !IsDone();
}

void HallOfFame::ProcessEvents() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			m_is_done = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			m_is_done = true;
			break;
		}
	}
}

bool HallOfFame::IsDone()
{
	return m_is_done;
}

void HallOfFame::NotDone()
{
	m_is_done = false;
}

void HallOfFame::LoadFromFile() 
{
	std::ifstream in("data/hof.txt");
	if (!in) 
	{
		std::cerr << "Cant open Hall of Fame file\n";
		return;
	}

	Entry entry;
	while (in >> entry.name >> entry.points) 
	{
		m_entries.push_back(entry);
	}
}
