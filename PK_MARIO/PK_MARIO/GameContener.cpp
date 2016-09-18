#include "StdAfx.h"
#include "GameContener.h"
#include "Tile.h"
#include <algorithm>

void GameContener::deleteList()
{
	for (int i = 0; i < monsterList.size(); i++)
		delete monsterList[i];
	monsterList.clear();
}

void GameContener::SetPlayer()
{
	

	p_level = new Level();
	p_level->LoadLevelFromFile("data\\" + std::to_string((int)m_entities_to_create[numberOfLevel][0].y) + ".lvl");
	m_player = new Player(9, 5, true, TYPES::Players, TYPES::PlayerLayer, 4, p_level->GetWidth());
	m_player->SetSprite();
	SpriteRenderer::setFilename("data\\tex" + std::to_string((int)m_entities_to_create[numberOfLevel][0].x) + ".png");
	m_stored_player_pos_x = m_player->GetX();
	try
	{
	Tile a;	a.SetSprite();
	
	Monster b; b.SetSprite();
	Bonus c; c.SetSprite();
	Bullet d; d.SetSprite();
	}
	catch (std::string e)
	{
		std::cout << e;
	}
	numberOfLevel = -1;
	SetLevel();
}


void GameContener::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (m_player->MoveMap()) {
		m_stored_player_pos_x = m_player->GetX();
	}
	if (m_stored_player_live != m_player->GetLifesCount()) 
	{
		m_stored_player_live = m_player->GetLifesCount();
			m_stored_player_pos_x = 9;
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glTranslatef(-(m_stored_player_pos_x*SpriteRenderer::GetTileWidth() - 0.45), 0, 0);
		glMatrixMode(GL_MODELVIEW);

		p_level->SetLevel(m_stored_player_pos_x);
		p_level->DrawLevel(m_stored_player_pos_x);
		m_player->Draw();
		for (std::vector<Character*>::iterator it = monsterList.begin(); it != monsterList.end(); ++it) {
			if ((*it)->IsAlive()) {
				(*it)->Draw();
			}
		}
	
		if (t.GetTimer() > 0)
		{
			t.SetSize(0.08, 0.08);
			t.DrawText("Hello", 0.3, 0.5);
		}
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	SDL_GL_SwapBuffers();
}

void GameContener::UpdateScene(double dt)
{
	t.Time(dt);
	m_player->SetDefaultMovement();

	CheckPlayerEntitiesCollisions(dt);
	CheckEntityEntityCollisions(dt);
	m_player->Update(dt, p_level);
	
	if (m_player->isBulletFired()) {
		addBullet();
	}


	monsterList.erase(
		std::remove_if(monsterList.begin(), monsterList.end(), [](Character * a) {return (*a).IsDead(); }), monsterList.end());

	for (std::vector<Character*>::iterator it = monsterList.begin(); it != monsterList.end(); ++it) {
		if ((*it)->IsAlive()) {
			(*it)->Update(dt, p_level);
		}
		
	}

	

}

Player * GameContener::GetPLayer()
{
	return m_player;
}

void GameContener::addEnemy(double x, double y)
{
	Monster * ptr = new Monster(x, y);
	monsterList.push_back(ptr);
	
			ptr->SetSprite();
	
}

void GameContener::CheckPlayerEntitiesCollisions(double dt) {
	// poziomy i pionowy aabb gracza w nastêpnym 'kroku'
	
	Collisions player_box_x = m_player->GetNextHorizontalAabb(dt);
	Collisions player_box_y = m_player->GetNextVerticalAabb(dt);

	for (std::vector<Character*>::iterator it = monsterList.begin(); it != monsterList.end(); ++it) {
	
		if ((*it)->GetType() == TYPES::PlayerBullet) {
			// postaæ nie koliduje ze swoimi pociskami
			continue;
		}
		if ((*it)->GetType() == TYPES::Bonuses) {
			Collisions entity_box = (*it)->GetAabb();
			if ((player_box_y.IsUnder(entity_box)) || (player_box_x.IsOnLeftOf(entity_box)) || (player_box_x.IsOnRightOf(entity_box)) || (player_box_y.IsUnder(entity_box))) {
				Bonus * ptr = dynamic_cast<Bonus*>(*it);
				if (ptr->getBonusType() == TYPES::hp)
				{
					m_player->addLive();
				}
				else if (ptr->getBonusType() == TYPES::levelEnd)
					m_player->LevelCompleted(true);

				(*it)->SetIsDead();
			}
			// postaæ nie koliduje ze swoimi pociskami
			continue;
		}

		// nieœmiertelna postaæ nie koliduje z innymi jednostkami,
		// ale mo¿e zbieraæ np. upgrade'y (patrz wy¿ej)
		if (m_player->IsImmortal()) {
			continue;
		}

		(*it)->SetDefaultMovement();
		Collisions entity_box = (*it)->GetAabb();

		// sprawdŸ czy wyst¹pi³a kolizja. Je¿eli tak to gracz, zdecyduje o losie
		// swoim i jednostki. Zauwa¿my, ¿e je¿eli wyst¹pi kolizja poni¿ej gracza
		// (naskoczenie na jednostkê), to pozosta³e nie bêd¹ sprawdzane.
		if (player_box_y.IsUnder(entity_box)) {
			// naskoczenie na jednostkê
			m_player->CollisionUnderPlayer(it);
			player_box_y = m_player->GetNextVerticalAabb(dt);
		}
		else if (player_box_x.IsOnLeftOf(entity_box)) {
			m_player->ForbidGoingRight();
			m_player->CollisionOnRight(it);
			player_box_x = m_player->GetNextHorizontalAabb(dt);
		}
		else if (player_box_x.IsOnRightOf(entity_box)) {
			m_player->ForbidGoingLeft();
			m_player->CollisionOnLeft(it);
			player_box_x = m_player->GetNextHorizontalAabb(dt);
		}
		else if (player_box_y.IsUnder(entity_box)) {
			m_player->Fall();
			m_player->CollisionOverPlayer(it);
			player_box_y = m_player->GetNextVerticalAabb(dt);
		}
	}
}

void GameContener::CheckCollisionOfOnePair(std::vector<Character*>::iterator fst_entity, TYPES::FieldType fst_type, std::vector<Character*>::iterator snd_entity, TYPES::FieldType snd_type, double dt)
{
	if ((*fst_entity)->GetNextAabb(dt).Collides((*snd_entity)->GetNextAabb(dt)) == false) {
		return;
	}

	// makro SWAP_IF pozwala zamieniæ znaczenie argumentów fst_* z snd_*
	// w ten sposób, ¿e sprawdzaj¹c kolizjê otrzymujemy wska¿niki zawsze
	// w dobrej kolejnoœci, tzn. tak, aby ka¿d¹ parê obs³ugiwaæ jeden raz
#define SWAP_IF( type_a, type_b )  \
    if (fst_type == type_a && snd_type == type_b) {  \
    	std::swap(fst_entity, snd_entity);   \
        std::swap(fst_type, snd_type);   \
    }

	SWAP_IF(TYPES::PlayerBullet, TYPES::Enemy)

		// w tym miejscu wiemy, ¿e je¿eli nast¹pi³a kolizja Mush z PlayerBullet,
		// to jednostka Mush bêdzie pod fst_entity a PlayerBullet pod snd_entity

		if (fst_type == TYPES::Enemy && snd_type == TYPES::PlayerBullet) {
			(*snd_entity)->SetIsDead(true);
			m_player->AddScores((*fst_entity)->GetScoresWhenKilled());
			(*fst_entity)->KilledWithBullet();
		}

	if (fst_type == TYPES::Enemy && snd_type == TYPES::Enemy) {
		(*fst_entity)->NegateXVelocity();
		(*snd_entity)->NegateXVelocity();
	}

#undef SWAP_IF
}

void GameContener::CheckEntityEntityCollisions(double dt) {
	// sprawdzenie ka¿dej pary (ka¿dej jednokrotnie) - O(n^2)
	std::vector<Character*>::iterator outer, inner;
	std::vector<Character*>::iterator out_entity, inn_entity;

	TYPES::FieldType out_type, inn_type;
	for (outer = monsterList.begin(); outer != monsterList.end(); ++outer) {
		out_entity = outer;
		out_type = (*outer)->GetType();
		if ((*out_entity)->IsDead()) {
			continue;
		}
		inner = outer;
		++inner;
		for (; inner != monsterList.end(); ++inner) {
			inn_entity = inner;
			inn_type = (*inn_entity)->GetType();
			if ((*inn_entity)->IsDead()) {
				continue;
			}
			CheckCollisionOfOnePair(inn_entity, inn_type, out_entity, out_type, dt);
		}
	}
}
bool GameContener::IsMarkedToDelete(Character *o)
{
	return true;
}

void GameContener::addBullet()
{
	double x, xvel;
	const double eps = 0.0001;  // jakakolwiek prêdkoœæ
	if (m_player->GetState() == TYPES::TurnLeft) {
		x = m_player->GetX() - .3;
		xvel = -eps;
	}
	else if (m_player->GetState() == TYPES::TurnRight) {
		x = m_player->GetX() + .7;
		xvel = eps;
	}
	else {
		x = m_player->GetXVelocity() < 0 ? m_player->GetX() - .3 : m_player->GetX() + .7;
		xvel = m_player->GetXVelocity();
	}
	monsterList.push_back(new Bullet(x, m_player->GetY(), xvel, 0));
	if (dynamic_cast<Bullet*>(&*monsterList.back()) != NULL) {
		Bullet*ptr = dynamic_cast<Bullet*>(&*monsterList.back());
		ptr->SetSprite();
	}

	m_player->DisableBullet();
}

void GameContener::addBonus(double x, double y, TYPES::BonusType type1)
{

	monsterList.push_back(new Bonus(x, y, true, TYPES::Bonuses, TYPES::Foreground, type1));
	if (dynamic_cast<Bonus*>(&*monsterList.back()) != NULL) {
		Bonus*ptr = dynamic_cast<Bonus*>(&*monsterList.back());
		ptr->SetSprite();
	}

}

bool GameContener::isLevelcomplete()
{
	if (m_player->IsLevelCompleted()) 
	{
		SetLevel();
		return true;
	}
	return false;
}

bool GameContener::isLevelFaild()
{
	return (m_player->GetLifesCount()<=0);
}

void GameContener::Reset()
{
	deleteList();
	p_level->~Level();
	p_level = new Level();
	p_level->LoadLevelFromFile("data\\" + std::to_string((int)m_entities_to_create[numberOfLevel][0].y) + ".lvl");
	m_player->~Player();
	m_player = new Player(m_entities_to_create[numberOfLevel][0].x, m_entities_to_create[numberOfLevel][0].y, true, TYPES::Players, TYPES::PlayerLayer, 4, p_level->GetWidth());
	m_player->SetSprite();
	m_stored_player_pos_x = 9;
	numberOfLevel = -1;
	SetLevel();
}

void GameContener::SetLevel()
{
	numberOfLevel++;
	if (numberOfLevel >= levels)
		numberOfLevel = 0;

	deleteList();
	p_level->~Level();
	p_level = new Level();
	m_player->LevelCompleted(false);
	m_stored_player_pos_x = 9;
	SpriteRenderer::resetTexture();


	for (int i = 0; i < m_entities_to_create[numberOfLevel].size(); i++) {

		if (m_entities_to_create[numberOfLevel][i].name == "level")
		{
			SpriteRenderer::setFilename("data\\tex" + std::to_string((int)m_entities_to_create[numberOfLevel][i].x) + ".png");
			p_level->LoadLevelFromFile("data\\" + std::to_string((int)m_entities_to_create[numberOfLevel][i].y) + ".lvl");
		}else
		if (m_entities_to_create[numberOfLevel][i].name == "player")
		{
			m_player->SetPosition(m_entities_to_create[numberOfLevel][i].x, m_entities_to_create[numberOfLevel][i].y);
		}else
		if (m_entities_to_create[numberOfLevel][i].name == "enemy")
		{
			addEnemy(m_entities_to_create[numberOfLevel][i].x, m_entities_to_create[numberOfLevel][i].y);
		}
		else
		if (m_entities_to_create[numberOfLevel][i].name == "hp")
		{
			addBonus(m_entities_to_create[numberOfLevel][i].x, m_entities_to_create[numberOfLevel][i].y,TYPES::hp);
		}
		else
		if (m_entities_to_create[numberOfLevel][i].name == "levelEnd")
		{
			addBonus(m_entities_to_create[numberOfLevel][i].x, m_entities_to_create[numberOfLevel][i].y, TYPES::levelEnd);
		}
	}

}

void GameContener::LoadEntitiesFromFile(const std::string & filename)
{
	std::ifstream file(filename.c_str());
	if (!file) {
		std::cerr << "Error on loading init File " << "\n";
		return;
	}

	// wczytaj linia po linii
	const int buffer_size = 1024;
	char buffer[buffer_size];


	file.getline(buffer, buffer_size);
	std::string line(buffer);
	std::istringstream iss(line);
	iss >> levels;
	m_entities_to_create.resize(levels);

	int i = -1;
	while (file) {
		

		file.getline(buffer, buffer_size);
		std::string line(buffer);
		if (line.length() < 5 || line.at(0) == '#')
			continue;
		std::istringstream iss(line);
		LevelEntityData data;

		iss >> data.name;
		iss >> data.x;
		iss >> data.y;
		if (data.name == "level") {
			i=i++;
		}

			m_entities_to_create[i].push_back(data);
//			std::cout << "[LoadEntityFromFile] " << i << " " << data.name << ", " << data.x << ", " << data.y << std::endl;



	}
	numberOfLevel = 0;
}
